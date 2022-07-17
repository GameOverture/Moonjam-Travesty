#ifndef Player_h__
#define Player_h__

#include "pch.h"
#include "IItem.h"
#include "IActor.h"

class Player : public IActor
{
	HySprite2d			m_Moon;
	HyPrimitive2d		m_DebugBody;

	glm::vec2			m_vVelocity;

	bool				m_bInputEnabled;
	bool				m_bIsGrounded;
	bool				m_bFaceUpwards;

	IItem *				m_pEquipedItem;

public:
	Player(HyEntity2d *pParent = nullptr);
	virtual ~Player();

	virtual void OnUpdate() override;

	void EnableInput(bool bEnable);
	bool IsOutside();

	HySprite2d &GetMoonSprite();
	MoonState GetMoonState() const;
	void SetMoonState(uint32 uiStateIndex);
	void FlipX(bool bFlip);

	IItem *GetEquipedItem();
	void SetEquipedItem(IItem *pItem);

	void OnTouchGround();
	void OnLeaveGround();
};

#endif // Player_h__
