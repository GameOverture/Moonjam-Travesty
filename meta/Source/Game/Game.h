#ifndef Game_h__
#define Game_h__

#include "pch.h"
#include "Computer.h"
#include "Bills.h"
#include "Clock.h"

const int iCUM_COST = 10000;
const int iGUN_COST = 20000;

const float fDAY_LENGTH = 15.0f;
const int64 iSTART_MONEY = 100000;

const int64 iMAX_WORK_PROFIT = 50000;
const float fMAX_WORK_TIME = 0.25f;

const int64 iMORTGAGE_COST = 25000;
const int64 iFOOD_COST = 10000;
const int64 iAC_COST = 10000;
const int64 iMEDICINE_COST = 10000;

class Game : public HyEntity2d
{
	Computer			m_Computer;
	Bills				m_Bills;
	Clock				m_Clock;

public:
	Game(HyEntity2d *pParent = nullptr);
	virtual ~Game();

	virtual void OnUpdate() override;

	int64 GetMoney();
	int64 GetCurWorkProfit();
	float GetPercentOfDayLeft();

	void StartDay();
	void EndDay();

	void ShowComputer();
	void HideComputer();

	void BuyCum();
	void BuyGun();
};

#endif // Game_h__
