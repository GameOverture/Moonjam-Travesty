#include "pch.h"
#include "Clock.h"
#include "Game.h"

Clock::Clock(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_StaminaBox("UI/Clock", "StaminaBox", this),
	m_StaminaBar("UI/Clock", "StaminaBar", this),
	m_TimeBar(HyPanelInit("UI/Clock", "BarBox"), "", "", this),
	m_DayNight("UI/Clock", "DayNight", this),
	m_Cover("UI/Clock", "Cover", this),
	m_MoneyBox(HyPanelInit("UI/Clock", "MoneyBox"), "UI/Clock", "Text", 2, 2, 2, 2, this)
{
	scale.Set(1.25f, 1.25f);
	UseWindowCoordinates();
	pos.Set(125.0f, HyEngine::Window().GetHeight() - 75.0f);

	m_TimeBar.pos.Offset(60.0f, -12.0f);
	m_TimeBar.SetRange(0, 100);

	m_MoneyBox.pos.SetY(-20.0f);
	m_MoneyBox.SetTextMonospacedDigits(true);
	m_MoneyBox.ShowAsCash(true);
	m_MoneyBox.SetValue(iSTART_MONEY, 0.0f);

	m_Timer.Init(fDAY_LENGTH);

	SetDisplayOrder(DISPLAYORDER_Clock);
}

/*virtual*/ Clock::~Clock()
{
}

/*virtual*/ void Clock::OnUpdate() /*override*/
{

	if(m_Timer.IsRunning())
	{
		float fPercLeft = GetPercentOfDayLeft();
		m_TimeBar.SetValue(100 - static_cast<int32>(fPercLeft * 100.0f));

		m_DayNight.rot.Set(180.0f - (fPercLeft * 180.0f));
	}
}

void Clock::Reset()
{
	m_Timer.Init(fDAY_LENGTH);
	m_TimeBar.SetValue(100);
}

void Clock::Start()
{
	m_Timer.Start();
}

void Clock::Stop()
{
	m_Timer.Pause();
}

int64 Clock::GetMoney()
{
	return m_MoneyBox.GetValue();
}

void Clock::OffsetMoney(int64 iOffsetAmt, float fDuration)
{
	m_MoneyBox.OffsetValue(iOffsetAmt, fDuration);
}

int64 Clock::GetCurWorkProfit()
{
	float fPercLeft = GetPercentOfDayLeft();
	if(fPercLeft < fMAX_WORK_TIME)
	{
		fPercLeft = fPercLeft / fMAX_WORK_TIME;
		return static_cast<int64>(iMAX_WORK_PROFIT * fPercLeft);
	}
	else
		return iMAX_WORK_PROFIT;
}

float Clock::GetPercentOfDayLeft()
{
	return static_cast<float>(m_Timer.TimeLeft() / m_Timer.GetDuration());
}
