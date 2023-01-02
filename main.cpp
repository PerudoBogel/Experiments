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
#include "AI.hpp"
#include "World.hpp"
#include "Scope.hpp"
#include "ScopeDisplay.hpp"

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
	humanModel->m_position = make_shared<Coordinates>(121 * ISector::m_Size.w/2+23, 81 * ISector::m_Size.h/2+23);
	cat0->m_position = make_shared<Coordinates>(143*5, 80*5);
	cat1->m_position = make_shared<Coordinates>(150*5, 81*5);
	cat2->m_position = make_shared<Coordinates>(153*5, 75*5);
	dogModel->m_position = make_shared<Coordinates>(30*5, 30*5);
	dog1Model->m_position = make_shared<Coordinates>(120*5, 60*5);
	dog2Model->m_position = make_shared<Coordinates>(30*5, 33*5);
	dog3Model->m_position = make_shared<Coordinates>(8, 8);
	humanModel->m_control= IModel::CONTROL_PLAYER;
	// cat0->m_control= IModel::CONTROL_AI;
	// cat1->m_control= IModel::CONTROL_AI;
	// cat2->m_control= IModel::CONTROL_AI;
	// dogModel->m_control= IModel::CONTROL_AI;
	dog1Model->m_control= IModel::CONTROL_AI;
	// dog2Model->m_control= IModel::CONTROL_AI;

	unique_ptr<TemplateReader> templateGen = make_unique<
			TemplateReader>("GameResources/Maps/road.png");

	vector<ISector*> mapSectors = SectorGenerator::generateMap(templateGen->getSize(),templateGen->getTemplate());

	shared_ptr<Map> map = make_shared<Map>(templateGen->getSize(),mapSectors);

	shared_ptr<World> world = make_shared<World>();
	world->setMap(map);
	world->setEntity(dog3Model);
	world->setEntity(humanModel);
	world->setEntity(cat1);
	world->setEntity(cat2);
	world->setEntity(cat0);
	world->setEntity(dogModel);
	world->setEntity(dog1Model);
	world->setEntity(dog2Model);

	shared_ptr<Scope> scope = make_shared<Scope>(world, humanModel->m_position);
	scope->setSize(Size(121 * ISector::m_Size.w, 81 * ISector::m_Size.h));

	unique_ptr<AI> ai = make_unique<AI>(world);

	auto pController = ai->getController(dog1Model);
	pController->AddPost(Coordinates(1000, 1000));
	pController->AddPost(Coordinates(600, 600));

	unique_ptr<PlayerModelController> controller = make_unique<PlayerModelController>(
			make_unique<Controller>(world, humanModel), scope);
	
	controller->addOffset(&scope->getOffset());

	unique_ptr<Window2d> window = make_unique<Window2d>(scope->getSize());
	
	unique_ptr<ScopeDisplay> scopeDisplay = make_unique<ScopeDisplay>(scope);

	int command;
	while (controller->run())
	{
		scope->update();
		ai->Run();
		//window->clear();
		window->addSprites(scopeDisplay->getSprites());
		window->lock();
		window->update();
		Sleep(1000.0 / 120.0);
	}

	cout<<"closing"<<endl;
}
