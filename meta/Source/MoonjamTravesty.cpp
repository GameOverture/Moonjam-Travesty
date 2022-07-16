#include "pch.h"
#include "MoonjamTravesty.h"

MoonjamTravesty::MoonjamTravesty(HarmonyInit &initStruct) :
	HyEngine(initStruct),
	m_pCamera(HyEngine::Window().CreateCamera2d())
{
	HyEngine::Input().MapBtn(INPUT_Menu, HYKEY_Escape);

	HyEngine::Input().MapBtn(INPUT_DebugCamUp, HYKEY_W);
	HyEngine::Input().MapBtn(INPUT_DebugCamDown, HYKEY_S);
	HyEngine::Input().MapBtn(INPUT_DebugCamLeft, HYKEY_A);
	HyEngine::Input().MapBtn(INPUT_DebugCamRight, HYKEY_D);

	//m_Outside.SetVisible(true);
	m_Outside.Load();
}

MoonjamTravesty::~MoonjamTravesty()
{
}

/*virtual*/ bool MoonjamTravesty::OnUpdate() /*override*/
{
	const float fDebugCamMovement = 100.0f;

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
