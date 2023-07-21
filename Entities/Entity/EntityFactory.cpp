#include "EntityFactory.hpp"
#include "AllocationPool.hpp"
#include "CsvReader.hpp"

// constexpr std::string_view ENTITY_INFO_FILE = "GameResources/Entities/EntitiesInfo.csv";

enum Value
{
    EntityId,
    TexId,
    CustomData,
    Health,
    IsCollidable,
    Damage,
    Attack,
    Defence,
    Range,
    MoveStrength,
    Speed,
    MemberFractions,
    AllyFractions,
    SizeW,
    SizeH,
};

std::map<int, EntityData> EntityFactory::m_entitiesInfo;
EntityFactory *EntityFactory::m_pInstance;

EntityFactory *EntityFactory::GetInstance()
{
    if(m_pInstance == nullptr)
        m_pInstance = new EntityFactory();

    return m_pInstance;
}

EntityFactory::EntityFactory()
{
    CsvReader csvReader("GameResources/Entities/EntitiesInfo.csv", 1, 1);
    csvReader.ReadFile();
    auto &content = csvReader.GetContent();

    for(auto row: content)
    {
        int colNo = 0, entityId;
        for(auto cell : row )
        {
            switch(colNo)
            {
            case Value::EntityId:
                entityId = cell;
                m_entitiesInfo.insert(std::pair(cell, EntityData()));
                break;
            case Value::TexId:
                m_entitiesInfo.at(entityId).m_textureId = static_cast<TextureId>(cell);
                break;
            case Value::CustomData:
                m_entitiesInfo.at(entityId).m_customData = cell;
                break;
            case Value::Health:
                m_entitiesInfo.at(entityId).m_health = cell;
                m_entitiesInfo.at(entityId).m_maxHealth = cell;
                m_entitiesInfo.at(entityId).m_isAlive = true;
                break;
            case Value::IsCollidable:
                m_entitiesInfo.at(entityId).m_isCollidable = static_cast<bool>(cell);
                break;
            case Value::Damage:
                m_entitiesInfo.at(entityId).m_baseDamage = cell;
                break;
            case Value::Attack:
                m_entitiesInfo.at(entityId).m_attack = cell;
                break;
            case Value::Defence:
                m_entitiesInfo.at(entityId).m_defence = cell;
                break;
            case Value::Range:
                m_entitiesInfo.at(entityId).m_range = cell;
                break;
            case Value::MoveStrength:
                m_entitiesInfo.at(entityId).m_moveStrength = cell;
                break;
            case Value::Speed:
                m_entitiesInfo.at(entityId).m_speed = cell;
                break;
            case Value::MemberFractions:
                m_entitiesInfo.at(entityId).m_memberFractions = cell;
                break;
            case Value::AllyFractions:
                m_entitiesInfo.at(entityId).m_allyFractions = cell;
                break;
            case Value::SizeW:
                m_entitiesInfo.at(entityId).m_size.w = cell;
                break;
            case Value::SizeH:
                m_entitiesInfo.at(entityId).m_size.h = cell;
                m_entitiesInfo.at(entityId).m_hitbox.update(m_entitiesInfo.at(entityId).m_size);
                break;
            default:
                break;
            }
            colNo++;
        }
    }
}

std::shared_ptr<Entity> EntityFactory::getEntity(int entityId)
{
    std::shared_ptr<Entity> rVal= nullptr;

    auto entityConfig = m_entitiesInfo.find(entityId);
    if(entityConfig != m_entitiesInfo.end())
        rVal = std::make_shared<Entity>();
        rVal->UpdateData(entityConfig->second);

    return rVal;
}