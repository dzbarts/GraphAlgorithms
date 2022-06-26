#include <stdio.h>
#include <stdlib.h>

//структура графа в виде матрицы инцидентности
typedef struct mgraph{
    int n;
    int *address;
}mgraph;

//функция инициализации графа
mgraph *minit(int n){
    mgraph *new_graph= malloc(sizeof(mgraph));
    new_graph->n=n;
    int *address = malloc(n*n*sizeof(int));
    int i;
    for(i=0;i<n*n;i++) address[i]=0;
    new_graph->address=address;
    return new_graph;
}

//функция добавления ребра в графе
void madd_edge(mgraph *g, int from, int to){
    if (from>=g->n||to>=g->n) return;
    int n1=g->n*from+to;
    int n2=g->n*to+from;
    int *add=g->address;
    add[n1]=1;
    add[n2]=1;
}

//функция удаления ребра в графе
void mdel_edge(mgraph *g, int from, int to){
    if (from>=g->n||to>=g->n) return;
    int n1=g->n*from+to;
    int n2=g->n*to+from;
    int *add =g->address;
    add[n1]=0;
    add[n2]=0;
}

//функция получения степени вершины графа
int power(mgraph *g, int v){
    int n=g->n;
    int *add=g->address;
    int i;
    int p=0;
    for(i=0;i<n;i++) p=p+add[v*n+i];
    return p;
}

//функция печати графа на экран
void print_gr(mgraph *g){
    unsigned int n = g->n;
    int i;
    printf("  ");
    for (i=0; i<n; i++) printf("%d ",i);
    printf("\n0 ");
    for(i=0; i<n*n; i++){
        printf("%d ", g->address[i]);
        if ((i+1)%n==0) {
            printf("\n");
            if (i != n * n - 1) printf("%d ", (i + 1) / n);
        }
    }
}

