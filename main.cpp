#include <iostream>
#include <windows.h>

#include "Map.hpp"
#include "SectorGenerator.hpp"
#include "Window2d.hpp"
#include "PlayerModelController.hpp"
#include "TemplateReader.hpp"
#include "Dog.hpp"
#include "Human.hpp"
#include "Cat.hpp"
#include "ControllersRunner.hpp"
#include "World.hpp"
#include "Scope.hpp"
#include "ScopeDisplay.hpp"
#include "Debug.hpp"
#include "EntityFactory.hpp"

using namespace std;

int main(int argc, char **argv)
{
	IMoveEntity moveEntity;
	auto humanModel = EntityFactory::makeEntity<Human>();
	// auto cat0 = EntityFactory::makeEntity<Cat>();
	// auto cat1 = EntityFactory::makeEntity<Cat>();
	// auto cat2 = EntityFactory::makeEntity<Cat>();
	auto dogModel = EntityFactory::makeEntity<Dog>();
	auto dog1Model = EntityFactory::makeEntity<Dog>();
	// auto dog2Model = EntityFactory::makeEntity<Dog>();
	// auto dog3Model = EntityFactory::makeEntity<Dog>();
	
	humanModel->getIMove(moveEntity);
	moveEntity.m_position = Coordinates(50,50);
	moveEntity.m_hitbox.update(moveEntity.m_position);
	humanModel->setIMove(moveEntity);

	// cat0->getIMove(moveEntity);
	// moveEntity.m_position = Coordinates(143*5, 80*5);
	// cat0->setIMove(moveEntity);

	// cat1->getIMove(moveEntity);
	// moveEntity.m_position = Coordinates(150*5, 81*5);
	// cat1->setIMove(moveEntity);

	// cat2->getIMove(moveEntity);
	// moveEntity.m_position = Coordinates(153*5, 75*5);
	// cat2->setIMove(moveEntity);

	dogModel->getIMove(moveEntity);
	moveEntity.m_position = Coordinates(30*5, 30*5);
	moveEntity.m_hitbox.update(moveEntity.m_position);
	dogModel->setIMove(moveEntity);

	dog1Model->getIMove(moveEntity);
	moveEntity.m_position = Coordinates(40, 80);
	moveEntity.m_hitbox.update(moveEntity.m_position);
	dog1Model->setIMove(moveEntity);
	
	// dog2Model->getIMove(moveEntity);
	// moveEntity.m_position = Coordinates(30*5, 33*5);
	// dog2Model->setIMove(moveEntity);

	// dog3Model->getIMove(moveEntity);
	// moveEntity.m_position = Coordinates(8, 8);
	// dog3Model->setIMove(moveEntity);

	humanModel->m_controller = CONTROL_PLAYER;
	// cat0->m_control= CONTROL_AI;
	// cat1->m_control= CONTROL_AI;
	// cat2->m_control= CONTROL_AI;
	// dogModel->m_control= CONTROL_AI;
	// dog1Model->m_controller = CONTROL_AI;
	// dog2Model->m_control= CONTROL_AI;

	auto templateGen = make_unique<TemplateReader>("GameResources/Maps/road.png");

	auto mapSectors = SectorGenerator::generateMap(templateGen->getSize(),templateGen->getTemplate());

	auto map = make_shared<Map>(templateGen->getSize(),mapSectors);

	auto world = make_shared<World>();
	world->setMap(map);
	// world->setEntity(dog3Model);
	world->setEntity(humanModel);
	// world->setEntity(cat1);
	// world->setEntity(cat2);
	// world->setEntity(cat0);
	world->setEntity(dogModel);
	world->setEntity(dog1Model);
	// world->setEntity(dog2Model);
	world->sync();

	auto scope = make_shared<Scope>(world, Coordinates(0,0));
	scope->setSize(Size(121 * ISector::m_Size.w, 81 * ISector::m_Size.h));
	scope->trace(humanModel);
	
	auto scopeDisplay = make_unique<ScopeDisplay>(scope);
	
	auto window = make_unique<Window2d>(scope->getSize());

	auto controllerRunner = make_unique<ControllersRunner>(world, scope, window.get());

	// auto pController = static_cast<AIController*>(controllerRunner->getController(dog1Model.get()).get());
	// pController->AddPost(Coordinates(40, 40));
	// pController->AddPost(Coordinates(150, 200));
	
	auto controller = static_cast<PlayerModelController*>(controllerRunner->getController(humanModel.get()).get());
	
	controller->addOffset(&scope->getOffset());

	humanModel.reset();
	// cat0.reset();
	// cat1.reset();
	// cat2.reset();
	dogModel.reset();
	dog1Model.reset();
	// dog2Model.reset();
	// dog3Model.reset();

	while (controller->IfAlive())
	{
		scope->update();
		window->addSprites(scopeDisplay->getSprites());
		controllerRunner->Run();
		Sleep(1000.0 / 120);
	}
}
