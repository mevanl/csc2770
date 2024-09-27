#include "malloc_functions.h"


bool validate_size(size_t size, size_t MEMORY_SIZE)
{
    // check if size is too big
    if (size > MEMORY_SIZE) 
    {
        printf("Can not allocate more than total memory");
        return false;
    }
    // check if size is too small
    if (size <= 0)
    {
        printf("Can not allocate 0 or negative amounts of memory");
        return false;
    }  

    return true;
}