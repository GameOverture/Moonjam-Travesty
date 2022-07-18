#include "pch.h"
#include "Game.h"

Game::Game(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_Computer(this),
	m_Bills(this),
	m_Clock(this)
{
	m_Computer.Hide(true);
	m_Computer.pos.Set(50.0f, 5.0f);

	m_Bills.Hide(true);	
}

/*virtual*/ Game::~Game()
{
}

/*virtual*/ void Game::OnUpdate() /*override*/
{
	if(HyEngine::Input().IsActionDown(INPUT_DebugCamUp))
		EndDay();
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

void Game::StartDay()
{
	m_Clock.Start();
}

void Game::EndDay()
{
	m_Clock.Stop();
	m_Bills.Assemble(GetCurWorkProfit());
	m_Bills.Load();
	m_Bills.Show();
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
