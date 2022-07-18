#include "pch.h"
#include "MoonjamTravesty.h"

MoonjamTravesty *MoonjamTravesty::sm_pInstance = nullptr;

MoonjamTravesty::MoonjamTravesty(HarmonyInit &initStruct) :
	HyEngine(initStruct),
	m_pCamera(HyEngine::Window().CreateCamera2d()),
	m_Outside(m_Player),
	m_Inside(m_Player),
	m_Title(),
	m_eGameState(STATE_Loading)
{
	m_LoadCover.UseWindowCoordinates();
	m_LoadCover.shape.SetAsBox(HyEngine::Window().GetWidthF(), HyEngine::Window().GetHeightF());
	m_LoadCover.SetTint(HyColor::Black);
	m_LoadCover.SetDisplayOrder(DISPLAYORDER_LoadCover);

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
	m_Game.Load();
	m_Title.Load();
	
	m_Outside.Hide();
	m_Inside.Hide();
	m_Title.SetVisible(false);

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

	switch(m_eGameState)
	{
	case STATE_Loading:
		if(m_Player.IsLoaded() &&
			m_Outside.IsLoaded() &&
			m_Inside.IsLoaded() &&
			m_Game.IsLoaded())
		{
			m_LoadCover.alpha.Tween(0.0f, 0.5f, HyTween::Linear, [](IHyNode *pThis) { pThis->SetVisible(false); });
			
			m_Outside.SetVisible(true);
			m_pCamera->SetZoom(1.0f);
			m_pCamera->pos.Set(0.0f, 275.0f);

			m_Title.SetVisible(true);
			m_Title.alpha.Set(0.0f);
			m_Title.alpha.Tween(1.0f, 0.5);

			m_eGameState = STATE_Title;
		}
		break;

	case STATE_Title:
		if(m_Title.IsFinished())
		{
			m_Title.alpha.Tween(0.0f, 0.5f, HyTween::Linear, [](IHyNode *pThis) { pThis->SetVisible(false); });

			m_Game.StartDay();
			EnterHouse();
			m_eGameState = STATE_Play;
		}
		break;

	case STATE_Play:
		break;

	case STATE_Sleep:
		break;
	}

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

/*static*/ Game &MoonjamTravesty::GetGame()
{
	return sm_pInstance->m_Game;
}

/*static*/ void MoonjamTravesty::BuyCum()
{
	sm_pInstance->m_Game.BuyCum();
	sm_pInstance->m_Outside.SpawnCum();
}

/*static*/ void MoonjamTravesty::BuyGun()
{
	sm_pInstance->m_Game.BuyGun();
	sm_pInstance->m_Outside.SpawnGun();
}

/*static*/ void MoonjamTravesty::Sleep()
{
	sm_pInstance->m_eGameState = STATE_Sleep;
}
