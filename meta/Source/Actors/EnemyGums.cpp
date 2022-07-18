#include "pch.h"
#include "EnemyGums.h"
#include "Game.h"

EnemyGums::EnemyGums(uint32 uiHealth, float fDeferDuration, HyEntity2d *pParent /*= nullptr*/) :
	IEnemy(uiHealth, fDeferDuration, pParent),
	m_Gums("Actors", "Gums", this)
{
	SetTag(TAG_Gums);

	m_Gums.scale.SetX(-1.0f);
}

/*virtual*/ EnemyGums::~EnemyGums()
{
}

/*virtual*/ void EnemyGums::OnUpdate() /*override*/
{
}
