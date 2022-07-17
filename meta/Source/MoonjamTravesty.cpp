#include "pch.h"
#include "MoonjamTravesty.h"

MoonjamTravesty *MoonjamTravesty::sm_pInstance = nullptr;

MoonjamTravesty::MoonjamTravesty(HarmonyInit &initStruct) :
	HyEngine(initStruct),
	m_pCamera(HyEngine::Window().CreateCamera2d()),
	m_Outside(m_Player),
	m_Inside(m_Player)
{
	HyEngine::Input().MapBtn(INPUT_Menu, HYKEY_Escape);

	HyEngine::Input().MapBtn(INPUT_DebugCamUp, HYKEY_Up);
	HyEngine::Input().MapBtn(INPUT_DebugCamDown, HYKEY_Down);
	HyEngine::Input().MapBtn(INPUT_DebugCamLeft, HYKEY_Left);
	HyEngine::Input().MapBtn(INPUT_DebugCamRight, HYKEY_Right);
	HyEngine::Input().MapBtn(INPUT_DebugSpawnCum, HYKEY_U);
	HyEngine::Input().MapBtn(INPUT_DebugSpawnGun, HYKEY_I);

	HyEngine::Input().MapBtn(INPUT_MoveLeft, HYKEY_A);
	HyEngine::Input().MapBtn(INPUT_MoveRight, HYKEY_D);
	HyEngine::Input().MapBtn(INPUT_MoveUp, HYKEY_W);
	HyEngine::Input().MapBtn(INPUT_MoveDown, HYKEY_S);
	HyEngine::Input().MapBtn(INPUT_Jump, HYKEY_Space);
	HyEngine::Input().MapBtn(INPUT_Action, HYKEY_E);

	HyEngine::Input().MapGamePadBtn(INPUT_MoveLeft, HYPAD_DpadLeft);
	HyEngine::Input().MapGamePadBtn(INPUT_MoveRight, HYPAD_DpadRight);
	HyEngine::Input().MapGamePadBtn(INPUT_MoveUp, HYPAD_DpadUp);
	HyEngine::Input().MapGamePadBtn(INPUT_MoveDown, HYPAD_DpadDown);
	HyEngine::Input().MapGamePadBtn(INPUT_Jump, HYPAD_A);
	HyEngine::Input().MapGamePadBtn(INPUT_Action, HYPAD_X);
	
	m_Player.Load();
	m_Outside.Load();
	m_Inside.Load();
	m_Clock.Load();
	

	m_Outside.Hide();
	m_Inside.Hide();

	//m_Inside.Init();
	m_Outside.Init();

	sm_pInstance = this;
}

MoonjamTravesty::~MoonjamTravesty()
{
}

/*virtual*/ bool MoonjamTravesty::OnUpdate() /*override*/
{
	const float fDebugCamMovement = 540.0f;
	if(HyEngine::Input().IsActionDown(INPUT_DebugCamUp))
		m_pCamera->pos.Offset(0.0f, fDebugCamMovement * HyEngine::DeltaTime());
	if(HyEngine::Input().IsActionDown(INPUT_DebugCamDown))
		m_pCamera->pos.Offset(0.0f, -fDebugCamMovement * HyEngine::DeltaTime());
	if(HyEngine::Input().IsActionDown(INPUT_DebugCamLeft))
		m_pCamera->pos.Offset(-fDebugCamMovement * HyEngine::DeltaTime(), 0.0f);
	if(HyEngine::Input().IsActionDown(INPUT_DebugCamRight))
		m_pCamera->pos.Offset(fDebugCamMovement * HyEngine::DeltaTime(), 0.0f);


	return true;
}

/*static*/ void MoonjamTravesty::LeaveHouse()
{
	sm_pInstance->m_Inside.Hide();
	sm_pInstance->m_Outside.Init();
}

/*static*/ void MoonjamTravesty::EnterHouse()
{
	sm_pInstance->m_Outside.Hide();
	sm_pInstance->m_Inside.Init();
}
