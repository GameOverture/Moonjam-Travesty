#include "pch.h"
#include "IEnemy.h"
#include "Game.h"

const float fEmoteScale = 0.25f;
const float fHeartSpacing = 5.0f;

IEnemy::IEnemy(uint32 uiMaxHealth, float fDeferDuration, HyEntity2d *pParent /*= nullptr*/) :
	IActor(pParent),
	m_uiCurHealth(uiMaxHealth),
	m_fDeferDuration(fDeferDuration),
	//m_Debug(this),
	m_bCanAttack(true)
{
	HyAssert(uiMaxHealth > 0, "Bad max health specified");
	for(uint32 i = 0; i < m_uiCurHealth; ++i)
	{
		HySprite2d *pNewSprite = HY_NEW HySprite2d("Actors", "EnemyHeart", this);
		pNewSprite->scale.Set(fEmoteScale, fEmoteScale);
		m_HeartList.push_back(pNewSprite);
	}

	float fTotalWidth = m_uiCurHealth * (m_HeartList[0]->GetFrameWidth(fEmoteScale) + fHeartSpacing);
	fTotalWidth -= fHeartSpacing;

	float fStartPosX = fTotalWidth * -0.5f;
	for(uint32 i = 0; i < m_uiCurHealth; ++i)
		m_HeartList[i]->pos.Set(fStartPosX + (i * m_HeartList[0]->GetFrameWidth(fEmoteScale) + fHeartSpacing), 80.0f);
}

/*virtual*/ IEnemy::~IEnemy()
{
	for(auto *pHeart : m_HeartList)
		delete pHeart;
}

/*virtual*/ void IEnemy::OnUpdate() /*override*/
{
}

bool IEnemy::CanAttack()
{
	return m_bCanAttack;
}

float IEnemy::GetDeferTime()
{
	return m_fDeferDuration;
}

void IEnemy::TakeDamage()
{
	if(m_uiCurHealth == 0)
		return;

	m_HeartList[m_uiCurHealth - 1]->pos.TweenOffset(0.0f, 32.0f, 0.5f, HyTween::QuadOut);
	m_HeartList[m_uiCurHealth - 1]->alpha.Tween(0.0f, 0.5f);

	m_uiCurHealth--;

	if(m_uiCurHealth == 0)
		Kill();
}

void IEnemy::AttackUpdate()
{
	if(m_bCanAttack)
	{
		if(GetTag() == TAG_Borpa)
			pos.Offset(fBORPA_MOVEMENT * m_fMovementMod * HyEngine::DeltaTime(), 0.0f);
		else
			pos.Offset(fGUMS_MOVEMENT * m_fMovementMod * HyEngine::DeltaTime(), 0.0f);
	}

	if(pos.X() > fLEFT_BOUNDS - 42.0f)
	{
		//m_Debug.shape.SetAsCircle(glm::vec2(0.0f, 32.0f), 25.0f);

		shape.SetAsCircle(glm::vec2(0.0f, 32.0f), 25.0f);
		physics.Init(HYPHYS_Dynamic);
		//pEnemy->physics.SetSensor(true);
	}
}

void IEnemy::Kill()
{
	for(int i = 0; i < m_uiCurHealth; ++i)
		TakeDamage();

	rot.Tween(180.0f, 1.0f, HyTween::BounceInOut);
	m_bCanAttack = false;
}

void IEnemy::AttackHouse()
{
	rot.Tween(90.0f, 2.0f, HyTween::BounceInOut);
	pos.Tween(0.0f, 100.0f, 2.0f, HyTween::BounceInOut);
	alpha.Tween(0.0f, 3.0f, HyTween::QuadOut);
	m_bCanAttack = false;
}
