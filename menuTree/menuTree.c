//
// Created by koech on 6/26/2023.
//
#include "menuTree.h"

MenuTree* createMenuTree() {
    MenuTree* menuTree = (MenuTree*)malloc(sizeof(MenuTree));
    menuTree->root = NULL;
    return menuTree;
}

void destroyMenuTreeHelper(MenuItem* menuItem) {
    if (menuItem == NULL)
        return;

    MenuItem* child = menuItem->children;
    while (child != NULL) {
        MenuItem* nextChild = child->next;
        destroyMenuTreeHelper(child);
        child = nextChild;
    }

    free(menuItem);
}

void destroyMenuTree(MenuTree* menuTree) {
    destroyMenuTreeHelper(menuTree->root);
    free(menuTree);
}

MenuItem* createMenuItem(int id, const char* label, const char* program) {
    MenuItem* menuItem = (MenuItem*)malloc(sizeof(MenuItem));
    menuItem->id = id;
    strncpy(menuItem->label, label, sizeof(menuItem->label) - 1);
    strncpy(menuItem->program, program, sizeof(menuItem->program) - 1);
    menuItem->parent = NULL;
    menuItem->children = NULL;
    menuItem->next = NULL;
    return menuItem;
}

void addMenuItem(MenuTree* menuTree, int id, const char* label, const char* program, int parentID) {
    MenuItem* menuItem = createMenuItem(id, label, program);

    if (menuTree->root == NULL) {
        menuTree->root = menuItem;
    } else {
        MenuItem* parentItem = findMenuItem(menuTree, parentID);
        if (parentItem != NULL) {
            menuItem->parent = parentItem;
            if (parentItem->children == NULL) {
                parentItem->children = menuItem;
            } else {
                MenuItem* sibling = parentItem->children;
                while (sibling->next != NULL)
                    sibling = sibling->next;
                sibling->next = menuItem;
            }
        } else {
            // Handle error: parentID not found
            free(menuItem);
            return;
        }
    }
}

MenuItem* findMenuItemHelper(MenuItem* menuItem, int id) {
    if (menuItem == NULL)
        return NULL;

    if (menuItem->id == id)
        return menuItem;

    MenuItem* child = menuItem->children;
    while (child != NULL) {
        MenuItem* foundItem = findMenuItemHelper(child, id);
        if (foundItem != NULL)
            return foundItem;
        child = child->next;
    }

    return NULL;
}

MenuItem* findMenuItem(MenuTree* menuTree, int id) {
    return findMenuItemHelper(menuTree->root, id);
}

void traverseMenuHelper(MenuItem* menuItem) {
    if (menuItem == NULL)
        return;

    printf("ID: %d, Label: %s, Program: %s\n", menuItem->id, menuItem->label, menuItem->program);

    MenuItem* child = menuItem->children;
    while (child != NULL) {
        traverseMenuHelper(child);
        child = child->next;
    }
}

void traverseMenu(MenuTree* menuTree) {
    traverseMenuHelper(menuTree->root);
}