/*
 * Implementation of the Cache class
 * CSF Assignment 3
 * Edward Wang: ewang43@jhu.edu
 * Sam Chordia: schordi1@jhu.edu
 */

#include <string>
#include "Cache.h"

using std::string;

Cache::Cache(unsigned int nSets, unsigned int blocks, unsigned int bytes, string writeAllocate, string writeThrough, string replacementPolicies)
{
    numSets = nSets;
    blocksPerSet = blocks;
    blockSize = bytes;

    this->writeAllocate = writeAllocate;
    this->writeThrough = writeThrough;
    this->replacementPolicy = replacementPolicies;

    loadHits = 0;
    loadMisses = 0;
    storeHits = 0;
    storeMisses = 0;
    totalCycles = 0;
    currentTimestamp = 0;

    for (unsigned int i = 0; i < numSets; ++i)
    {
        Set set;
        for (unsigned int j = 0; j < blocksPerSet; ++j)
        {
            Block block;
            block.tag = 0;
            block.loadTimestamp = 0;
            block.accessTimestamp = 0;
            block.valid = false;
            block.dirty = false;
            set.blocks.push_back(block);
        }
        sets.push_back(set);
    }
}

unsigned int Cache::getLoadHits() const {
    return loadHits;
}

unsigned int Cache::getLoadMisses() const {
    return loadMisses;
}

unsigned int Cache::getTotalLoads() const {
    return loadHits + loadMisses;
}

unsigned int Cache::getStoreHits() const {
    return storeHits;
}

unsigned int Cache::getStoreMisses() const {
    return storeMisses;
}

unsigned int Cache::getTotalStores() const {
    return storeHits + storeMisses;
}

unsigned int Cache::getTotalCycles() const {
    return totalCycles;
}

void Cache::store(unsigned int address) {
    unsigned int tempAddress = address;
    unsigned int index =  (tempAddress >> uintLog2(blockSize)) % uintLog2(numSets);
    unsigned int tag = tempAddress >> uintLog2(numSets);
    bool found = false;
    int blockPos;
    int emptyBlockPos = -1;
    // Loops through all the blocks in the set to check if a block with the given tag exists
    // Stores the position of the block and sets a boolean value to true if the block exists
    for (int i = 0; i < blocksPerSet; ++i) {
        if (sets[index][i].tag == tag && sets[index][i].valid) {
            found == true;
            BlockPos = i;
            break;
        }
        if (!sets[index][i].valid) {
            emptyBlockPos = i;
        }
    }
    if (!found) {
        storeMisses++;
        if (writeAllocate == "no-write-allocate") {
            totalCycles += 100;
        } else {
            totalCycles++;
            if (emptyBlockPos == -1) {
                // TODO: Eviction Code
            } else {
                sets[index][emptyBlockPos].tag = tag;
                sets[index][emptyBlockPos].valid = true;
            }
        }
    } else {
        storeHits++;
        sets[index][blockPos].tag = tag;
        if (writeThrough == "write-through") {
            totalCycles += 101;
        } else {
            totalCycles++;
            sets[index][blockPos].dirty = true;
        }
    }
}

void Cache::load(unsigned int address) {
    // TODO
}

unsigned int uintLog2(unsigned int x)
{
    unsigned int result = 0;
    while (x != 1)
    {
        ++result;
        x >>= 1;
    }
    return result;
}

