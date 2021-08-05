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

int main(int argc, char **argv)
{
	auto humanModel = std::make_shared<Human>();
	auto cat0 = std::make_shared<Cat>();
	auto cat1 = std::make_shared<Cat>();
	auto cat2 = std::make_shared<Cat>();
	auto dogModel = std::make_shared<Dog>();
	auto dog1Model = std::make_shared<Dog>();
	auto dog2Model = std::make_shared<Dog>();
	auto dog3Model = std::make_shared<Dog>();
	*humanModel->m_position = Coordinates(24, 24);
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

	std::unique_ptr<TemplateReader> templateGen = std::make_unique<
			TemplateReader>("World/Map/templates/road.png");

	std::vector<ISector*> mapSectors = SectorGenerator::generateMap(templateGen->getSize(),templateGen->getTemplate());

	std::shared_ptr<Map> map = std::make_shared<Map>(templateGen->getSize(),mapSectors);

	std::shared_ptr<World> world = std::make_shared<World>();
	world->setMap(map);
	world->setModel(dog3Model);
	world->setModel(humanModel);
	world->setModel(cat1);
	world->setModel(cat2);
	world->setModel(cat0);
	world->setModel(dogModel);
	world->setModel(dog1Model);
	world->setModel(dog2Model);

	std::shared_ptr<Scope> scope = std::make_unique<Scope>();
	scope->setWorld(world);
	scope->setSize(Size(121 * ISector::m_Size.w, 81 * ISector::m_Size.h));
	//scope->trace(world->getPlayer());
	scope->trace(dog1Model->m_position);

	std::unique_ptr<AI> ai = std::make_unique<AI>(world);

	auto pController = ai->getController(dog1Model);
	pController->AddPost(Coordinates(120, 60));
	pController->AddPost(Coordinates(130, 80));

	std::unique_ptr<UserControl> controller = std::make_unique<UserControl>(
			Controller(world, world->getPlayer()));

	std::unique_ptr<Window2d> window = std::make_unique<Window2d>(scope,
			scope->getSize().w, scope->getSize().h);
	window->makeWindow();

	int command;
	do
	{
		command = controller->run();
		ai->Run();
		window->update();
		Sleep(1000 / 15);

	} while (command != UserControl::QUIT);
}
