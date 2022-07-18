#include "pch.h"
#include "Gun.h"
#include "Game.h"

Gun::Gun(HyEntity2d *pParent /*= nullptr*/) :
	IItem("Package", fGUN_RANGE, pParent),
	m_Base("Outside/Attack", "GunBot", this),
	m_Top("Outside/Attack", "GunTop", this),
	m_Debug(this)
{
	SetTag(TAG_Gun);

	m_Base.alpha.Set(0.0f);
	m_Top.alpha.Set(0.0f);

	m_Debug.shape.SetAsCircle(glm::vec2(0.0f, 25.0f), 25.0f);
	m_Debug.alpha.Set(0.0f);
}

/*virtual*/ Gun::~Gun()
{
}

/*virtual*/ void Gun::OnUpdate() /*override*/
{
}

/*virtual*/ void Gun::StartSetupLoop(float fDuration) /*override*/
{
	m_Base.alpha.Tween(1.0f, 0.2f);

	m_Top.alpha.Tween(1.0f, fDuration);
	m_Top.scale.Set(0.0001f, 0.0001f);
	m_Top.scale.Tween(1.0f, 1.0f, fDuration);
}
