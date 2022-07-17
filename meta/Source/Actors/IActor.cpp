#include "pch.h"
#include "IActor.h"

IActor::IActor(HyEntity2d *pParent /*= nullptr*/) :
	HyEntity2d(pParent),
	m_fMovementMod(1.0f)
{
}

/*virtual*/ IActor::~IActor()
{
}

/*virtual*/ void IActor::OnUpdate() /*override*/
{
}

void IActor::SetMoveModifer(float fMoveMod)
{
	m_fMovementMod = fMoveMod;
}
