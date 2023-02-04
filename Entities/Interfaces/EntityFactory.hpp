#pragma once

#include "IEntity.hpp"
#include "EntityType.hpp"
#include "Debug.hpp"

#include "memory"
#include "vector"

using namespace std;

class EntityFactory
{
public:
    EntityFactory() = delete;

    template<class T>
    static shared_ptr<T> makeEntity(void)
    {
        shared_ptr<T> r_ptr;
        T* pRaw;

        auto entityIndexSize = sizeof(T) / sizeof(int) + 1;

        for(auto it = m_allocationTable.begin(); (it < m_allocationTable.end() - 1) && (m_allocationTable.size() > 1); it++)
        {
            auto nextIt = it + 1;
            auto indexesBetween = nextIt->first - it->second;
            if(indexesBetween >= entityIndexSize)
            {
                auto startIndex = it->second;
                // +1 to make sure round up
                // another +1 to point to one behind
                auto endIndex = startIndex + entityIndexSize + 2;
                m_allocationTable.insert(nextIt, pair(startIndex, endIndex));
                pRaw = reinterpret_cast<T*>(&m_memoryPool[startIndex]);
                new(pRaw) T();
                r_ptr = {pRaw,deleteEntity};
                break;
            }
        }
    
        if(!r_ptr)
        {
            auto startIndex = m_allocationTable.size() > 0 ? m_allocationTable.back().second : 0;
            auto endIndex = startIndex + entityIndexSize;
            if(endIndex <= MEMORY_POOL_SIZE)
            {
                m_allocationTable.push_back(pair(startIndex,endIndex));
                pRaw = reinterpret_cast<T*>(&m_memoryPool[startIndex]);
                new(pRaw) T();
                r_ptr = {pRaw,deleteEntity};
            }
        }
        DEBUG_DUMP_VAR(pRaw);
        return r_ptr;
    }

    static void deleteEntity(IEntity *pEntity)
    {
        DEBUG_DUMP_VAR(pEntity);
        for(auto it = m_allocationTable.begin(); it < m_allocationTable.end(); it++)
        {
            if(pEntity == reinterpret_cast<IEntity*>(&m_memoryPool[it->first]))
            {
                pEntity->~IEntity();
                m_allocationTable.erase(it);
                break;
            }
        }
    }

private:

    static const uint64_t MEMORY_POOL_SIZE = 10 * 1024 * 1024 / sizeof(int);
    static vector<pair<int,int>> m_allocationTable; // pair<beginIndex,endIndex(last+1)>
    static int m_memoryPool[];
};
