//单源最短路径Dijkstra
#include <stdio.h>
#include <stdlib.h>
#define INF 2147483647
#define MAX_VERTICES 100
typedef struct {
    int Vernum;
    int Edgenum;
    int arcs[MAX_VERTICES][MAX_VERTICES];
} Graph;
void Dijkstra(Graph* G, int start, FILE* fp_out) {
    int S[MAX_VERTICES] = {0}; //已确定最短路径的顶点集合
    int dist[MAX_VERTICES]; //起点到各顶点的最短路径长度
    int Path[MAX_VERTICES]; //各顶点的前驱顶点
    for (int i = 0; i < G->Vernum; i++) {
        dist[i] = G->arcs[start][i];
        if (dist[i] < INF) {
            Path[i] = start;
        } else {
            Path[i] = -1; //无路径
        }
    }
    S[start] = 1; //起点加入集合S
    dist[start] = 0;
    for (int i = 1; i < G->Vernum; i++) {
        int minDist = INF;
        int u = -1;
        for (int j = 0; j < G->Vernum; j++) {
            if (!S[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }
        if (u == -1) break; //所有可达顶点已加入集合S
        S[u] = 1; //将u加入集合S
        for (int v = 0; v < G->Vernum; v++) {
            if (!S[v] && G->arcs[u][v] < INF) {
                if (dist[u] + G->arcs[u][v] < dist[v]) {
                    dist[v] = dist[u] + G->arcs[u][v];
                    Path[v] = u;
                }
            }
        }
    }
    for (int i = 0; i < G->Vernum; i++){
        fprintf(fp_out, "%d\t%d\t", i, dist[i]);
        fprintf(fp_out, "\n");
    }

}
int main(){
    FILE* fp = fopen("lab5_1_data.txt", "r");
    FILE* fp_out = fopen("lab5_1_output.txt", "w");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }
    Graph G;
    int startVer;
    fscanf(fp, "%d", &G.Vernum);
    fscanf(fp, "%d", &G.Edgenum);
    fscanf(fp, "%d", &startVer);
    for (int i = 0; i < G.Vernum; i++) {
        for (int j = 0; j < G.Vernum; j++) {
            G.arcs[i][j] = INF;
        }
    }
    for (int i = 0; i < G.Edgenum; i++) {
        int u, v, w;
        fscanf(fp, "%d %d %d", &u, &v, &w);
        G.arcs[u][v] = w;
    }
    Dijkstra(&G, startVer, fp_out);
    fclose(fp);
    fclose(fp_out);
    return 0;
}