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

/*virtual*/ void EnemyGums::OnAttackUpdate() /*override*/
{
	if(m_Gums.rot.IsAnimating() == false && m_uiCurHealth > 0)
	{
		if(m_Gums.rot.Get() > 0.0f)
			m_Gums.rot.Tween(-8.0f, 0.3f, HyTween::BounceInOut);
		else
			m_Gums.rot.Tween(8.0f, 0.3f, HyTween::BounceInOut);
	}
}
