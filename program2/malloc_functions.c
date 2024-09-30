#include "malloc_functions.h"


// returns True if not null and marked as BAD_BLOCK, else false
bool isBadBlock(void *ptr) {
    return (ptr != NULL && *(char*)ptr == BAD_BLOCK);
}