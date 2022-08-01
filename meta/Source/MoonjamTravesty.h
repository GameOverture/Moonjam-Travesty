#ifndef MoonjamTravesty_h__
#define MoonjamTravesty_h__

#include "pch.h"
#include "Player.h"
#include "Outside.h"
#include "Inside.h"
#include "Game.h"
#include "TitleOverlay.h"
#include "TheNextDay.h"
#include "GameOver.h"

class MoonjamTravesty : public HyEngine
{
	static MoonjamTravesty *	sm_pInstance;
	HyCamera2d *				m_pCamera;

	Player						m_Player;
	Outside						m_Outside;
	Inside						m_Inside;
	Game						m_Game;
	TitleOverlay				m_Title;
	TheNextDay					m_TheNextDay;
	GameOver					m_GameOver;

	HyPrimitive2d				m_LoadCover;

	enum GameState
	{
		STATE_Loading = 0,
		STATE_Title,
		STATE_Play,
		STATE_FadeOut,
		STATE_Bills,
		STATE_Attack,
		STATE_TheNextDay,
		STATE_GameOver
	};
	GameState					m_eGameState;

	int32						m_iDayIndex;

public:
	MoonjamTravesty(HarmonyInit &initStruct);
	virtual ~MoonjamTravesty();

	virtual bool OnUpdate() override;

	static void LeaveHouse();
	static void EnterHouse();

	static Game &GetGame();
	static int32 GetDayIndex();

	static void BuyCum();
	static void BuyGun();

	static void StartDay();
	static void EndDay();
	static void Sleep(int64 iRemainingMoney, bool bBoughtMedicine, bool bBoughtFood);
	static void GameOver(GameOverType eGameOverType);
};

#endif // MoonjamTravesty_h__
