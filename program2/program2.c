#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "malloc_functions.h"

#define MEMORY_SIZE 256
#define LARGE_MEMORY_SIZE (1 * 1024 * 1024) // 1 MB
#define BAD_BLOCK 'X'

// Simulate the memory space for our allocator
static char memory[MEMORY_SIZE];

// Simulate a large memory space for testing
char *large_memory = NULL;

// Structure to manage memory blocks
typedef struct Block {
    size_t size;
    bool free;
    struct Block *next;
} Block;

Block *freeList = (Block*)memory;

// Initialize the memory manager
void initializeMemory() {
    freeList->size = MEMORY_SIZE - sizeof(Block);
    freeList->free = true;
    freeList->next = NULL;
}

// Randomly mark blocks as "bad" in the large memory
void markBadBlocks(char *memory, size_t size, size_t badBlockCount) {
    srand(time(NULL));
    for (size_t i = 0; i < badBlockCount; i++) {
        size_t randomIndex = rand() % size;
        memory[randomIndex] = BAD_BLOCK; // Mark as bad block
    }
}





// Skeleton function: Allocate memory dynamically, skipping bad blocks
void* myMalloc(size_t size) {
    // STUDENTS: Implement logic to allocate memory dynamically, ensuring that you skip over bad blocks

    // check size bounds 
    // does it need to be freeList->size ? 
    if (size == 0 || size > MEMORY_SIZE - sizeof(Block))
    {
        return NULL;
    }

    Block *current = freeList;

    while (current != NULL) 
    {

        // is this block free and big enough?
        if (current->free && current->size >= size)
        {
            bool badBlockCheck = false; 

            // find the bad blocks 
            for (size_t i = 0; i < size; i++) 
            {
                // this fun line of code here does:
                // cast the value from void * to char * since 
                // bad block is char
                //
                // then + 1 will skip the struct header info
                // then + i for incrementing 
                if (isBadBlock(((char *)(current + 1) + i)))
                {
                    badBlockCheck = true;
                    break;
                }

                // if no bad blocks 
                if (!badBlockCheck)
                {
                    // mark as used / "allocate"
                    current->free = false;

                    size_t extraSpace = current->size - size - sizeof(Block);

                    current->size = size; 

                    // if we did not use all the space for our allocation:
                    if (extraSpace > 0)
                    {
                        // create new block
                        Block *newBlock = (Block *)((char *)(current + 1) + size);
                        newBlock->size = extraSpace;
                        newBlock->free = true;
                        newBlock->next = current->next; 
                    }
                    // if we used all the space
                    else 
                    {
                        if (current->next != NULL) 
                        {
                            Block *nextBlock = current->next;
                            current->size += sizeof(Block);
                            current->next = nextBlock->next;
                        }
                    }
                    
                    // return pointer after block struct info
                    return (char *)(current + 1); 
                }
            }

            current = current->next;
        }
    }    
    
    return NULL; // Placeholder return value
}




// Skeleton function: Free the allocated memory
void myFree(void *ptr) {
    // STUDENTS: Implement logic to free the allocated memory

    // no deallocation needed
    if (ptr == NULL)
    {
        return;
    }

    // cast to block without the struct info
    Block *current = (Block *)ptr - 1; 
    // mark it free
    // data doesnt need to be removed from memory
    // just marked as can be overwritten
    current->free = true;

    // restructure the memory as one big free section 
    Block *next = current->next;
    while (next != NULL && next->free)
    {
        current->size += sizeof(Block) + next->size;
        current->next = next->next;
        next = current->next; 
    }
}




int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <size_of_allocation>\n", argv[0]);
        return 1;
    }

    // Convert the command-line argument to an integer for allocation size
    size_t allocationSize = atoi(argv[1]);

    // Initialize memory management
    initializeMemory();

    // Allocate a large memory block (1 MB)
    large_memory = (char*)malloc(LARGE_MEMORY_SIZE);
    if (large_memory == NULL) {
        printf("Failed to allocate large memory.\n");
        return 1;
    }

    // Mark some blocks as "bad"
    markBadBlocks(large_memory, LARGE_MEMORY_SIZE, 1000); // Mark 1000 bad blocks

    // Simulate memory allocation
    int *array = (int*)myMalloc(allocationSize * sizeof(int));  // Allocate memory for an array of integers
    if (array == NULL) {
        printf("Memory allocation failed.\n");
    } else {
        // Assign values to the array and print them
        for (int i = 0; i < allocationSize; i++) {
            array[i] = i * i;  // Assign square of index
            printf("Array[%d] = %d\n", i, array[i]);
        }

        // Free the allocated memory
        myFree(array);
        printf("Memory successfully freed.\n");
    }

    // Clean up large memory block using system's free function
    myFree(large_memory);

    return 0;
}