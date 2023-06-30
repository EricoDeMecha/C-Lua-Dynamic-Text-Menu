//
// Created by koech on 6/26/2023.
//
#include "menuTree.h"

MenuTree *createMenuTree(const char *rootLabel) {
    MenuTree *menuTree = (MenuTree *) malloc(sizeof(MenuTree));
    menuTree->root = createMenuItem(0, rootLabel, "");
    return menuTree;
}


void destroyMenuTreeHelper(MenuItem *menuItem) {
    if (menuItem == NULL)
        return;

    MenuItem *child = menuItem->children;
    while (child != NULL) {
        MenuItem *nextChild = child->next;
        destroyMenuTreeHelper(child);
        child = nextChild;
    }

    free(menuItem);
}

void destroyMenuTree(MenuTree *menuTree) {
    destroyMenuTreeHelper(menuTree->root);
    free(menuTree);
}

MenuItem *createMenuItem(int id, const char *label, const char *program) {
    MenuItem *menuItem = (MenuItem *) malloc(sizeof(MenuItem));
    menuItem->id = id;
    strncpy(menuItem->label, label, sizeof(menuItem->label) - 1);
    strncpy(menuItem->program, program, sizeof(menuItem->program) - 1);
    menuItem->parent = NULL;
    menuItem->children = NULL;
    menuItem->next = NULL;
    return menuItem;
}

