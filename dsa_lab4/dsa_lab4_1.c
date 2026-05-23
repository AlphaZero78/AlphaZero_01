#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
#define MAX_CELLS (MAX_SIZE * MAX_SIZE)

typedef struct {
    int x;
    int y;
    int accessible;  // 0 表示障碍物，1 表示可通行
} Point;

int is_valid(Point maze[MAX_SIZE][MAX_SIZE], int n, int m, int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m && maze[x][y].accessible == 1;
}

void print_path(FILE *fp_out, Point path[], int path_len) {
    for (int i = 0; i < path_len; i++) {
        fprintf(fp_out, "(%d,%d)", path[i].x, path[i].y);
        if (i != path_len - 1) {
            fprintf(fp_out, " -> ");
        }
    }
    fprintf(fp_out, "\n");
}

void copy_path(Point dest[], Point src[], int len) {
    for (int i = 0; i < len; i++) {
        dest[i] = src[i];
    }
}

void find_all_paths(Point maze[MAX_SIZE][MAX_SIZE],
                    int n,
                    int m,
                    Point current,
                    Point end,
                    int visited[MAX_SIZE][MAX_SIZE],
                    Point path[],
                    int path_len,
                    int *path_count,
                    Point shortest_path[],
                    int *shortest_len,
                    FILE *fp_out) {
    int directions[4][2] = {
        {0, 1},   // 右
        {1, 0},   // 下
        {0, -1},  // 左
        {-1, 0}   // 上
    };

    visited[current.x][current.y] = 1;
    path[path_len++] = current;

    if (current.x == end.x && current.y == end.y) {
        int steps = path_len - 1;
        (*path_count)++;

        fprintf(fp_out, "路径 %d:\n", *path_count);
        print_path(fp_out, path, path_len);
        fprintf(fp_out, "步数：%d\n\n", steps);

        if (*shortest_len == 0 || path_len < *shortest_len) {
            *shortest_len = path_len;
            copy_path(shortest_path, path, path_len);
        }

        visited[current.x][current.y] = 0;
        return;
    }

    for (int i = 0; i < 4; i++) {
        int new_x = current.x + directions[i][0];
        int new_y = current.y + directions[i][1];

        if (is_valid(maze, n, m, new_x, new_y) && !visited[new_x][new_y]) {
            Point next = {new_x, new_y, maze[new_x][new_y].accessible};
            find_all_paths(maze, n, m, next, end, visited, path, path_len,
                           path_count, shortest_path, shortest_len, fp_out);
        }
    }

    visited[current.x][current.y] = 0;
}

int main() {
    FILE *fp = fopen("lab4_1_data.txt", "r");
    FILE *fp_out = fopen("lab4_1_output.txt", "w");

    int n, m;
    Point start, end;
    Point maze[MAX_SIZE][MAX_SIZE];

    fscanf(fp, "%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(fp, "%d", &maze[i][j].accessible);
            maze[i][j].x = i;
            maze[i][j].y = j;
        }
    }

    fscanf(fp, "%d %d", &start.x, &start.y);
    fscanf(fp, "%d %d", &end.x, &end.y);

    start.accessible = maze[start.x][start.y].accessible;
    end.accessible = maze[end.x][end.y].accessible;

    int visited[MAX_SIZE][MAX_SIZE] = {0};
    Point path[MAX_CELLS];
    Point shortest_path[MAX_CELLS];
    int path_count = 0;
    int shortest_len = 0;

    fprintf(fp_out, "从入口到出口的所有简单路径：\n\n");
    find_all_paths(maze, n, m, start, end, visited, path, 0,
                   &path_count, shortest_path, &shortest_len, fp_out);

    if (path_count == 0) {
        fprintf(fp_out, "入口到出口不可达\n");
    } else {
        fprintf(fp_out, "步数最少的简单路径：\n");
        print_path(fp_out, shortest_path, shortest_len);
        fprintf(fp_out, "最少步数：%d\n", shortest_len - 1);
    }

    fclose(fp);
    fclose(fp_out);
    return 0;
}
