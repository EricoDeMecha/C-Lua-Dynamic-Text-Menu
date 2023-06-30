//
// Created by koech on 6/15/2023.
//
#include "utils.h"

void printInt(void* value){
    printf("%d", ((int*)value));
}
void printChar(void* value){
    printf("%c", (char*)value);
}
void printPairInts(void* value){
    Pair* temp = (Pair*)value;
    printf("{%d, %d}", (int*)temp->first, (int*)temp->second);
}

void printPairFloats(void* value){
    Pair* temp = (Pair*)value;
    printf("{%f, %f}", (float*)temp->first, (float*)temp->second);
}
void printPairChars(void* value){
    Pair* temp = (Pair*)value;
    printf("{%f, %f}", (char*)temp->first, (char*)temp->second);
}

char* concatenateStrings(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t resultLen = len1 + len2 + 1;  // +1 for null terminator

    char* result = (char*)malloc(resultLen * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    strcpy(result, str1);
    strcat(result, str2);

    return result;
}

char* normalize_path(const char* path) {
    if (path == NULL) return NULL;

    size_t len = strlen(path);
    char* normalized = (char*)malloc((len + 1) * sizeof(char));
    if (normalized == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    strcpy(normalized, path);

#ifdef _WIN32
    // Replace forward slashes with backslashes
    for (size_t i = 0; i < len; ++i) {
        if (normalized[i] == '/') {
            normalized[i] = '\\';
        }
    }
#else
    // Replace backslashes with forward slashes
    for (size_t i = 0; i < len; ++i) {
        if (normalized[i] == '\\') {
            normalized[i] = '/';
        }
    }
#endif

#ifdef _WIN32
    // Check if the executable is located in a different directory
    char exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, MAX_PATH);
    char* exeDir = strrchr(exePath, '\\');
    if (exeDir != NULL) {
        *exeDir = '\0';
        char* temp = normalized;
        size_t exeDirLen = strlen(exePath);
        normalized = (char*)malloc((len + exeDirLen + 2) * sizeof(char));
        if (normalized == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free(temp);
            return NULL;
        }
        strcpy(normalized, exePath);
        strcat(normalized, "\\");
        strcat(normalized, temp);
        free(temp);
    }
#else
    // Check if the executable is located in a different directory
    char exePath[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", exePath, sizeof(exePath));
    if (count != -1) {
        exePath[count] = '\0';
        char* exeDir = strrchr(exePath, '/');
        if (exeDir != NULL) {
            *exeDir = '\0';
            char* temp = normalized;
            size_t exeDirLen = strlen(exePath);
            normalized = (char*)malloc((len + exeDirLen + 2) * sizeof(char));
            if (normalized == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free(temp);
                return NULL;
            }
            strcpy(normalized, exePath);
            strcat(normalized, "/");
            strcat(normalized, temp);
            free(temp);
        }
    }
#endif

    return normalized;
}