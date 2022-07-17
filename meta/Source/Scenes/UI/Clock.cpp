#include "pch.h"
#include "Clock.h"

Clock::Clock(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_StaminaBox("UI/Clock", "StaminaBox", this),
	m_StaminaBar("UI/Clock", "StaminaBar", this),
	m_DayNight("UI/Clock", "DayNight", this),
	m_Cover("UI/Clock", "Cover", this)
{
	scale.Set(1.25f, 1.25f);
	UseWindowCoordinates();
	pos.Set(125.0f, HyEngine::Window().GetHeight() - 75.0f);

	SetDisplayOrder(DISPLAYORDER_Clock);
}

/*virtual*/ Clock::~Clock()
{
}

/*virtual*/ void Clock::OnUpdate() /*override*/
{
}
