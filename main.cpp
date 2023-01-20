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

using namespace std;

int main(int argc, char **argv)
{
	auto humanModel = make_shared<Human>();
	auto cat0 = make_shared<Cat>();
	auto cat1 = make_shared<Cat>();
	auto cat2 = make_shared<Cat>();
	auto dogModel = make_shared<Dog>();
	auto dog1Model = make_shared<Dog>();
	auto dog2Model = make_shared<Dog>();
	auto dog3Model = make_shared<Dog>();
	humanModel->m_position = Coordinates(50,50);
	cat0->m_position = Coordinates(143*5, 80*5);
	cat1->m_position = Coordinates(150*5, 81*5);
	cat2->m_position = Coordinates(153*5, 75*5);
	dogModel->m_position = Coordinates(30*5, 30*5);
	dog1Model->m_position = Coordinates(40, 80);
	dog2Model->m_position = Coordinates(30*5, 33*5);
	dog3Model->m_position = Coordinates(8, 8);
	humanModel->getIControl().m_controller = CONTROL_PLAYER;
	// cat0->m_control= CONTROL_AI;
	// cat1->m_control= CONTROL_AI;
	// cat2->m_control= CONTROL_AI;
	// dogModel->m_control= CONTROL_AI;
	dog1Model->getIControl().m_controller = CONTROL_AI;
	// dog2Model->m_control= CONTROL_AI;

	auto templateGen = make_unique<TemplateReader>("GameResources/Maps/road.png");

	auto mapSectors = SectorGenerator::generateMap(templateGen->getSize(),templateGen->getTemplate());

	auto map = make_shared<Map>(templateGen->getSize(),mapSectors);

	auto world = make_shared<World>();
	world->setMap(map);
	world->setEntity(dog3Model);
	world->setEntity(humanModel);
	world->setEntity(cat1);
	world->setEntity(cat2);
	world->setEntity(cat0);
	world->setEntity(dogModel);
	world->setEntity(dog1Model);
	world->setEntity(dog2Model);

	auto scope = make_shared<Scope>(world, Coordinates(0,0));
	scope->setSize(Size(121 * ISector::m_Size.w, 81 * ISector::m_Size.h));
	scope->trace(&humanModel->getIWorld());
	
	auto scopeDisplay = make_unique<ScopeDisplay>(scope);
	
	auto window = make_unique<Window2d>(scope->getSize());

	auto controllerRunner = make_unique<ControllersRunner>(world, scope, window.get());

	auto pController = static_cast<AIController*>(controllerRunner->getController(dog1Model.get()).get());
	pController->AddPost(Coordinates(40, 40));
	pController->AddPost(Coordinates(150, 200));
	
	auto controller = static_cast<PlayerModelController*>(controllerRunner->getController(humanModel.get()).get());
	
	controller->addOffset(&scope->getOffset());

	while (controller->IfAlive())
	{
		scope->update();
		window->addSprites(scopeDisplay->getSprites());
		controllerRunner->Run();
		Sleep(1000.0 / 120);
	}
}
