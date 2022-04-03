#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>


#define V "│"
#define BRANCH "├─"
#define L "─"
#define E "└"

typedef char sstring[1024];

struct str_list {
    sstring str;
    int depth;
    ino64_t ino;
    struct str_list *next;
};

struct files_stat {
};

struct str_list *new_str_list(const char *str, int depth, ino64_t ino) {
    struct str_list *
    new = (struct str_list *) malloc(sizeof(struct str_list));

    new->next = NULL;
    strcpy((char *) new->str, str);
    new->depth = depth;
    new->ino = ino;

    return new;
}

struct str_list *str_stack_push(struct str_list *head, const char *str, int depth, ino64_t ino) {
    struct str_list *new_head = new_str_list(str, depth, ino);
    new_head->next = head;
    return new_head;
}

struct str_list *str_stack_pop(struct str_list *head, char *res, int *depth, ino64_t *ino) {
    strcpy(res, head->str);
    *depth = head->depth;
    *ino = head->ino;

    struct str_list *new_head = head->next;
    free(head);

    return new_head;
}

void spaces(int count) {
    for (int i = 0; i < count; ++i) putchar('\t');
}


int print_nd(const char *dir_path) {
    DIR *current_dir;
    struct dirent *current_dirent;
    struct str_list *dir_stack = new_str_list(dir_path, 0, 0);
    sstring current_path;
    int current_depth, current_path_len;
    ino64_t current_ino;

    while (dir_stack != NULL) {
        dir_stack = str_stack_pop(dir_stack, current_path, &current_depth, &current_ino);
        current_path_len = (int) strlen(current_path);

        spaces(current_depth - 1);
        printf("%s %s %llu\n", BRANCH, strrchr(current_path, '/') + 1, current_ino);

        current_dir = opendir(current_path);
        if (current_dir == NULL) { return 1; }

        while ((current_dirent = readdir(current_dir))) {
            if (current_dirent->d_type != DT_DIR) {
                spaces(current_depth);
                printf("%s %s %llu \n", BRANCH, current_dirent->d_name, current_dirent->d_ino);

            } else if (strcmp(current_dirent->d_name, "..") != 0 && strcmp(current_dirent->d_name, ".") != 0) {
                strcpy(&current_path[current_path_len + 1], current_dirent->d_name);
                current_path[current_path_len] = '/';

                dir_stack = str_stack_push(dir_stack, current_path, current_depth + 1, current_dirent->d_ino);

                current_path[current_path_len + 1] = 0;
            }
        }
    }
    return 0;
}

int main() {
    return print_nd("./.");
}


