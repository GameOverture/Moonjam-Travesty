#ifndef Game_h__
#define Game_h__

#include "pch.h"
#include "Computer.h"
#include "Bills.h"
#include "Clock.h"
#include "BillyChecklist.h"

const int iCUM_COST = 10000;
const int iGUN_COST = 20000;

const float fSNACK_DUR = 6.0f;
const float fDINNER_DUR = 12.0f;
const float fHOMEWORK_DUR = 8.0f;

const float fDAY_LENGTH = 1500.0f;
const int64 iSTART_MONEY = 100000;

const int64 iMAX_WORK_PROFIT = 100000;
const float fMAX_WORK_TIME = 0.5f;

const int64 iMORTGAGE_COST = 25000;
const int64 iFOOD_COST = 10000;
const int64 iAC_COST = 10000;
const int64 iMEDICINE_COST = 10000;
const int64 iHOUSE_DAMAGE_COST = 10000;

// ATTACK
const float fGUMS_MOVEMENT = 175.0f;
const float fBORPA_MOVEMENT = 275.0f;

const float fGUN_RANGE = 420.0f;
const float fGUMS_CUM_MOVE_MOD = 0.42f;

const float fLEFT_BOUNDS = -1375.0f;
const float fRIGHT_BOUNDS = 666.0f;


class MoonjamTravesty;

class Game : public HyEntity2d
{
	friend class MoonjamTravesty;

	Computer			m_Computer;
	Bills				m_Bills;
	Clock				m_Clock;

	BillyChecklist		m_BillyChecklist;

public:
	Game(HyEntity2d *pParent = nullptr);
	virtual ~Game();

	virtual void OnUpdate() override;

	int64 GetMoney();
	int64 GetCurWorkProfit();
	float GetPercentOfDayLeft();
	int32 GetFoodCount();

	void ShowComputer();
	void HideComputer();

	BillyChecklist &GetBilly();

private:
	void BuyCum();
	void BuyGun();
	void OnStartDay();
	void OnEndDay();
	void OnSleep(bool bBoughtMedicine, bool bBoughtFood);
};

#endif // Game_h__
