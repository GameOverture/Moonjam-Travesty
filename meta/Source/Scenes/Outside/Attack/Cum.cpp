#include "pch.h"
#include "Cum.h"

#define fCUM_RANGE 200.0f

Cum::Cum(HyEntity2d *pParent /*= nullptr*/) :
	IItem("Cum", fCUM_RANGE, pParent),
	m_Ground(this)
{
	SetTag(TAG_Cum);

	m_Ground.alpha.Set(0.0f);
	m_Ground.shape.SetAsCircle(m_fEFFECTIVE_RANGE * 0.5f);
	m_Ground.scale.Set(1.0f, 0.25f);
}

/*virtual*/ Cum::~Cum()
{
}

/*virtual*/ void Cum::OnUpdate() /*override*/
{
}

/*virtual*/ void Cum::StartSetupLoop(float fDuration) /*override*/
{
	m_Ground.alpha.Tween(1.0f, fDuration);
	m_Ground.scale.Set(0.1f, 0.5f);
	m_Ground.scale.Tween(1.0f, 0.25f, fDuration, HyTween::BounceOut);
}
