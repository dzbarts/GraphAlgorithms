#include <stdio.h>
#include <stdlib.h>

// Структура для представления каждого звена графа
struct node {
    int d; // вес
    int c; // 1-красный, 0-черный
    struct node* p; // родитель
    struct node* r; // правый ребенок
    struct node* l; // левый ребенок
};

// глобальный корень
struct node* root = NULL;

// функция для вствки бинарного дерева поиска
struct node* bst(struct node* trav,
                 struct node* temp)
{
    // если дерево пустое, возвращает новое звено
    if (trav == NULL)
        return temp;

    // иначе спускается по дереву вниз
    if (temp->d < trav->d)
    {
        trav->l = bst(trav->l, temp);
        trav->l->p = trav;
    }
    else if (temp->d > trav->d)
    {
        trav->r = bst(trav->r, temp);
        trav->r->p = trav;
    }

    // Возвращает указатель узла
    return trav;
}

// функция разворота по часовой
void rightrotate(struct node* temp)
{
    struct node* left = temp->l;
    temp->l = left->r;
    if (temp->l)
        temp->l->p = temp;
    left->p = temp->p;
    if (!temp->p)
        root = left;
    else if (temp == temp->p->l)
        temp->p->l = left;
    else
        temp->p->r = left;
    left->r = temp;
    temp->p = left;
}

// функция для разворота против часовой
void leftrotate(struct node* temp)
{
    struct node* right = temp->r;
    temp->r = right->l;
    if (temp->r)
        temp->r->p = temp;
    right->p = temp->p;
    if (!temp->p)
        root = right;
    else if (temp == temp->p->l)
        temp->p->l = right;
    else
        temp->p->r = right;
    right->l = temp;
    temp->p = right;
}

// балансировка
void fixup(struct node* root, struct node* pt)
{
    struct node* parent_pt = NULL;
    struct node* grand_parent_pt = NULL;

    while ((pt != root) && (pt->c != 0)
           && (pt->p->c == 1))
    {
        parent_pt = pt->p;
        grand_parent_pt = pt->p->p;

        /* Case : A
            родитель - левый ребенок грендов */
        if (parent_pt == grand_parent_pt->l)
        {

            struct node* uncle_pt = grand_parent_pt->r;

            /* Case : 1
                дядя - красный
                необходимо лишь перекрасить
            */
            if (uncle_pt != NULL && uncle_pt->c == 1)
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }

            else {

                /* Case : 2
                    родитель - правый ребенок грендов
                    необходим поворот против часовой
                 */
                if (pt == parent_pt->r) {
                    leftrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }

                /* Case : 3
                    родитель - левый ребенок грендов
                    необходим поворот по часовой
                 */
                rightrotate(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }

            /* Case : B
                родитель - правый ребенок грендов
                */
        else {
            struct node* uncle_pt = grand_parent_pt->l;

            /* Case : 1
                дядя - красный
                необходимо лишь перекрасить
                */
            if ((uncle_pt != NULL) && (uncle_pt->c == 1))
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }
            else {
                /* Case : 2
                    родитель - левый ребенок грендов
                    необходим поворот по часовой
                 */
                if (pt == parent_pt->l) {
                    rightrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }

                /* Case : 3
                    родитель - правый ребенок грендов
                    необходим поворот против часовой
                 */
                leftrotate(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }
    }

    root->c = 0;
}

// Функция для печати неупорядоченного обхода сбалансированного дерева
void inorder(struct node* trav)
{
    if (trav == NULL)
        return;
    inorder(trav->l);
    printf("%d ", trav->d);
    inorder(trav->r);
}

// итоговая функция
int RBTree()
{
    int n = 7;
    int a[7] = { 7, 5, 20, 4, 117, 2, 22 };

    for (int i = 0; i < n; i++) {

        // выделение памяти и инициализация
        // 1. по умолчанию увет красный
        // 2. родители и указатели NULL
        // 3. вес берется соответственно из массива
        struct node* temp
                = (struct node*)malloc(sizeof(struct node));
        temp->r = NULL;
        temp->l = NULL;
        temp->p = NULL;
        temp->d = a[i];
        temp->c = 1;

        // создание дерева
        root = bst(root, temp);

        // балансировка
        fixup(root, temp);
    }

    printf("Упорядоченное сбалансированное дерево\n");
    inorder(root);

    return 0;
}


#include <limits.h>
#include <stdbool.h>

// Количество вершин в графе
#define V 9

// Вспомогательная функция для поиска вершины с минимальным значением расстояния из набора вершин,
// еще не включенных в дерево кратчайших путей.
int minDistance(int dist[], bool sptSet[])
{
    // Инициализация минимального значения
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Вспомогательная функция для печати построенного массива расстояний
void printSolution(int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Функция, которая реализует алгоритм кратчайшего пути Дейкстры с одним источником для графа,
// представленного с использованием представления матрицы смежности.
void dijkstra(int graph[V][V], int src)
{
    int dist[V];
    // Выходной массив. dist[i] будет содержать кратчайшее расстояние от src до i

    bool sptSet[V];
    // sptSet[i] будет истинным, если вершина i включена в дерево кратчайших путей
    // или кратчайшее расстояние от src до i завершено

    // Инициализация всего расстояния как INFINITE и stpSet[] как false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Расстояние исходной вершины от самой себя всегда равно 0
    dist[src] = 0;

    // Поиск кратчайшего пути для всех вершин
    for (int count = 0; count < V - 1; count++) {
        // Выбирается вершина минимального расстояния из набора еще не обработанных вершин. u всегда равно src в первой итерации.
        int u = minDistance(dist, sptSet);

        // Отмечаем выбранную вершину как пройденную
        sptSet[u] = true;

        // Обновление значений расстояний смежных вершин выбранной вершины.
        for (int v = 0; v < V; v++)

            // Необходимо обновлять dist[v] только в том случае, если его нет в sptSet,
            // есть ребро от u до v и общий вес пути от src до v через u меньше текущего значения dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // печать итога
    printSolution(dist);
}

// итоговая функция с тестовым набором
int Dijkstra()
{
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    dijkstra(graph, 0);

    return 0;
}
