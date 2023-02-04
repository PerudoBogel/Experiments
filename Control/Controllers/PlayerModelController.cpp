#include "PlayerModelController.hpp"
#include "Debug.hpp"

#include <cmath>
#include <assert.h>

using namespace std;

PlayerModelController::PlayerModelController(weak_ptr<World> pWorld, shared_ptr<IEntity> pEntity, weak_ptr<Scope> pScope, Window2d* pWindow):
	Controller(pWorld, pEntity),
    m_pScope(pScope),
    m_control(pWindow)
{
    assert(m_pEntity->getIMove().ifValid());
    assert(m_pEntity->getIWorld().ifValid());
    assert(m_pEntity->getIAttack().ifValid());

	m_control.RegisterKeyAction(UserControl::KeyAction::KEY_UP,(UserControl::Callback)&PlayerModelController::actionUpKey,this);
	m_control.RegisterKeyAction(UserControl::KeyAction::KEY_DOWN,(UserControl::Callback)&PlayerModelController::actionDownKey,this);
	m_control.RegisterKeyAction(UserControl::KeyAction::KEY_LEFT,(UserControl::Callback)&PlayerModelController::actionLeftKey,this);
	m_control.RegisterKeyAction(UserControl::KeyAction::KEY_RIGHT,(UserControl::Callback)&PlayerModelController::actionRightKey,this);

	m_control.RegisterWindowAction(UserControl::WindowAction::KEY_QUIT,(UserControl::Callback)&PlayerModelController::actionQuit,this);
    
	m_control.RegisterMouseAction(UserControl::MouseAction::MOUSE_PRESS_RIGHT,(UserControl::Callback)&PlayerModelController::actionRightClick,this);
	m_control.RegisterMouseAction(UserControl::MouseAction::MOUSE_PRESS_LEFT,(UserControl::Callback)&PlayerModelController::actionLeftClick,this);
}

void PlayerModelController::Run()
{
    auto lockedEntity = m_pEntity;
    if(!lockedEntity)
        m_isAlive = false;

    if(m_isAlive)
    {
        auto moveEntity = lockedEntity->getIMove();
        m_movement = Coordinates(0,0);
        m_control.Run();

        if (m_movement != Coordinates(0, 0))
        {
            m_movement *= *moveEntity.m_pSpeed;
            Move(m_movement);
        }
    }
    Controller::Run();
}

void PlayerModelController::actionRightClick(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);

    auto lockedEntity = pThis->m_pEntity;
    auto lockedScope = pThis->m_pScope.lock();
    
    if(!lockedEntity || !lockedScope)
        pThis->m_isAlive = false;

    if(pThis->m_isAlive)
    {
        auto worldEntity = lockedEntity->getIWorld();
        Coordinates direction = pThis->m_control.GetMouseCoordinates();
        direction += lockedScope->getOffset();
        direction -= *worldEntity.m_pPosition;

        pThis->Shoot(direction);
    }
}
void PlayerModelController::actionLeftClick(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);

    auto lockedScope = pThis->m_pScope.lock();
    
    if(!lockedScope)
        pThis->m_isAlive = false;

    if(pThis->m_isAlive)
    {
        Coordinates target = pThis->m_control.GetMouseCoordinates();
        if(pThis->m_pOffset)
            target += *pThis->m_pOffset;
        
        for (auto pEntity : *lockedScope->getEntities().lock().get())
        {
            auto worldTarget = pEntity->getIWorld();

            if(!worldTarget.ifValid())
            {
                continue;
            }

            if (Box(*worldTarget.m_pSize, *worldTarget.m_pPosition).Contains(target))
            {
                pThis->Attack(pEntity);
                break;
            }
        }
    }
}
void PlayerModelController::actionUpKey(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);
    if(pThis->m_isAlive)
    {
        pThis->m_movement += Coordinates(0,-1); 
    }
}
void PlayerModelController::actionDownKey(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);
    if(pThis->m_isAlive)
    {
        pThis->m_movement += Coordinates(0,1); 
    }
}
void PlayerModelController::actionRightKey(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);
    if(pThis->m_isAlive)
    {
        pThis->m_movement += Coordinates(1,0); 
    }
}
void PlayerModelController::actionLeftKey(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);
    if(pThis->m_isAlive)
    {
        pThis->m_movement += Coordinates(-1,0); 
    }
}

void PlayerModelController::actionQuit(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);
    if(pThis->m_isAlive)
    {
        pThis->m_isAlive = false;
    }
}