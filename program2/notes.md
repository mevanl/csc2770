## Memory Implementation
* Look for x continuous blocks of memory
  * Bad blocks are stand in for blocks we cant use
  * Memory wraps around, so if we need 8 blocks and have 7 blocks at the end and 1 at the start, that is valid (last address + 1 = first address)

## General Notes about the Professor's code 
 ```c
  Block *freelist = (Block*)memory
  ``` 
  - This is just saying our freelist (available memory) is initialized to the start of our memory. The (Block*) is just type casting since you would not be able to assign normally. 
  - freelist is a pointer to a Block, so it is the array of blocks. 

  We will skip over the bad blocks in our memory and continue our allocation until we either:
  - Have enough for the allocation 
  - Wrap around back to the start and still do not have enough memory to allocate 

### Free List
Freelist is an array, the elements of the array are Blocks, which are nodes in the linked list. Free nodes will point to the next free node. Blocks in use and blocks that are BAD (aka can not be allocated for some reason) will not be in the linked list, but will be with the memory it self of course. Amazing article here: https://medium.com/howsofcoding/custom-memory-allocator-malloc-62d28e10bfb8

