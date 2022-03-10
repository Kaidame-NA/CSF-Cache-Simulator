#ifndef CACHE_H
#define CACHE_H

#include <vector>

class Cache {
    private:
        unsigned int blockSize; // num of bytes in the block
        unsigned int numSets; // number of different offsets
        unsigned int blocksPerSet; // how many blocks in each offset

        unsigned int loadHits;
        unsigned int loadMisses;
        unsigned int storeHits;
        unsigned int storeMisses;
        unsigned int totalCycles;

        unsigned int currentTimestamp;

        struct Block {
            unsigned int tag;
            unsigned int loadTimestamp;
            unsigned int accessTimestamp;
            bool valid;
            bool dirty;
        };

        struct Set {
            std::vector<Block> blocks;
        };
    public:
        Cache();

        unsigned int getLoadHits();
        unsigned int getLoadMisses();
        unsigned int getTotalLoads();
        unsigned int getStoreHits();
        unsigned int getStoreMisses();
        unsigned int getTotalStores();
        unsigned int getTotalCycles();

        void store(unsigned int address);
        void load(unsigned int address);
};

#endif
