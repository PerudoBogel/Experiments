#include <iostream>
#include <windows.h>

#include "Map.hpp"
#include "SectorGenerator.hpp"
#include "Window2d.hpp"
#include "PlayerModelController.hpp"
#include "TemplateReader.hpp"
#include "ControllersRunner.hpp"
#include "World.hpp"
#include "Scope.hpp"
#include "ScopeDisplay.hpp"
#include "Debug.hpp"
#include "EntityFactory.hpp"

#include "FrameTick.hpp"

using namespace std;

int main(int argc, char **argv)
{
	IMoveEntity moveEntity;
	auto humanModel = EntityFactory::GetInstance()->getEntity(1);
	auto dogModel = EntityFactory::GetInstance()->getEntity(2);
	auto catModel = EntityFactory::GetInstance()->getEntity(2);
	
	Entity::getInterface(humanModel, moveEntity);
	moveEntity.m_position = Coordinates(50,50);
	moveEntity.m_hitbox.update(moveEntity.m_position);
	Entity::setInterface(humanModel, moveEntity);

	Entity::getInterface(dogModel, moveEntity);
	moveEntity.m_position = Coordinates(30*5, 30*5);
	moveEntity.m_hitbox.update(moveEntity.m_position);
	Entity::setInterface(dogModel, moveEntity);

	Entity::getInterface(catModel, moveEntity);
	moveEntity.m_position = Coordinates(40, 80);
	moveEntity.m_hitbox.update(moveEntity.m_position);
	Entity::setInterface(catModel, moveEntity);

	humanModel->UpdateController(CONTROL_PLAYER);

	auto templateGen = make_unique<TemplateReader>("GameResources/Maps/road.png");

	auto mapSectors = SectorGenerator::generateMap(templateGen->getSize(),templateGen->getTemplate());

	auto map = make_shared<Map>(templateGen->getSize(),mapSectors);

	auto world = make_shared<World>();
	world->setMap(map);
	world->setEntity(humanModel);
	world->setEntity(dogModel);
	world->setEntity(catModel);
	world->sync();

	auto scope = make_shared<Scope>(world, Coordinates(0,0));
	scope->setSize(Size(121 * ISector::m_Size.w, 81 * ISector::m_Size.h));
	scope->trace(humanModel);
	
	auto scopeDisplay = make_unique<ScopeDisplay>(scope);
	
	auto window = make_unique<Window2d>(scope->getSize());

	auto controllerRunner = make_unique<ControllersRunner>(world, scope, window.get());
	
	auto controller = static_cast<PlayerModelController*>(controllerRunner->getController(humanModel.get()).get());
	
	controller->addOffset(&scope->getOffset());

	humanModel.reset();
	dogModel.reset();
	catModel.reset();

	clock_t checkpoint;

	while (controller->IfAlive())
	{
		checkpoint = std::clock();
		scope->update();
		window->addSprites(scopeDisplay->getSprites());
		controllerRunner->Run();
		checkpoint = std::clock() - checkpoint;

		FrameTick::GetIntance()->Update((checkpoint * 1000) / CLOCKS_PER_SEC, 60);
		auto sleepTime = FrameTick::GetIntance()->GetTimeToSleep_ms();

		Sleep(sleepTime);
	}

	FrameTick::Terminate();
}
