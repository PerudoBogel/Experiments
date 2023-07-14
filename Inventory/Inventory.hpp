#pragma once
#include "ItemBase.hpp"
#include "ItemType.hpp"

#include <memory>

struct InventoryConfig
{
    std::array<bool, ItemType::COUNT> spotEnabled;
};

class Inventory
{
public:
    Inventory(InventoryConfig &config):m_config(config){ }

    template<class T>
    void modifyModel(T &modelInterface);

    std::shared_ptr<ItemBase> getItem();

private:
    InventoryConfig m_config;
    std::map<ItemType, std::shared_ptr<ItemBase>>
};