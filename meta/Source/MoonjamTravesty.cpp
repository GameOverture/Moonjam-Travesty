#include "pch.h"
#include "MoonjamTravesty.h"

MoonjamTravesty *MoonjamTravesty::sm_pInstance = nullptr;

MoonjamTravesty::MoonjamTravesty(HarmonyInit &initStruct) :
	HyEngine(initStruct),
	m_pCamera(HyEngine::Window().CreateCamera2d()),
	m_Outside(m_Player),
	m_Inside(m_Player),
	m_Title(),
	m_eGameState(STATE_Loading),
	m_iDayIndex(0)
{
	m_LoadCover.UseWindowCoordinates();
	m_LoadCover.shape.SetAsBox(HyEngine::Window().GetWidthF(), HyEngine::Window().GetHeightF());
	m_LoadCover.SetTint(HyColor::Black);
	m_LoadCover.SetDisplayOrder(DISPLAYORDER_LoadCover);

	HyEngine::Input().MapBtn(INPUT_Menu, HYKEY_Escape);

	//HyEngine::Input().MapBtn(INPUT_DebugCamUp, HYKEY_Up);
	//HyEngine::Input().MapBtn(INPUT_DebugCamDown, HYKEY_Down);
	//HyEngine::Input().MapBtn(INPUT_DebugCamLeft, HYKEY_Left);
	//HyEngine::Input().MapBtn(INPUT_DebugCamRight, HYKEY_Right);
	//HyEngine::Input().MapBtn(INPUT_DebugSpawnCum, HYKEY_U);
	//HyEngine::Input().MapBtn(INPUT_DebugSpawnGun, HYKEY_I);

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
	m_TheNextDay.Load();
	m_GameOver.Load();
	
	m_Outside.Hide();
	m_Inside.Hide();
	m_Title.SetVisible(false);
	m_TheNextDay.SetVisible(false);
	m_GameOver.SetVisible(false);

	sm_pInstance = this;
}

MoonjamTravesty::~MoonjamTravesty()
{
}

