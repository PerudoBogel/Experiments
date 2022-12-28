#include "PlayerModelController.hpp"
#include "Debug.hpp"

PlayerModelController::PlayerModelController(Controller controller, Scope &scope):
    m_controller(controller),
    m_scope(scope),
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
    m_movement = Coordinates(0,0);
    m_control.run();
		
    if (m_movement != Coordinates(0, 0))
    {
        m_movement *= m_controller.m_model->m_speed;
		m_controller.move(m_movement);
    }
    return m_isRunning;
}

void PlayerModelController::actionRightClick(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);
	Coordinates direction = pThis->m_control.getMouseCoordinates();
	direction -= pThis->m_controller.m_model->m_position;
}
void PlayerModelController::actionLeftClick(void* pObj)
{
    PlayerModelController *pThis = static_cast<PlayerModelController*>(pObj);
    Coordinates target = pThis->m_control.getMouseCoordinates();
	if(pThis->m_pOffset)
		target += *pThis->m_pOffset;
	
	for (auto pModel : pThis->m_scope.getCharacters())
	{
		if (Box(pModel->getSize(), pModel->m_position).Contains(target))
		{
	        pThis->m_controller.attack(pModel.get());
			break;
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