#include "AllocationPool.hpp"

int AllocationPool::m_memoryPool[MEMORY_POOL_SIZE];
vector<pair<int,int>> AllocationPool::m_allocationTable;
int AllocationPool::allocation_counter = 0;