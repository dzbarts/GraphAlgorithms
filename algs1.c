#include <stdio.h>
#include <stdlib.h>
#include "graph.c"

//алгоритм поиска в глубину в графе
void DFS(graph *g, int number){
    graph *start=get_vertex(g,number);
    adj_list *current;
    if (!start->status){
        start->status=1;
        printf("%d ",start->number);
        current=start->vertexes;
        while(current){
            DFS(g,current->vertex.number);
            current=current->next;
        }
    }
    else return;
}

//алгоритм поиска в ширину в графе
void BFS(graph *g, int number){
    graph *start=get_vertex(g,number);
    adj_list *current;
    if (!start->status) {
        start->status = 1;
        printf("%d ", start->number);
    }
    current=start->vertexes;
    while(current){
        unsigned int n=current->vertex.number;
        graph *address=get_vertex(g,n);
        if(!address->status){
            printf("%d ",n);
            address->status=1;
        }
        current=current->next;
    }
    current=start->vertexes;
    while(current){
        unsigned int n=current->vertex.number;
        BFS(g,n);
        current=current->next;
    }

}

