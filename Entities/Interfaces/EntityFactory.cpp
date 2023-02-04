#include "EntityFactory.hpp"

int EntityFactory::m_memoryPool[MEMORY_POOL_SIZE];
vector<pair<int,int>> EntityFactory::m_allocationTable;