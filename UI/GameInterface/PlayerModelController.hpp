#pragma once

#include "Controller.hpp"
#include "Scope.hpp"
#include "UserControl.hpp"

class PlayerModelController
{
public:
    PlayerModelController(Controller controller, Scope &scope);
	void addOffset(const Coordinates *pOffset){m_pOffset = pOffset;}

    bool run();

    static void actionRightClick(void* pObj);
    static void actionLeftClick(void* pObj);
    static void actionUpKey(void* pObj);
    static void actionDownKey(void* pObj);
    static void actionRightKey(void* pObj);
    static void actionLeftKey(void* pObj);
    static void actionQuit(void* pObj);

private:

    Controller m_controller;
    Scope &m_scope;
    const Coordinates *m_pOffset;
    UserControl m_control;

    Coordinates m_movement;
    bool m_isRunning;
};