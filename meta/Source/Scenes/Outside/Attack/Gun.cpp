#include "pch.h"
#include "Gun.h"
#include "Game.h"

Gun::Gun(HyEntity2d *pParent /*= nullptr*/) :
	IItem("Package", fGUN_RANGE, pParent),
	m_Base("Outside/Attack", "GunBot", this),
	m_Top("Outside/Attack", "GunTop", this),
	m_Debug(this),
	m_CoolDownBar(HyPanelInit("Actors", "ProgBar"), "", "", 0, 12, 0, 12)
{
	SetTag(TAG_Gun);

	m_Base.alpha.Set(0.0f);
	m_Top.alpha.Set(0.0f);

	m_Debug.shape.SetAsCircle(glm::vec2(0.0f, 25.0f), 25.0f);
	m_Debug.alpha.Set(0.0f);

	m_CoolDownBar.SetRange(0, 100);
	m_CoolDownBar.alpha.Set(0.0f);
}

/*virtual*/ Gun::~Gun()
{
}

/*virtual*/ void Gun::OnUpdate() /*override*/
{
	m_CoolDownBar.pos.Set(pos);
	m_CoolDownBar.pos.Offset(-32.0f, 75.0f);

	if(m_CoolDownBar.alpha.Get() != 0.0f)
		m_CoolDownBar.SetValue(static_cast<int32>(100.0f * (m_CoolDownStopwatch.TimeElapsed() / fSHOOT_COOLDOWN)));

	if(m_CoolDownBar.alpha.Get() != 0.0f && m_CoolDownStopwatch.TimeElapsed() > fSHOOT_COOLDOWN)
	{
		m_CoolDownBar.alpha.Set(0.0f);
		m_CoolDownBar.SetValue(0);
	}
}

/*virtual*/ void Gun::StartSetupLoop(float fDuration) /*override*/
{
	m_Base.alpha.Tween(1.0f, 0.2f);

	m_Top.alpha.Tween(1.0f, fDuration);
	m_Top.scale.Set(0.0001f, 0.0001f);
	m_Top.scale.Tween(1.0f, 1.0f, fDuration);
}

bool Gun::CanShoot()
{
	return m_CoolDownBar.alpha.Get() == 0.0f;
}

void Gun::Shoot(float fShootLocation)
{
	m_CoolDownStopwatch.Reset();
	m_CoolDownStopwatch.Start();
	m_CoolDownBar.alpha.Set(1.0f);
}
