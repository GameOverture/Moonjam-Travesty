#include "pch.h"
#include "EnemyGums.h"

EnemyGums::EnemyGums(uint32 uiHealth, float fDeferDuration, HyEntity2d *pParent /*= nullptr*/) :
	IEnemy(uiHealth, fDeferDuration, pParent),
	m_Gums("Actors", "Gums", this)
{
}

/*virtual*/ EnemyGums::~EnemyGums()
{
}

/*virtual*/ void EnemyGums::OnUpdate() /*override*/
{
}
