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
    // TODO 
    return 0;
}

unsigned int Cache::getLoadMisses() const {
    // TODO
    return 0;
}

unsigned int Cache::getTotalLoads() const {
    // TODO
    return 0;
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
    // TODO
    return 0;
}

void Cache::store(unsigned int address) {
    // TODO
}

void Cache::load(unsigned int address) {
    // TODO
}
