//
// Created by koech on 6/26/2023.
//

#include <sqlite3.h>
#include <time.h>
#include <lua.h>
#include <lualib.h>
#include <luaconf.h>
#include <lauxlib.h>
#include "menuTree/menuTree.h"
#include "utils.h"

void populateDatabaseWithRandomMenu(sqlite3* db, int numItems) {
    // Create the menu_items table
    const char* createTableSQL = "CREATE TABLE IF NOT EXISTS menu_items (id INT PRIMARY KEY, label TEXT, program TEXT, parent_id INT)";
    int rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Generate and insert random menu items
    sqlite3_exec(db, "BEGIN TRANSACTION", 0, 0, 0);  // Begin transaction for faster inserts
    sqlite3_stmt* stmt;

    const char* insertSQL = "INSERT INTO menu_items (id, label, program, parent_id) VALUES (?, ?, ?, ?)";
    rc = sqlite3_prepare_v2(db, insertSQL, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare SQL statement: %s\n", sqlite3_errmsg(db));
        sqlite3_exec(db, "ROLLBACK", 0, 0, 0);  // Rollback transaction
        return;
    }

    srand(time(NULL));  // Seed the random number generator

    for (int i = 1; i <= numItems; i++) {
        int id = i;
        char label[256];
        char program[256];
        int parentId = (i == 1) ? 0 : (rand() % (i - 1)) + 1;  // Randomly choose a parent ID

        snprintf(label, sizeof(label), "Menu %d", id);
        snprintf(program, sizeof(program), "program%d", id);

        sqlite3_reset(stmt);
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_bind_text(stmt, 2, label, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, program, -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 4, parentId);

        rc = sqlite3_step(stmt);
        if (rc != SQLITE_DONE) {
            fprintf(stderr, "Failed to execute SQL statement: %s\n", sqlite3_errmsg(db));
            sqlite3_exec(db, "ROLLBACK", 0, 0, 0);  // Rollback transaction
            sqlite3_finalize(stmt);
            return;
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT", 0, 0, 0);  // Commit transaction
    printf("Random menu items inserted successfully.\n");
}

void loadMenuTree(MenuTree* menuTree, sqlite3* db) {
    sqlite3_stmt *stmt;
    int rc;

    const char *sql = "SELECT id, label, program, parent_id FROM menu_items";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare SQL statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* label = (const char*)sqlite3_column_text(stmt, 1);
        const char* program = (const char*)sqlite3_column_text(stmt, 2);
        int parentID = sqlite3_column_int(stmt, 3);

        addMenuItem(menuTree, id, label, program, parentID);
    }

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to execute SQL statement: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
}


int main() {
    sqlite3 *db;
    char *errMsg = 0;

    int rc = sqlite3_open("file.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }
//    populateDatabaseWithRandomMenu(db, 30);
   /**************************CREATE TABLE*****************************************/
    // Create the menu_items table
    const char *sql = "CREATE TABLE IF NOT EXISTS menu_items (id INT PRIMARY KEY, label TEXT, program TEXT, parent_id INT)";
    rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return rc;
    }

    // Insert menu items into the table
    sql = "INSERT INTO menu_items (id, label, program, parent_id) VALUES "
          "(1, 'Menu 1', 'program1', 0), "
          "(2, 'Submenu 1.1', 'program2', 1), "
          "(3, 'Submenu 1.2', 'program3', 1), "
          "(4, 'Menu 2', 'program4', 0)"
          ;
    rc = sqlite3_exec(db, sql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Menu items inserted successfully.\n");
    }
   /***************************END CREATE TABLE******************************************/

    /***************************LOAD TABLE******************************************/

    // Create the menu tree
    MenuTree* menuTree = createMenuTree("Menu");

    // Load menu items from the database into the menu tree
    loadMenuTree(menuTree, db);

    // Traverse the menu tree to verify the loaded menu items
    traverseMenu(menuTree);
    // navigate menu manually
    navigateMenu(menuTree);

    // find menu item
    MenuItem* foundItem = findMenuItem(menuTree, 1);
    if (foundItem != NULL) {
        printf("Found menu item: ID: %d, Label: %s, Program: %s\n", foundItem->id, foundItem->label, foundItem->program);
    } else {
        printf("Menu item not found.\n");
    }
    // execute a lua script for the selected program
    lua_State *L = luaL_newstate();

    // Load Lua libraries
    luaL_openlibs(L);

    char* temp_script_path = concatenateStrings("../luas/",concatenateStrings(foundItem->program, ".lua"));
    char* script_path = normalize_path(temp_script_path);
    // Load and execute a Lua script
    if (luaL_dofile(L, script_path) != LUA_OK) {
        printf("Failed to load and execute Lua script: %s\n", lua_tostring(L, -1));
        lua_close(L);
        return 1;
    }

    // Clean up Lua state
    lua_close(L);

    /* TODO
     * - load a program from the selected menu item
     *  * - Dynamic Loading or
     *  * - Loading a python script or
     *  * - Loading a lua script
     *  */

    /***************************END LOAD TABLE******************************************/

    // Close the database and free memory
    sqlite3_close(db);
    destroyMenuTree(menuTree);
    return 0;
}
