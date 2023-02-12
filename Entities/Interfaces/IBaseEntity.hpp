#pragma once

class IBaseEntity
{
public:
    bool operator==(IBaseEntity &ibaseEntity)
    {
        return m_pEntity==ibaseEntity.m_pEntity;
    }

    void* m_pEntity;
};