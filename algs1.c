//#include <stdio.h>
//#include <stdlib.h>
//#include "graph.c"
//
////алгоритм поиска в глубину в графе
//void DFS(graph *g, int number){
//    graph *start=get_vertex(g,number);
//    adj_list *current;
//    if (!start->status){
//        start->status=1;
//        printf("%d ",start->number);
//        current=start->vertexes;
//        while(current){
//            DFS(g,current->vertex.number);
//            current=current->next;
//        }
//    }
//    else return;
//}
//
////алгоритм поиска в ширину в графе
//void BFS(graph *g, int number){
//    graph *start=get_vertex(g,number);
//    adj_list *current;
//    if (!start->status) {
//        start->status = 1;
//        printf("%d ", start->number);
//    }
//    current=start->vertexes;
//    while(current){
//        unsigned int n=current->vertex.number;
//        graph *address=get_vertex(g,n);
//        if(!address->status){
//            printf("%d ",n);
//            address->status=1;
//        }
//        current=current->next;
//    }
//    current=start->vertexes;
//    while(current){
//        unsigned int n=current->vertex.number;
//        BFS(g,n);
//        current=current->next;
//    }
//
//}
//
////алгоритм Белмана-Форда
//double *Belman_Ford(graph *g, int vertex){
//    adj_list *current;
//    pair p;
//    int n=0;
//    int number;
//    int curr;
//    int dist;
//    double distance;
//    graph *gr=g;
//    while(gr){
//        n++;
//        gr=gr->next;
//    }
//    double *res= malloc(n * sizeof(double));
//    int i;
//    for(i=0;i<n;i++){
//        if(i==vertex) res[i]=0;
//        else res[i]=10000;
//    }
//    adj_list *list2=NULL;
//    p.number=vertex;
//    p.distance=0;
//    list2=add(list2,p);
//    adj_list *list=list2;
//    for(i=0;i<n-1;i++){
//        list2=NULL;
//        while(list){
//            curr=list->vertex.number;
//            printf("%d ",curr);
//            current = get_vertex(g, curr)->vertexes;
//            while(current){
//                number=current->vertex.number;
//                distance=current->vertex.distance;
//                dist=res[curr]+distance;
//                if(dist<res[number]) res[number]=dist;
//                current=current->next;
//                p.number=number;
//                p.distance=0;
//                list2=add(list2,p);
//            }
//            list=list->next;
//        }
//        list=list2;
//        printf("\n");
//    }
//    return res;
//}
//
//void top_sort(graph *g, graph *start, int *res, int *n){
//    if(start->status) return;
//    start->status=1;
//    adj_list *list=start->vertexes;
//    graph *current;
//    while(list){
//        current= get_vertex(g,list->vertex.number);
//        if(!(current->status)){
//            top_sort(g,current,res,n);
//        }
//        list=list->next;
//    }
//    res[*n]=start->number;
//    *n=*n-1;
//}
//
//graph *Topological_Sort(graph *g){
//    graph *current=g;
//    int *n= malloc(sizeof(int));
//    *n=0;
//    while(current){
//        *n=*n+1;
//        current=current->next;
//    }
//    current=g;
//    int *res= malloc(*n * sizeof(int));
//    *n=*n-1;
//    int k=*n;
//    while(current){
//        top_sort(g,current,res,n);
//        current=current->next;
//    }
//    free(n);
//    int i;
//    graph *elem= malloc(sizeof(graph));
//    graph *old;
//    old= get_vertex(g,res[0]);
//    elem->is_empty=old->is_empty;
//    elem->number=old->number;
//    elem->status=old->status;
//    elem->vertexes=old->vertexes;
//    graph *ng=elem;
//    graph *new_graph=elem;
//    for(i=1;i<=k;i++){
//        elem= malloc(sizeof(graph));
//        old= get_vertex(g,res[i]);
//        elem->is_empty=old->is_empty;
//        elem->number=old->number;
//        elem->status=old->status;
//        elem->vertexes=old->vertexes;
//        ng->next=elem;
//        ng=ng->next;
//    }
//    ng->next=NULL;
//    free(res);
//    zero_status(new_graph);
//    return new_graph;
//}
//
