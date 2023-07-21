#pragma once
#include "Size.hpp"
#include "ControllerType.hpp"
#include "Fraction.hpp"
#include "Coordinates.hpp"
#include "Hitbox.hpp"
#include "TextureId.hpp"

struct EntityData
{
    TextureId m_textureId;
	int m_customData;
    int m_health;
    int m_maxHealth;
	bool m_isAlive;
	bool m_isCollidable;
    int m_baseDamage;
    int m_attack;
    int m_defence;
    int m_range;
    int m_moveStrength;
	decltype(Coordinates::x) m_speed;
	ControllerType m_controller = CONTROL_NONE;
	Fraction m_memberFractions,	m_allyFractions;
    Coordinates m_position;
    Size m_size;
	Hitbox m_hitbox;
};