void addMenuItem(MenuTree *menuTree, int id, const char *label, const char *program, int parentID) {
    MenuItem *menuItem = createMenuItem(id, label, program);

    if (menuTree->root == NULL) {
        menuTree->root = menuItem;
    } else {
        MenuItem *parentItem = findMenuItem(menuTree, parentID);
        if (parentItem != NULL) {
            menuItem->parent = parentItem;
            if (parentItem->children == NULL) {
                parentItem->children = menuItem;
            } else {
                MenuItem *sibling = parentItem->children;
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

MenuItem *findMenuItemHelper(MenuItem *menuItem, int id) {
    if (menuItem == NULL)
        return NULL;

    if (menuItem->id == id)
        return menuItem;

    MenuItem *child = menuItem->children;
    while (child != NULL) {
        MenuItem *foundItem = findMenuItemHelper(child, id);
        if (foundItem != NULL)
            return foundItem;
        child = child->next;
    }

    return NULL;
}

MenuItem *findMenuItem(MenuTree *menuTree, int id) {
    return findMenuItemHelper(menuTree->root, id);
}

void traverseMenuHelper(MenuItem *menuItem, int depth) {
    if (menuItem == NULL)
        return;

    for (int i = 0; i < depth; i++)
        printf("  ");

    printf("%d. %s\n", menuItem->id, menuItem->label);

    MenuItem *child = menuItem->children;
    while (child != NULL) {
        traverseMenuHelper(child, depth + 1);
        child = child->next;
    }
}

void traverseMenu(MenuTree *menuTree) {
    traverseMenuHelper(menuTree->root, 0);
}

void navigateMenu(MenuTree *menuTree) {
    MenuItem *previousMenu = NULL;

    while (1) {
        printf("Available Options:\n");
        MenuItem *mainMenu = menuTree->root;
        printf("Menu: %s \n", mainMenu->label);
        int optionCount = 1;
        while (mainMenu != NULL) {
            printf("%d. %s\n", optionCount, mainMenu->label);
            mainMenu = mainMenu->next;
            optionCount++;
        }
        printf("%d. Exit\n", optionCount);

        if (previousMenu != NULL) {
            printf("%d. Go back to the previous menu\n", optionCount + 1);
        }

        int selectedOption;
        printf("\nSelect > ");
        scanf("%d", &selectedOption);

        if (selectedOption >= 1 && selectedOption <= optionCount - 1) {
            mainMenu = menuTree->root;
            int mainMenuOption = 1;
            while (mainMenuOption < selectedOption && mainMenu != NULL) {
                mainMenu = mainMenu->next;
                mainMenuOption++;
            }
            MenuItem *currentMenu = mainMenu;

            while (1) {
                printf("\nCurrent Menu: %s\n", currentMenu->label);
                printf("Available Options:\n");
                MenuItem *child = currentMenu->children;
                int childOptionCount = 1;
                while (child != NULL) {
                    printf("%d. %s\n", childOptionCount, child->label);
                    child = child->next;
                    childOptionCount++;
                }
                if (previousMenu != NULL) {
                    printf("%d. Go back to the previous menu\n", childOptionCount);
                }
                printf("%d. Go back to the main menu\n", childOptionCount + 1);
                printf("%d. Exit\n", childOptionCount + 2);

                printf("\nSelect > ");
                scanf("%d", &selectedOption);

                if (selectedOption >= 1 && selectedOption <= childOptionCount) {
                    if (selectedOption == childOptionCount) {
                        if (previousMenu != NULL) {
                            currentMenu = previousMenu;
                            previousMenu = NULL;
                        } else {
                            printf("Invalid option. Cannot go back further.\n");
                        }
                    } else {
                        child = currentMenu->children;
                        int childOption = 1;
                        while (childOption < selectedOption && child != NULL) {
                            child = child->next;
                            childOption++;
                        }
                        previousMenu = currentMenu;
                        currentMenu = child;
                    }
                } else if (selectedOption == childOptionCount + 1) {
                    previousMenu = NULL;
                    break;
                } else if (selectedOption == childOptionCount + 2) {
                    return;
                } else {
                    printf("Invalid option. Please try again.\n");
                }
            }
        } else if (selectedOption == optionCount) {
            return;
        } else if (selectedOption == optionCount + 1) {
            if (previousMenu != NULL) {
                MenuItem *currentMenu = previousMenu;
                previousMenu = NULL;

                printf("\nCurrent Menu: %s\n", currentMenu->label);
                printf("Available Options:\n");
                MenuItem *child = currentMenu->children;
                int childOptionCount = 1;
                while (child != NULL) {
                    printf("%d. %s\n", childOptionCount, child->label);
                    child = child->next;
                    childOptionCount++;
                }
                if (previousMenu != NULL) {
                    printf("%d. Go back to the previous menu\n", childOptionCount);
                }
                printf("%d. Go back to the main menu\n", childOptionCount + 1);
                printf("%d. Exit\n", childOptionCount + 2);

                printf("\nSelect > ");
                scanf("%d", &selectedOption);

                if (selectedOption >= 1 && selectedOption <= childOptionCount) {
                    if (selectedOption == childOptionCount) {
                        if (previousMenu != NULL) {
                            currentMenu = previousMenu;
                            previousMenu = NULL;
                        } else {
                            printf("Invalid option. Cannot go back further.\n");
                        }
                    } else {
                        child = currentMenu->children;
                        int childOption = 1;
                        while (childOption < selectedOption && child != NULL) {
                            child = child->next;
                            childOption++;
                        }
                        previousMenu = currentMenu;
                        currentMenu = child;
                    }
                } else if (selectedOption == childOptionCount + 1) {
                    previousMenu = NULL;
                    break;
                } else if (selectedOption == childOptionCount + 2) {
                    return;
                } else {
                    printf("Invalid option. Please try again.\n");
                }
            }
        } else {
            printf("Invalid option. Please try again.\n");
        }
    }
}


void addMenuItemByLabel(MenuTree *menuTree, int id, const char *label, const char *program, const char *parentLabel) {
    MenuItem *menuItem = createMenuItem(id, label, program);

    if (menuTree->root == NULL) {
        menuTree->root = menuItem;
    } else {
        MenuItem *parentItem = findMenuItemByLabel(menuTree, parentLabel);
        if (parentItem != NULL) {
            menuItem->parent = parentItem;
            if (parentItem->children == NULL) {
                parentItem->children = menuItem;
            } else {
                MenuItem *sibling = parentItem->children;
                while (sibling->next != NULL)
                    sibling = sibling->next;
                sibling->next = menuItem;
            }
        } else {
            // Handle error: parent label not found
            free(menuItem);
            return;
        }
    }
}

MenuItem *findMenuItemByLabelHelper(MenuItem *menuItem, const char *label) {
    if (menuItem == NULL)
        return NULL;

    if (strcmp(menuItem->label, label) == 0)
        return menuItem;

    MenuItem *child = menuItem->children;
    while (child != NULL) {
        MenuItem *foundItem = findMenuItemByLabelHelper(child, label);
        if (foundItem != NULL)
            return foundItem;
        child = child->next;
    }

    return NULL;
}

MenuItem *findMenuItemByLabel(MenuTree *menuTree, const char *label) {
    return findMenuItemByLabelHelper(menuTree->root, label);
}



