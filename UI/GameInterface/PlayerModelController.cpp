#include "PlayerModelController.hpp"
#include "Debug.hpp"

#include <cmath>

using namespace std;

#define TEST_STATIC_PTR(ptr)    if(!ptr)\
                                {\
                                    pThis->m_isRunning = false;\
                                    return;\
                                }

const float PI = 3.141592653589793238462643383279502884;

PlayerModelController::PlayerModelController(unique_ptr<Controller>&& controller, weak_ptr<Scope> scope):
    m_pController(move(controller)),
    m_pScope(scope),
    m_isRunning(true)
{
	m_control.registerKeyAction(UserControl::KeyAction::KEY_UP,(UserControl::Callback)&PlayerModelController::actionUpKey,this);
	m_control.registerKeyAction(UserControl::KeyAction::KEY_DOWN,(UserControl::Callback)&PlayerModelController::actionDownKey,this);
	m_control.registerKeyAction(UserControl::KeyAction::KEY_LEFT,(UserControl::Callback)&PlayerModelController::actionLeftKey,this);
	m_control.registerKeyAction(UserControl::KeyAction::KEY_RIGHT,(UserControl::Callback)&PlayerModelController::actionRightKey,this);

	m_control.registerWindowAction(UserControl::WindowAction::KEY_QUIT,(UserControl::Callback)&PlayerModelController::actionQuit,this);
    
	m_control.registerMouseAction(UserControl::MouseAction::MOUSE_CLICK_RIGHT,(UserControl::Callback)&PlayerModelController::actionRightClick,this);
	m_control.registerMouseAction(UserControl::MouseAction::MOUSE_CLICK_LEFT,(UserControl::Callback)&PlayerModelController::actionLeftClick,this);
}

bool PlayerModelController::run()
{
    auto lockedWorldEntity = m_pController->m_pEntity->getIWorld().lock();
    if(!lockedWorldEntity)
        return false;

    if(m_isRunning)
    {
        m_movement = Coordinates(0,0);
        m_control.run();

        if (m_movement != Coordinates(0, 0))
        {
            m_movement *= *lockedWorldEntity->m_pSpeed;
            m_pController->move(m_movement);
        }
    }
    return m_isRunning;
}

void PlayerModelController::actionRightClick(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);

    auto lockedWorldEntity = pThis->m_pController->m_pEntity->getIWorld().lock();
    TEST_STATIC_PTR(lockedWorldEntity)

    auto lockedScope = pThis->m_pScope.lock();
    TEST_STATIC_PTR(lockedScope);

    if(pThis->m_isRunning)
    {
        Coordinates direction = pThis->m_control.getMouseCoordinates();
        direction += lockedScope->getOffset();
        direction -= *lockedWorldEntity->m_pPosition;

        auto rotation = atan(direction.y/ direction.x) / (2 * PI) * 360;

        if(direction.x < 0)
        {
            rotation += 180;
        }

        pThis->m_pController->shoot(rotation);
    }
}
void PlayerModelController::actionLeftClick(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);

    auto lockedWorldEntity = pThis->m_pController->m_pEntity->getIWorld().lock();
    TEST_STATIC_PTR(lockedWorldEntity);

    auto lockedScope = pThis->m_pScope.lock();
    TEST_STATIC_PTR(lockedScope);

    if(pThis->m_isRunning)
    {
        Coordinates target = pThis->m_control.getMouseCoordinates();
        if(pThis->m_pOffset)
            target += *pThis->m_pOffset;
        
        for (auto pEntity : *lockedScope->getEntities().lock().get())
        {
            auto lockedEntity = pEntity.lock();
            if (Box(*lockedWorldEntity->m_pSize, *lockedWorldEntity->m_pPosition).Contains(target) && lockedEntity)
            {
                pThis->m_pController->attack(pThis->m_pController->m_pEntity);
                break;
            }
        }
    }
}
void PlayerModelController::actionUpKey(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);
    pThis->m_movement += Coordinates(0,-1); 
}
void PlayerModelController::actionDownKey(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);
    pThis->m_movement += Coordinates(0,1); 
}
void PlayerModelController::actionRightKey(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);
    pThis->m_movement += Coordinates(1,0); 
}
void PlayerModelController::actionLeftKey(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);
    pThis->m_movement += Coordinates(-1,0); 
}

void PlayerModelController::actionQuit(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);
    pThis->m_isRunning = false;
}