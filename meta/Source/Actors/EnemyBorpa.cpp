#include "pch.h"
#include "EnemyBorpa.h"
#include "Game.h"

EnemyBorpa::EnemyBorpa(uint32 uiHealth, float fDeferDuration, HyEntity2d *pParent /*= nullptr*/) :
	IEnemy(uiHealth, fDeferDuration, pParent),
	m_Borpa("Actors", "Borpa", this)
{
	SetTag(TAG_Borpa);
}

/*virtual*/ EnemyBorpa::~EnemyBorpa()
{
}

/*virtual*/ void EnemyBorpa::OnUpdate() /*override*/
{
}

void EnemyBorpa::RunAway()
{
	scale.SetX(-1.0f);
	pos.Tween(-2000.0f, 0.0f, 2.5f, HyTween::QuadIn);
	m_bCanAttack = false;
}
