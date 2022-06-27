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