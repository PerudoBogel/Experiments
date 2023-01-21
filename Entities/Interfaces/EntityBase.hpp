#pragma once 

class EntityBase
{
public:
    EntityBase():m_pObj(this){};
    EntityBase(void* pObj):m_pObj(pObj){}
    virtual ~EntityBase(){}

    inline bool operator==(const EntityBase &attackModel){
        return m_pObj == attackModel.m_pObj;
    }
    inline bool ifValid(){return m_pObj != nullptr;}
    
private:
    void *m_pObj = nullptr;
};