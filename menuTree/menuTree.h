//
// Created by koech on 6/26/2023.
//

#ifndef TEST_MENUTREE_H
#define TEST_MENUTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MenuItem {
    int id;
    char label[256];
    char program[256];
    struct MenuItem* parent;
    struct MenuItem* children;
    struct MenuItem* next;
} MenuItem;

typedef struct MenuTree {
    MenuItem* root;
} MenuTree;

MenuTree* createMenuTree();
void destroyMenuTree(MenuTree* menuTree);
void addMenuItem(MenuTree* menuTree, int id, const char* label, const char* program, int parentID);
MenuItem* findMenuItem(MenuTree* menuTree, int id);
void traverseMenu(MenuTree* menuTree);

#endif //TEST_MENUTREE_H
