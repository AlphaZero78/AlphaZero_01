#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 100
#define MAX_EDGE 1000
#define NAME_LEN 32

typedef struct {
    char name[NAME_LEN];
} City;

typedef struct {
    int u;
    int v;
    int cost;
} Edge;

int parent[MAX_VERTEX];// 并查集父节点

int find_city(City cities[], int city_count, const char name[]) {
    for (int i = 0; i < city_count; i++) {
        if (strcmp(cities[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int get_city_id(City cities[], int *city_count, const char name[]) {
    int id = find_city(cities, *city_count, name);
    if (id != -1) {
        return id;
    }

    strcpy(cities[*city_count].name, name);
    (*city_count)++;
    return *city_count - 1;
}

void init_set(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int find_set(int x) {
    if (parent[x] != x) {
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

int union_set(int x, int y) {
    int root_x = find_set(x);
    int root_y = find_set(y);

    if (root_x == root_y) {
        return 0;
    }

    parent[root_y] = root_x;
    return 1;
}

int compare_edges(const void *a, const void *b) {
    const Edge *edge_a = (const Edge *)a;
    const Edge *edge_b = (const Edge *)b;
    return edge_a->cost - edge_b->cost;
}

int main() {
    FILE *fp = fopen("lab4_2_data.txt", "r");
    FILE *fp_out = fopen("lab4_2_output.txt", "w");

    int n, e;
    City cities[MAX_VERTEX];
    Edge edges[MAX_EDGE];
    int city_count = 0;

    fscanf(fp, "%d %d", &n, &e);

    for (int i = 0; i < e; i++) {
    char city1[NAME_LEN], city2[NAME_LEN];
    int cost;

    fscanf(fp, "%s %s %d", city1, city2, &cost);

    edges[i].u = get_city_id(cities, &city_count, city1);
    edges[i].v = get_city_id(cities, &city_count, city2);
    edges[i].cost = cost;
    }

    if (city_count < n) {
        fprintf(fp_out, "不连通\n");
        fprintf(fp_out, "无法建设覆盖所有城市的通信网络\n");
        fclose(fp);
        fclose(fp_out);
        return 0;
    }

    //kruskal算法
    qsort(edges, e, sizeof(Edge), compare_edges);
    init_set(n);

    int total_cost = 0;
    int selected_edges = 0;

    for (int i = 0; i < e && selected_edges < n - 1; i++) {
        if (union_set(edges[i].u, edges[i].v)) {
            total_cost += edges[i].cost;
            selected_edges++;
        }
    }

    if (selected_edges == n - 1) {
        fprintf(fp_out, "连通\n");
        fprintf(fp_out, "最小建设成本：%d\n", total_cost);
    } else {
        fprintf(fp_out, "不连通\n");
        fprintf(fp_out, "无法建设覆盖所有城市的通信网络\n");
    }

    fclose(fp);
    fclose(fp_out);
    return 0;
}
