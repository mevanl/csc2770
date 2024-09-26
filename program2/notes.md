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