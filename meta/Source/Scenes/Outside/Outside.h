#ifndef Outside_h__
#define Outside_h__

#include "pch.h"
#include "Player.h"
#include "OutsideContactListener.h"
#include "Cum.h"
#include "Gun.h"
#include "IEnemy.h"

class Outside : public HyPhysicsGrid2d
{
	friend class OutsideContactListener;

	Player &					m_PlayerRef;

	OutsideContactListener		m_OutsideContactListener;

	std::vector<HySprite2d *>	m_SkyList;
	std::vector<HySprite2d *>	m_GrassList;
	std::vector<HySprite2d *>	m_PathList;
	HySprite2d					m_Cottage;

	HyPrimitive2d				m_Ground;
	HyPrimitive2d				m_LeftWall;
	HyPrimitive2d				m_RightWall;

	HyPrimitive2d				m_NightDarkness;

	HyText2d					m_AirText;

	enum OutsideState
	{
		STATE_Inactive,
		STATE_LeavingHouse,
		STATE_Play,
		STATE_EnteringHouse,

		STATE_Attack
	};
	OutsideState				m_eOutsideState;

	// Attack stuff
	std::vector<Cum *>			m_CumList;
	std::vector<Gun *>			m_GunList;

	std::vector<IEnemy *>		m_EnemyList;
	HyStopwatch					m_AttackStopwatch;

	enum AttackState
	{
		ATTACKSTATE_Inactive = 0,
		ATTACKSTATE_Intro,
		ATTACKSTATE_IntroPan,
		ATTACKSTATE_Attacking,
		ATTACKSTATE_Finished
	};
	AttackState					m_eAttackState;
	int32						m_iHouseDamage;

public:
	Outside(Player &playerRef, HyEntity2d *pParent = nullptr);
	virtual ~Outside();

	virtual void OnUpdate() override;

	void Init();
	void Hide();

	void SpawnCum();
	void SpawnGun();

	IItem *FindClosestItem(ItemState eItemState, float fPosX, float &fDistAwayOut);

	void SetupAttack(uint32 uiDayIndex);
	void AttackUpdate();

	void DestroyCum();
	void DestroyGun();

	bool IsAttackFinished();
};

#endif // Outside_h__
