#include <iostream>
#include <windows.h>

#include "Map.hpp"
#include "SectorGenerator.hpp"
#include "Window2d.hpp"
#include "UserControl.hpp"
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
	*humanModel->m_position = Coordinates(121 * ISector::m_Size.w/2+23, 81 * ISector::m_Size.h/2+23);
	*cat0->m_position = Coordinates(143*5, 80*5);
	*cat1->m_position = Coordinates(150*5, 81*5);
	*cat2->m_position = Coordinates(153*5, 75*5);
	*dogModel->m_position = Coordinates(30*5, 30*5);
	*dog1Model->m_position = Coordinates(120*5, 60*5);
	*dog2Model->m_position = Coordinates(30*5, 33*5);
	*dog3Model->m_position = Coordinates(8, 8);
	humanModel->m_control= IModel::CONTROL_PLAYER;
	/*cat0->m_control= IModel::CONTROL_AI;
	cat1->m_control= IModel::CONTROL_AI;
	cat2->m_control= IModel::CONTROL_AI;
	dogModel->m_control= IModel::CONTROL_AI;*/
	dog1Model->m_control= IModel::CONTROL_AI;
	//dog2Model->m_control= IModel::CONTROL_AI;

	unique_ptr<TemplateReader> templateGen = make_unique<
			TemplateReader>("GameResources/Maps/road.png");

	vector<ISector*> mapSectors = SectorGenerator::generateMap(templateGen->getSize(),templateGen->getTemplate());

	shared_ptr<Map> map = make_shared<Map>(templateGen->getSize(),mapSectors);

	shared_ptr<World> world = make_shared<World>();
	world->setMap(map);
	world->setModel(dog3Model);
	world->setModel(humanModel);
	world->setModel(cat1);
	world->setModel(cat2);
	world->setModel(cat0);
	world->setModel(dogModel);
	world->setModel(dog1Model);
	world->setModel(dog2Model);

	shared_ptr<Scope> scope = make_unique<Scope>(world, humanModel->m_position);
	scope->setSize(Size(121 * ISector::m_Size.w, 81 * ISector::m_Size.h));

	unique_ptr<AI> ai = make_unique<AI>(world);

	auto pController = ai->getController(dog1Model);
	pController->AddPost(Coordinates(200, 200));
	pController->AddPost(Coordinates(600, 600));

	unique_ptr<UserControl> controller = make_unique<UserControl>(
			Controller(world, world->getPlayer()));

	unique_ptr<Window2d> window = make_unique<Window2d>(scope->getSize());
	
	unique_ptr<ScopeDisplay> scopeDisplay = make_unique<ScopeDisplay>(scope);

	int command;
	do
	{
		command = controller->run();
		scope->update();
		ai->Run();
		//window->clear();
		window->addElements(scopeDisplay->getElements());
		window->lock();
		window->update();
		Sleep(1000.0 / 120.0);

	} while (command != UserControl::QUIT);
}
