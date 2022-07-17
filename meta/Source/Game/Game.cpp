#include "pch.h"
#include "Game.h"

Game::Game(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_Computer(this),
	m_Clock(this)
{
	m_Computer.Hide(true);
	m_Computer.pos.Set(50.0f, 5.0f);
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

void Game::StartDay()
{
	m_Clock.Start();
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
