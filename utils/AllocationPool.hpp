#pragma once
#include "Debug.hpp"

#include "memory"
#include "vector"

using namespace std;

class AllocationPool
{
public:
    AllocationPool() = delete;

    template<class T>
    static shared_ptr<T> makeAllocation(void)
    {
        shared_ptr<T> r_ptr;
        T* pRaw;

        // +1 to make sure round up
        int entityIndexSize = sizeof(T) / sizeof(int) + 1;

        for(auto it = m_allocationTable.begin(); (it < m_allocationTable.end() - 1) && (m_allocationTable.size() > 1); it++)
        {
            auto nextIt = it + 1;
            int indexesBetween = nextIt->first - it->second;
            if(indexesBetween >= entityIndexSize)
            {
                auto startIndex = it->second;
                // another +1 to point to one behind
                auto endIndex = startIndex + entityIndexSize + 1;
                m_allocationTable.insert(nextIt, pair(startIndex, endIndex));
                pRaw = reinterpret_cast<T*>(&m_memoryPool[startIndex]);
                new(pRaw) T();
                r_ptr = {pRaw,deleteAllocation<T>};
                allocation_counter++;
                break;
            }
        }
    
        if(!r_ptr)
        {
            auto startIndex = m_allocationTable.size() > 0 ? m_allocationTable.back().second : 0;
            auto endIndex = startIndex + entityIndexSize + 1;
            if(endIndex <= MEMORY_POOL_SIZE)
            {
                m_allocationTable.push_back(pair(startIndex,endIndex));
                pRaw = reinterpret_cast<T*>(&m_memoryPool[startIndex]);
                new(pRaw) T();
                r_ptr = {pRaw,deleteAllocation<T>};
                allocation_counter++;
            }
        }
        cout<<"allocation count: "<< allocation_counter <<" new added with size: "<< entityIndexSize * sizeof(int) << endl;
        DEBUG_DUMP_VAR(pRaw);
        return r_ptr;
    }

    template<class T>
    static void deleteAllocation(T *pAllocation)
    {
        DEBUG_DUMP_VAR(pAllocation);
        for(auto it = m_allocationTable.begin(); it < m_allocationTable.end(); it++)
        {
            if(pAllocation == reinterpret_cast<T*>(&m_memoryPool[it->first]))
            {
                std::destroy_at(pAllocation);
                m_allocationTable.erase(it);
                allocation_counter--;
                break;
            }
        }
    }

private:

    static const uint64_t MEMORY_POOL_SIZE = 10 * 1024 * 1024 / sizeof(int);
    static vector<pair<int,int>> m_allocationTable; // pair<beginIndex,endIndex(last+1)>
    static int m_memoryPool[];
    static int allocation_counter;
};
