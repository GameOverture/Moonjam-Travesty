#ifndef MoonjamTravesty_h__
#define MoonjamTravesty_h__

#include "pch.h"
#include "Player.h"
#include "Outside.h"
#include "Inside.h"
#include "Game.h"

class MoonjamTravesty : public HyEngine
{
	static MoonjamTravesty *	sm_pInstance;
	HyCamera2d *				m_pCamera;

	Player						m_Player;
	Outside						m_Outside;
	Inside						m_Inside;
	Game						m_Game;

	enum GameState
	{
		STATE_Loading = 0,
		STATE_Play
	};
	GameState					m_eGameState;

public:
	MoonjamTravesty(HarmonyInit &initStruct);
	virtual ~MoonjamTravesty();

	virtual bool OnUpdate() override;

	static void LeaveHouse();
	static void EnterHouse();

	static Game &GetGame();
	static void BuyCum();
	static void BuyGun();
};

#endif // MoonjamTravesty_h__
