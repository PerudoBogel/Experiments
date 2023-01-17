#pragma once

#include "Controller.hpp"
#include "Scope.hpp"
#include "UserControl.hpp"
#include "Window2d.hpp"

#include <memory>

using namespace std;

class PlayerModelController: public Controller
{
public:
    PlayerModelController() = delete;
    PlayerModelController(weak_ptr<World> pWorld, weak_ptr<IEntity> pEntity, weak_ptr<Scope> pScope, Window2d* pWindow);
	void addOffset(const Coordinates *pOffset){m_pOffset = pOffset;}

    void Run();
	ControllerType GetType(){return CONTROL_PLAYER;}

    static void actionRightClick(void* pObj);
    static void actionLeftClick(void* pObj);
    static void actionUpKey(void* pObj);
    static void actionDownKey(void* pObj);
    static void actionRightKey(void* pObj);
    static void actionLeftKey(void* pObj);
    static void actionQuit(void* pObj);

private:

    weak_ptr<Scope> m_pScope;
    const Coordinates *m_pOffset;
    UserControl m_control;

    Coordinates m_movement;
};