#include <iostream>
#include <windows.h>

#include "Window2d.hpp"
#include "Human.hpp"
#include "Debug.hpp"
#include "EntityFactory.hpp"
#include "TextureLoader.hpp"
#include "AnimationDriver.hpp"

using namespace std;

int main(int argc, char **argv)
{
	IMoveEntity moveEntity;
	auto humanModel = EntityFactory::makeEntity<Human>();
	
	IEntity::getInterface(humanModel, moveEntity);
	moveEntity.m_position = Coordinates(25,25);
	moveEntity.m_hitbox.update(moveEntity.m_position);
	moveEntity.m_size = Size(50, 50);
	IEntity::setInterface(humanModel, moveEntity);
	
	auto window = make_unique<Window2d>(Size(500,500));

	TextureLoader loader;
	if(loader.ReadTexture("GameResources/Models/Test.png", MODEL_TYPE_HUMAN))
	{
		auto config = loader.GetTextureConfig(MODEL_TYPE_HUMAN);
		AnimationDriver animation(humanModel, *config);

		for (int i = 0; i < 60 * 4; i++)
		{	
			vector<sf::Sprite> sprites;
			sprites.push_back(*animation.GetFrame(TextureMode::IDLE, 0.5, 30));
			window->addSprites(sprites);
			Sleep(1000/30);
		}
	}
}
