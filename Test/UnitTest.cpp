#include "EntityFactory.hpp"

void TestEntityFactory()
{
    DEBUG_DUMP_VAR(*EntityFactory::GetInstance()->getEntity(1).get());
    DEBUG_DUMP_VAR(*EntityFactory::GetInstance()->getEntity(2).get());
    DEBUG_DUMP_VAR(*EntityFactory::GetInstance()->getEntity(3).get());
}

void TestInventory()
{

}

int main(int argc, char **argv)
{
    TestEntityFactory();
    TestInventory();
    return 0;
}