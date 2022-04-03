#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>

typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;

static int dopath(Myfunc *, char *);

static int myftw(char *, Myfunc *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[]) {
    int ret;
    if (argc != 2) {
        printf("Usage: ftw <start directory>");
        return 1;
    }

    ret = myftw(argv[1], myfunc);
    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (ntot == 0)
        ntot = 1;
    printf("regular =           \t\t%ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
    printf("directories =       \t\t%ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
    printf("special block =     \t\t%ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
    printf("special symbol =    \t\t%ld, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
    printf("FIFO =              \t\t%ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
    printf("symbolic links =    \t\t%ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
    printf("sockets =           \t\t%ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);
    exit(ret);
}


#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4
static char *fullpath;
static size_t pathlen;
#define NAME_MAX 1024

typedef char sstring[1024];

struct str_list {
    sstring str;
    int depth;
    struct str_list *next;
};


struct str_list *new_str_list(const char *str, int depth) {
    struct str_list *
            new = (struct str_list *) malloc(sizeof(struct str_list));

    new->next = NULL;
    strcpy((char *) new->str, str);
    new->depth = depth;

    return new;
}

struct str_list *str_stack_push(struct str_list *head, const char *str, int depth) {
    struct str_list *new_head = new_str_list(str, depth);
    new_head->next = head;
    return new_head;
}

struct str_list *str_stack_pop(struct str_list *head, char *res, int *depth) {
    strcpy(res, head->str);
    *depth = head->depth;

    struct str_list *new_head = head->next;
    free(head);

    return new_head;
}

static int myftw(char *pathname, Myfunc *func) {
    return dopath(func, pathname);
}

void spaces(int count) {
    for (int i = 0; i < count; ++i) putchar('\t');
}

static int dopath(Myfunc *func, char *start_path) {
    struct str_list *stack = new_str_list(start_path, 0);
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp;
    sstring full_path;
    char *pos;
    int ret, n, current_depth;

    while (stack != NULL) {
        stack = str_stack_pop(stack, full_path, &current_depth);
        n = (int) strlen(full_path);

        if (lstat(full_path, &statbuf) < 0) {
            func(full_path, &statbuf, FTW_NS);
        } else {
            func(full_path, &statbuf, FTW_D);
        }

        pos = strrchr(full_path, '/');
        pos = pos ? pos + 1 : full_path;
        spaces(current_depth - 1);
        printf("%s %s %llu\n", "├─", pos, statbuf.st_ino);

        if ((dp = opendir(full_path)) == NULL) {
            ret = func(fullpath, &statbuf, FTW_DNR);
            break;
        }

        full_path[n++] = '/';
        full_path[n] = 0;

        while ((dirp = readdir(dp)) != NULL) {
            strcpy(&full_path[n], dirp->d_name);
            if (dirp->d_type != DT_DIR) {

                if (lstat(full_path, &statbuf) < 0)
                    func(full_path, &statbuf, FTW_NS);
                else {
                    func(full_path, &statbuf, FTW_F);
                    spaces(current_depth);
                    printf("%s %s %llu\n", "├─", strrchr(full_path, '/') + 1, statbuf.st_ino);
                }
            } else if (strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0) {
                stack = str_stack_push(stack, full_path, current_depth + 1);
            }
            full_path[n] = 0;
        }
        if (closedir(dp) < 0) {
            printf("can't close directory %s", fullpath);
        }
    }

    return (ret);
}

static int myfunc(const char *pathname, const struct stat *statptr, int type) {
    switch (type) {
        case FTW_F:
            switch (statptr->st_mode & S_IFMT) {
                case S_IFREG:
                    nreg++;
                    break;
                case S_IFBLK:
                    nblk++;
                    break;
                case S_IFCHR:
                    nchr++;
                    break;
                case S_IFIFO:
                    nfifo++;
                    break;
                case S_IFLNK:
                    nslink++;
                    break;
                case S_IFSOCK:
                    nsock++;
                    break;
                case S_IFDIR: {
                    printf("IFDIR");
                    return 0;
                }
            }
            break;
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR: {
            printf("закрыт доступ к каталогу %s", pathname);
        }
            break;
        case FTW_NS:
            printf("ошибка вызова функции stat для %s", pathname);
            break;
        default:
            printf("неизвестный тип %d для файла %s", type, pathname);
    }
    return (0);
}
