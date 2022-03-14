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

unsigned int Cache::getLoadHits() const
{
    return loadHits;
}

unsigned int Cache::getLoadMisses() const
{
    return loadMisses;
}

unsigned int Cache::getTotalLoads() const
{
    return loadHits + loadMisses;
}

unsigned int Cache::getStoreHits() const
{
    return storeHits;
}

unsigned int Cache::getStoreMisses() const
{
    return storeMisses;
}

unsigned int Cache::getTotalStores() const
{
    return storeHits + storeMisses;
}

unsigned int Cache::getTotalCycles() const
{
    return totalCycles;
}

void Cache::store(unsigned int address)
{
    unsigned int index = (address >> uintLog2(blockSize)) % uintLog2(numSets);
    unsigned int tag = address >> uintLog2(numSets);

    Block *relevantBlock = getBlock(index, tag);
    if (relevantBlock == nullptr)
    {
        ++storeMisses;
        if (writeAllocate == "write-allocate")
        {
            relevantBlock = getBlockToBeEvicted(index);
            if (relevantBlock->dirty)
            {
                totalCycles += 100 * blockSize / 4;
                relevantBlock->dirty = false;
            }
            relevantBlock->tag = tag;
            relevantBlock->loadTimestamp = currentTimestamp;
            relevantBlock->accessTimestamp = currentTimestamp;
            relevantBlock->valid = true;
        }
    }
    else
    {
        ++storeHits;
    }
    if (writeThrough == "write-through")
    {
        totalCycles += 100 * blockSize / 4;
        // Cache needs to be written to as well if the block is in the cache
        if (relevantBlock != nullptr)
        {
            ++totalCycles;
        }
    }
    else
    {
        ++totalCycles;
        relevantBlock->dirty = true;
        relevantBlock->accessTimestamp = currentTimestamp;
    }
    ++currentTimestamp;
}

void Cache::load(unsigned int address)
{
    // TODO
}

Cache::Block *Cache::getBlock(unsigned int index, unsigned int tag)
{
    for (unsigned int i = 0; i < blocksPerSet; ++i)
    {
        if (sets[index].blocks[i].tag == tag && sets[index].blocks[i].valid)
        {
            return &(sets[index].blocks[i]);
        }
    }
    return nullptr;
}

Cache::Block *Cache::getBlockToBeEvicted(unsigned index)
{
    unsigned int oldestBlockTime= currentTimestamp;
    unsigned int oldestBlockIndex;
    for (unsigned int i = 0; i < blocksPerSet; ++i)
    {
        if (!sets[index].blocks[i].valid)
        {
            return &(sets[index].blocks[i]);
        }
        if (sets[index].blocks[i].accessTimestamp < oldestBlockIndex) {
            oldestBlockTime = sets[index].blocks[i].accessTimestamp;
            oldestBlockIndex = i;
        }
    }
    // TODO: Other eviction policies
    return &(sets[index].blocks[oldestBlockIndex]);
}

unsigned int Cache::uintLog2(unsigned int x)
{
    unsigned int result = 0;
    while (x != 1)
    {
        ++result;
        x >>= 1;
    }
    return result;
}
