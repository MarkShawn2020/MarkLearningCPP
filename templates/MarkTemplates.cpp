#include "MarkTemplates.h"

namespace mark {
    void printIntArray(int *arr, int n, const char * name) { printf("-> %10s: [", name);for(int i=0; i <= n; ++i) printf("%2d, ", arr[i]);printf("\b\b]\n"); }
    void printIdArray(int n, const char * name) { printf("-> %10s: [", name);for(int i=0; i <= n; ++i) printf("%2d, ", i);printf("\b\b]\n"); }
}
