/*
 * Header file for a cache implementatiion
 * CSF Assignment 3
 * Edward Wang: ewang43@jhu.edu
 * Sam Chordia: schordi1@jhu.edu
 */

#ifndef CACHE_H
#define CACHE_H

#include <vector>
#include <string>

class Cache
{
private:
    struct Block
    {
        unsigned int tag;
        unsigned int loadTimestamp;
        unsigned int accessTimestamp;
        bool valid;
        bool dirty;
    };

    struct Set
    {
        std::vector<Block> blocks;
    };

    std::string writeAllocate;
    std::string writeThrough;
    std::string replacementPolicy;

    unsigned int blockSize;    // num of bytes in the block
    unsigned int numSets;      // number of different offsets
    unsigned int blocksPerSet; // how many blocks in each offset

    unsigned int loadHits;
    unsigned int loadMisses;
    unsigned int storeHits;
    unsigned int storeMisses;
    unsigned int totalCycles;

    unsigned int currentTimestamp;

    std::vector<Set> sets;

    /*
     * Get the pointer to a block with the given address
     *
     * Parameters:
     *     index - an unsigned int with the index of the address
     *     tag - an unsigned int with the tag of the address
     * Returns:
     *     a pointer to the Block with the corresponding address. return a null pointer if the Block isn't found
     */
    Block *getBlock(unsigned int index, unsigned int tag);

    /*
     * Get the pointer to a block to be evicted
     * 
     * Parameters:
     *     index - an unsigned int with the index of the address which gives us the set to evict from
     * Returns:
     *     a pointer to the Block to be evicted or overwritten
     */
    Block *getBlockToBeEvicted(unsigned int index);
public:
    /*
     * Construct a cache using the given parameters.
     *
     * Parameters:
     *     sets - an unsigned int representing the number of sets in the cache (each offset corresponds to one set)
     *     blocks - an unsigned int representing the number of blocks contained in each set
     *     bytes - an unsigned int representing the number of bytes contained in each block
     *     writeAllocate - a string representing the policy taken when a store miss occurs (write-allocate, no-write-allocate)
     *     writeThrough - a string representing the policy taken when performing a store (write-through, write-back)
     *     replacementPolicy - a string representing the policy taken when a block needs to be evicted (fifo, lru)
     */
    Cache(unsigned int sets, unsigned int blocks, unsigned int bytes,
          std::string writeAllocate, std::string writeThrough, std::string replacementPolicy);

    /*
     * Get the number of load hits in the cache
     *
     * Returns:
     *     an unsigned integer representing the number of load hits
     */
    unsigned int getLoadHits() const;

    /*
     * Get the number of load misses in the cache
     *
     * Returns:
     *     an unsigned integer representing the number of load misses
     */
    unsigned int getLoadMisses() const;

    /*
     * Get the total number of loads in the cache
     *
     * Returns:
     *     an unsigned integer representing the number of total loads
     */
    unsigned int getTotalLoads() const;

    /*
     * Get the total number of store hits in the cache
     *
     * Returns:
     *     an unsigned integer representing the number of store hits
     */
    unsigned int getStoreHits() const;

    /*
     * Get the total number of store misses in the cache
     *
     * Returns:
     *     an unsigned integer representing the total number of store hits
     */
    unsigned int getStoreMisses() const;

    /*
     * Get the total number of stores in the cache
     *
     * Returns:
     *     an unsigned integer representing the total number of stores
     */
    unsigned int getTotalStores() const;

    /*
     * Get the total number of cycles taken by the cache
     * Returns:
     *     an unsigned integer representing the total number of cycles
     */
    unsigned int getTotalCycles() const;

    /*
     * Given an address, perform a store at that address in accordance to the cache policies,
     * updating the counts for store hits, store misses, and total cycles
     *
     * Parameters:
     *     address - an unsigned int representing the memory address being stored to
     */
    void store(unsigned int address);

    /*
     * Given an address, perform a load at that address, updating the counts for load hits,
     * load misses, and total cycles
     *
     * Parameters:
     *     address - an unsigned int representing the memory address being loaded
     */
    void load(unsigned int address);

    unsigned int uintLog2(unsigned int x);
};

#endif
