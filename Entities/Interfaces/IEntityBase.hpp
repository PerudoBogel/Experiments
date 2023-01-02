#pragma once 

class IEntityBase
{
public:
    inline bool operator==(const IEntityBase &attackModel){
        return m_pObj == attackModel.m_pObj;
    }
    
private:
    void *m_pObj = nullptr;
};