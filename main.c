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

