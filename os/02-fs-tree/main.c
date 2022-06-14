#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>


typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;

int do_path(char *start_path);

int main(int argc, char *argv[]) {
    int ret;
//    if (argc != 2) {
//        printf("Usage: ftw <start directory>");
//        return 1;
//    }
//
//    ret = myftw(argv[1], myfunc);
    ret = do_path(".");
    exit(ret);
}

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
    if (res) {
        strcpy(res, head->str);
    }
    if (depth) {
        *depth = head->depth;
    }

    struct str_list *new_head = head->next;
    free(head);

    return new_head;
}

struct str_list *str_stack_clear(struct str_list *head) {
    while (head) {
        head = str_stack_pop(head, NULL, NULL);
    }
    return NULL;
}


void spaces(int count) {
    for (int i = 0; i < count; ++i) putchar('\t');
}

void handle_lstat_error(int error_num) {
    switch (error_num) {
        case EACCES:
            puts("A component of the path prefix denies search permission.");
            break;
        case EIO:
            puts("An error occurred while reading from the file system.");
            break;
        case ELOOP:
            puts("Too many symbolic links were encountered in resolving path.");
            break;
        case ENAMETOOLONG:
            puts("The length of a pathname exceeds PATH_MAX, or pathname component is longer than NAME_MAX.");
            break;
        case ENOTDIR:
            puts("A component of the path prefix is not a directory.");
            break;
        case ENOENT:
            puts("A component of path does not name an existing file or path is an empty string.");
            break;
        case EOVERFLOW:
            printf("The file size in bytes or the number of blocks allocated to the file or the file serial number cannot be represented correctly in the structure pointed to by buf.");
            break;
        default:
            puts("Unknown error");
    }
}

int do_path(char *start_path) {
    struct str_list *stack = new_str_list(start_path, 0);
    struct stat stat_buf;
    struct dirent *dir_p;
    DIR *dp;
    sstring path, pathtext;
    int current_depth, prev_depth;
    prev_depth = 0;

    while (stack != NULL) {
        stack = str_stack_pop(stack, path, &current_depth);

        if (current_depth <= prev_depth && current_depth > 0) {
            for (int i = 0; i < prev_depth - current_depth + 1; ++i) chdir("..");
        }

        prev_depth = current_depth;

        if (lstat(path, &stat_buf) < 0) {
            printf("lstat error: %s current dir = %s path = %s cd = %d pd = %d\n", strerror(errno),
                   getcwd(pathtext, 1024), path, current_depth, prev_depth);
            handle_lstat_error(errno);
            stack = str_stack_clear(stack);
            return 1;
        }

        spaces(current_depth - 1);
        printf("%s %s %llu\n", current_depth ? "├─" : "", path, stat_buf.st_ino);

        if ((dp = opendir(path)) == NULL) {
            perror("Can't open dir");
            return 1;
        }

        chdir(path);

        while ((dir_p = readdir(dp)) != NULL) {
            if (dir_p->d_type != DT_DIR) {
                if (lstat(dir_p->d_name, &stat_buf) < 0) {
                    printf("lstat error: %s\n", strerror(errno));
                    stack = str_stack_clear(stack);
                    handle_lstat_error(errno);
                    return 1;
                } else {
                    spaces(current_depth);
                    printf("%s %s %llu\n", "├─", dir_p->d_name, stat_buf.st_ino);
                }
            } else if (strcmp(dir_p->d_name, ".") != 0 && strcmp(dir_p->d_name, "..") != 0) {
                stack = str_stack_push(stack, dir_p->d_name, current_depth + 1);
            }
        }
        if (closedir(dp) < 0) {
            printf("can't close directory %s", path);
        }
    }

}