#include "pch.h"
#include "EnemyBorpa.h"

EnemyBorpa::EnemyBorpa(uint32 uiHealth, float fDeferDuration, HyEntity2d *pParent /*= nullptr*/) :
	IEnemy(uiHealth, fDeferDuration, pParent),
	m_Borpa("Actors", "Borpa", this)
{
}

/*virtual*/ EnemyBorpa::~EnemyBorpa()
{
}

/*virtual*/ void EnemyBorpa::OnUpdate() /*override*/
{
}
