//#include <stdio.h>
//#include <stdlib.h>
//
////структура пара, в которой будет храниться номер сежной вершины и расстояние до нее
//typedef struct pair{
//    unsigned int number;
//    double distance;
//}pair;
//
////структура список смежных вершин
//typedef struct adj_list{
//    pair vertex;
//    struct adj_list *next;
//}adj_list;
//
////функция добавления элемента в список смежных вершин
//adj_list *add(adj_list *list, pair new_pair){
//    if (!list){
//        adj_list *new_list= (malloc(sizeof(adj_list)));
//        new_list->vertex=new_pair;
//        new_list->next=NULL;
//        return new_list;
//    }
//    adj_list *current=list;
//    while(current->next&&current->vertex.number!=new_pair.number) current=current->next;
//    if (current->vertex.number==new_pair.number){
//        current->vertex=new_pair;
//        return list;
//    }
//    adj_list *elem = (malloc(sizeof(adj_list)));
//    elem->vertex=new_pair;
//    elem->next=NULL;
//    current->next=elem;
//    return list;
//}
//
////функция удаления элемента из списка смежных вершин
//adj_list *del(adj_list *list, unsigned int number){
//    if (!list) return list;
//    adj_list *current=list;
//    if(list->vertex.number==number){
//        list=list->next;
//        free(current);
//        return list;
//    }
//    while(current->next&&current->next->vertex.number!=number){
//        current=current->next;
//    }
//    if (!current->next) return list;
//    adj_list *next=current->next;
//    current->next=current->next->next;
//    free(next);
//    return list;
//}
//
////функция полного удаления списка смежных вершин
//adj_list *del_list(adj_list *list){
//    if (!list) return list;
//    adj_list *current=list;
//    adj_list *next=list;
//    while(next){
//        next=next->next;
//        free(current);
//        current=next;
//    }
//    return NULL;
//}
//
////структура граф в виде списков смежности
//typedef struct graph{
//    unsigned char is_empty;//поле, позволяющее определить пустой ли граф
//    unsigned int number;//номер вершины
//    unsigned char status;//ствтус вершины
//    adj_list *vertexes;//список смежных вершин для данной вершины
//    struct graph *next;//ссылка на следующую вершину графа
//}graph;
//
////функция инициализации графа
//graph *init(){
//    graph *new_graph= (malloc(sizeof(graph)));
//    new_graph->is_empty=1;
//    new_graph->vertexes=NULL;
//    new_graph->next=NULL;
//    return new_graph;
//}
//
////функция добавления вершины в граф
//void add_vertex(graph *g, unsigned int number, unsigned char status){
//    if (g->is_empty){
//        g->is_empty=0;
//        g->number=number;
//        g->status=status;
//        return;
//    }
//    graph *current = g;
//    while(current->next&&current->number!=number) current=current->next;
//    if (current->number==number){
//        current->status=status;
//        return;
//    }
//    graph *new_g=init();
//    new_g->number=number;
//    new_g->status=status;
//    current->next=new_g;
//}
//
////функция добавления ребра в граф
//void add_edge(graph *g, unsigned int from, unsigned int to, double distance){
//    graph *current = g;
//    pair pair0;
//    pair0.number =to;
//    pair0.distance=distance;
//    if (g->is_empty) add_vertex(g,from,0);
//    while(current->number!=from&&current->next) current=current->next;
//    if (current->number!=from){
//        graph *new_g= init();
//        new_g->is_empty=0;
//        new_g->number=from;
//        new_g->status=0;
//
//        new_g->vertexes=add(new_g->vertexes, pair0);
//        current->next=new_g;
//    }
//    else current->vertexes=add(current->vertexes,pair0);
//    current=g;
//    while(current->number!=to&&current->next) current=current->next;
//    if (current->number!=to){
//        graph *new_g= init();
//        new_g->is_empty=0;
//        new_g->number=to;
//        new_g->status=0;
//        current->next=new_g;
//        return;
//    }
//}
//
//
////функция удаления ребра из графа
//void del_edge(graph *g, unsigned int from, unsigned int to){
//    graph *current=g;
//    while(current->next&&current->number!=from) current=current->next;
//    if (current->number!=from) return;
//    current->vertexes=del(current->vertexes, to);
//}
//
////функция удаления вершины из графа
//void del_vertex(graph *g, unsigned int number){
//    graph *current=g;
//    graph *prev=g;
//    if (g->number==number&&!g->next){
//        del_list(g->vertexes);
//        free(g);
//        g->is_empty=1;
//        g->vertexes=NULL;
//        g->next=NULL;
//        return;
//    }
//    if(g->number==number){
//        g->status=g->next->status;
//        g->number=g->next->number;
//        del_list(g->vertexes);
//        g->vertexes=g->next->vertexes;
//        prev=g->next;
//        g->next=g->next->next;
//        free(prev);
//        while(current->next){
//            current->vertexes=del(current->vertexes,number);
//            current=current->next;
//        }
//        return;
//    }
//    while(current->next&&current->number!=number){
//        prev=current;
//        current=current->next;
//    }
//    if (current->number!=number) return;
//    prev->next=current->next;
//    del_list(current->vertexes);
//    free(current);
//    current=g;
//    while(current->next){
//        current->vertexes=del(current->vertexes,number);
//        current=current->next;
//    }
//}
//
////функция печати графа на экран
//void print_graph(graph *g){
//    graph *current=g;
//    if(current->is_empty){
//        printf("Graph is empty");
//        return;
//    }
//    while(current){
//        printf("number = %d, status=%d, vertexes={" ,current->number, current->status);
//        adj_list *list=current->vertexes;
//        while(list){
//            printf("(to =%d, distance=%.2f)",list->vertex.number, list->vertex.distance);
//            if(list->next) printf(", ");
//            list=list->next;
//        }
//        printf("}\n");
//        current=current->next;
//    }
//
//}
//
////функция обнуления статуса всех вершин графа
//void zero_status(graph *g){
//    graph *current=g;
//    while (current){
//        current->status=0;
//        current=current->next;
//    }
//}
//
////функция получения адреса вершины в шрафе
//graph *get_vertex(graph *g, unsigned int number){
//    graph *current=g;
//    while(current&&current->number!=number) current=current->next;
//    return current;
//}
//
