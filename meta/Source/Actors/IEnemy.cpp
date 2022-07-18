#include "pch.h"
#include "IEnemy.h"

const float fEmoteScale = 0.25f;
const float fHeartSpacing = 5.0f;

IEnemy::IEnemy(uint32 uiMaxHealth, float fDeferDuration, HyEntity2d *pParent /*= nullptr*/) :
	IActor(pParent),
	m_uiCurHealth(uiMaxHealth),
	m_fDeferDuration(fDeferDuration)
{
	HyAssert(uiMaxHealth > 0, "Bad max health specified");
	for(uint32 i = 0; i < m_uiCurHealth; ++i)
	{
		HySprite2d *pNewSprite = HY_NEW HySprite2d("Actors", "EnemyHeart", this);
		pNewSprite->scale.Set(fEmoteScale, fEmoteScale);
		m_HeartList.push_back(pNewSprite);
	}

	float fTotalWidth = m_uiCurHealth * (m_HeartList[0]->GetFrameWidth(fEmoteScale) + fHeartSpacing);
	//fTotalWidth -= fHeartSpacing;

	float fStartPosX = fTotalWidth * 0.5f;
	for(uint32 i = 0; i < m_uiCurHealth; ++i)
		m_HeartList[i]->pos.Set(fStartPosX + (i * m_HeartList[0]->GetFrameWidth(fEmoteScale) + fHeartSpacing), 125.0f);
}

/*virtual*/ IEnemy::~IEnemy()
{
	for(auto *pHeart : m_HeartList)
		delete pHeart;
}

/*virtual*/ void IEnemy::OnUpdate() /*override*/
{
}

void IEnemy::TakeDamage()
{
	m_HeartList[m_uiCurHealth - 1]->pos.TweenOffset(0.0f, 32.0f, 0.5f, HyTween::QuadOut);
	m_HeartList[m_uiCurHealth - 1]->alpha.Tween(0.0f, 0.5f);

	m_uiCurHealth--;

	if(m_uiCurHealth == 0)
	{
	}
}
