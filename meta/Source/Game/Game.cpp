#include "pch.h"
#include "Game.h"

Game::Game(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_Computer(this),
	m_Bills(this),
	m_Clock(this),
	m_BillyChecklist(this)
{
	m_Computer.Hide(true);
	m_Computer.pos.Set(50.0f, 5.0f);

	m_Bills.Hide(true);
	
	m_Clock.SetVisible(false);

	m_BillyChecklist.SetVisible(false);
	m_BillyChecklist.pos.Set(1170, 505);
	m_BillyChecklist.SetDisplayOrder(DISPLAYORDER_Computer);

}

/*virtual*/ Game::~Game()
{
}

/*virtual*/ void Game::OnUpdate() /*override*/
{
}

int64 Game::GetMoney()
{
	return m_Clock.GetMoney();
}

int64 Game::GetCurWorkProfit()
{
	return m_Clock.GetCurWorkProfit();
}

float Game::GetPercentOfDayLeft()
{
	return m_Clock.GetPercentOfDayLeft();
}

int32 Game::GetFoodCount()
{
	return m_BillyChecklist.GetFoodCount();
}

void Game::OnStartDay()
{
	HyLog("Game::OnStartDay()");
	m_Clock.Reset();
	m_Clock.Start();
	m_Clock.SetVisible(true);

	m_BillyChecklist.ResetTasks();
	m_BillyChecklist.SetVisible(true);
}

void Game::OnEndDay()
{
	HyLog("Game::OnEndDay()");
	m_Clock.Pause();
	m_Clock.SetVisible(false);
	m_Computer.Hide();
	
	m_BillyChecklist.OnEndDay();
	m_BillyChecklist.SetVisible(false);

	// TODO:
	HyLogError("TODO REPAIR COST");
	int64 iRepairCost = 0;

	m_Bills.Assemble(GetCurWorkProfit(), iRepairCost, m_BillyChecklist.GetBillyFeels(), m_BillyChecklist.GetBillyGrade());
	m_Bills.Load();
	m_Bills.Show();
}

void Game::OnSleep(bool bBoughtMedicine, bool bBoughtFood)
{
	HyLog("Game::OnSleep()");
	m_Clock.OnSleep();

	m_BillyChecklist.OnSleep(bBoughtMedicine, bBoughtFood);
	m_Bills.Hide();
}

void Game::ShowComputer()
{
	m_Computer.Show();
}

void Game::HideComputer()
{
	m_Computer.Hide();
}

void Game::BuyCum()
{
	m_Clock.OffsetMoney(-iCUM_COST, 1.0f);
}

void Game::BuyGun()
{
	m_Clock.OffsetMoney(-iGUN_COST, 1.0f);
}