/*virtual*/ bool MoonjamTravesty::OnUpdate() /*override*/
{
	const float fDebugCamMovement = 540.0f;
	//if(HyEngine::Input().IsActionDown(INPUT_DebugCamUp))
	//	m_pCamera->pos.Offset(0.0f, fDebugCamMovement * HyEngine::DeltaTime());
	//if(HyEngine::Input().IsActionDown(INPUT_DebugCamDown))
	//	m_pCamera->pos.Offset(0.0f, -fDebugCamMovement * HyEngine::DeltaTime());
	//if(HyEngine::Input().IsActionDown(INPUT_DebugCamLeft))
	//	m_pCamera->pos.Offset(-fDebugCamMovement * HyEngine::DeltaTime(), 0.0f);
	//if(HyEngine::Input().IsActionDown(INPUT_DebugCamRight))
	//	m_pCamera->pos.Offset(fDebugCamMovement * HyEngine::DeltaTime(), 0.0f);

	//if(HyEngine::Input().IsActionReleased(INPUT_DebugCamUp))
	//	EndDay();

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
		m_iDayIndex = 0;
		if(m_Title.IsFinished())
		{
			m_Inside.Reset();

			m_Title.alpha.Tween(0.0f, 0.5f, HyTween::Linear, [](IHyNode *pThis) { pThis->SetVisible(false); });

			m_Game.OnStartDay();
			EnterHouse();
			m_eGameState = STATE_Play;
		}
		break;

	case STATE_Play:
		break;

	case STATE_FadeOut:
		if(m_Outside.alpha.IsAnimating() == false)
		{
			m_Outside.alpha.Set(1.0f);
			m_Outside.Hide();
			m_Inside.alpha.Set(1.0f);
			m_Inside.Hide();

			m_Game.OnEndDay(m_Outside.GetHouseDamage() * iHOUSE_DAMAGE_COST);
			m_eGameState = STATE_Bills;
		}
		break;

	case STATE_Bills:
		break;

	case STATE_Attack:
		if(m_Outside.IsAttackFinished())
		{
			if(m_iDayIndex >= iDAYINDEX_ENDGAME)
			{
				m_Game.m_Bills.Assemble(iMAX_WORK_PROFIT, m_Outside.GetHouseDamage() * iHOUSE_DAMAGE_COST, m_Game.m_BillyChecklist.GetBillyFeels(), m_Game.m_BillyChecklist.GetBillyGrade());
				m_Game.m_Bills.Load();
				m_Game.m_Bills.Show();
				m_eGameState = STATE_Bills;
			}
			else
			{
				m_TheNextDay.Reset(m_iDayIndex >= iDAYINDEX_ENDGAME - 1);
				m_TheNextDay.SetVisible(true);
				m_TheNextDay.alpha.Set(0.0f);
				m_TheNextDay.alpha.Tween(1.0f, 2.0f, HyTween::Linear, [](IHyNode *pThis) { static_cast<TheNextDay *>(pThis)->Start(); });
				m_eGameState = STATE_TheNextDay;
			}
		}
		break;

	case STATE_TheNextDay:
		if(m_TheNextDay.IsFinished())
		{
			m_TheNextDay.alpha.Tween(0.0f, 0.6f, HyTween::Linear, [](IHyNode *pThis) { pThis->SetVisible(false); });

			m_Inside.Reset();

			m_Game.OnStartDay();
			EnterHouse();
			m_eGameState = STATE_Play;
		}

		break;

	case STATE_GameOver:


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

/*static*/ int32 MoonjamTravesty::GetDayIndex()
{
	return sm_pInstance->m_iDayIndex;
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

/*static*/ void MoonjamTravesty::StartDay()
{
	sm_pInstance->m_Game.OnStartDay();
}

/*static*/ void MoonjamTravesty::EndDay()
{
	if(sm_pInstance->m_eGameState == STATE_Play)
	{
		sm_pInstance->m_Game.m_Clock.Pause();

		sm_pInstance->m_Player.EnableInput(false);
		sm_pInstance->m_Game.HideComputer();

		sm_pInstance->m_Inside.alpha.Tween(0.0f, 2.0f);
		sm_pInstance->m_Outside.alpha.Tween(0.0f, 2.0f);

		sm_pInstance->m_eGameState = STATE_FadeOut;
	}
}

/*static*/ void MoonjamTravesty::Sleep(int64 iRemainingMoney, bool bBoughtMedicine, bool bBoughtFood)
{
	sm_pInstance->m_Game.m_Clock.SetMoney(iRemainingMoney, 0.0f);
	sm_pInstance->m_Game.OnSleep(bBoughtMedicine, bBoughtFood);
	sm_pInstance->m_Outside.SetupAttack(sm_pInstance->m_iDayIndex);
	sm_pInstance->m_iDayIndex++;

	HyLog("Day: " << sm_pInstance->m_iDayIndex);

	sm_pInstance->m_eGameState = STATE_Attack;
}

/*static*/ void MoonjamTravesty::GameOver(GameOverType eGameOverType)
{
	sm_pInstance->m_Outside.Hide();
	sm_pInstance->m_Inside.Hide();
	sm_pInstance->m_Game.m_Bills.Hide();
	sm_pInstance->m_Game.m_Clock.SetVisible(false);
	sm_pInstance->m_Game.HideComputer();
	sm_pInstance->m_Title.SetVisible(false);
	sm_pInstance->m_TheNextDay.SetVisible(false);
	
	if(eGameOverType == GAMEOVER_Win)
		sm_pInstance->m_GameOver.m_GameOver.SetText("YOU WIN!");

	sm_pInstance->m_GameOver.SetVisible(true);
	sm_pInstance->m_GameOver.m_StoryEnds.Play();

	sm_pInstance->m_eGameState = STATE_GameOver;
}
