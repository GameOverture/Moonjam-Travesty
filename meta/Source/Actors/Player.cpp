#include "pch.h"
#include "Player.h"

#define PLAYER_RADIUS 16.0f

Player::Player(HyEntity2d *pParent /*= nullptr*/) :
	IActor(pParent),
	m_Moon("Actors", "Moon", this),
	m_DebugBody(this),
	m_bInputEnabled(false),
	m_bIsGrounded(false),
	m_bFaceUpwards(false),
	m_pEquipedItem(nullptr)
{
	SetTag(TAG_Player);

	shape.SetAsCircle(PLAYER_RADIUS);
	m_DebugBody.shape.SetAsCircle(PLAYER_RADIUS);
	m_DebugBody.SetVisible(false);

	physics.Init(HYPHYS_Dynamic, false, true);
	physics.SetEnabled(m_bInputEnabled);
	physics.SetSleepingAllowed(false);
	physics.SetCcd(true);
}

/*virtual*/ Player::~Player()
{
}

/*virtual*/ void Player::OnUpdate() /*override*/
{
	if(m_bInputEnabled == false)
		return;

	const float fACCEL_AMT = 20.0f;
	const float fDECEL_AMT = 38.0f;
	const float fMAX_SPEED = 10.0f * m_fMovementMod;
	const float fOUTSIDE_GRAVITY = 50.0f;
	const float fJUMP_PWR = 7.0f * m_fMovementMod;
	
	if(HyEngine::Input().IsActionDown(INPUT_MoveLeft))
	{
		m_vVelocity.x -= fACCEL_AMT * HyEngine::DeltaTime();
	}
	else if(m_vVelocity.x < 0.0f)
	{
		m_vVelocity.x += fDECEL_AMT * HyEngine::DeltaTime();
		m_vVelocity.x = HyClamp(m_vVelocity.x, m_vVelocity.x, 0.0f);
	}

	if(HyEngine::Input().IsActionDown(INPUT_MoveRight))
	{
		m_vVelocity.x += fACCEL_AMT * HyEngine::DeltaTime();
	}
	else if(m_vVelocity.x > 0.0f)
	{
		m_vVelocity.x -= fDECEL_AMT * HyEngine::DeltaTime();
		m_vVelocity.x = HyClamp(m_vVelocity.x, 0.0f, m_vVelocity.x);
	}
	m_vVelocity.x = HyClamp(m_vVelocity.x, -fMAX_SPEED, fMAX_SPEED);

	if(IsOutside() == false)
	{
		if(HyEngine::Input().IsActionDown(INPUT_MoveDown))
		{
			m_vVelocity.y -= fACCEL_AMT * HyEngine::DeltaTime();
		}
		else if(m_vVelocity.y < 0.0f)
		{
			m_vVelocity.y += fDECEL_AMT * HyEngine::DeltaTime();
			m_vVelocity.y = HyClamp(m_vVelocity.y, m_vVelocity.y, 0.0f);
		}

		if(HyEngine::Input().IsActionDown(INPUT_MoveUp))
		{
			m_vVelocity.y += fACCEL_AMT * HyEngine::DeltaTime();
		}
		else if(m_vVelocity.y > 0.0f)
		{
			m_vVelocity.y -= fDECEL_AMT * HyEngine::DeltaTime();
			m_vVelocity.y = HyClamp(m_vVelocity.y, 0.0f, m_vVelocity.y);
		}
		m_vVelocity.y = HyClamp(m_vVelocity.y, -fMAX_SPEED, fMAX_SPEED);
	}

	pos.Offset(m_vVelocity);

	if(IsOutside())
	{
		// Apply gravity
		if(physics.IsSimulating() && m_bIsGrounded == false)
			m_vVelocity.y -= (HyEngine::DeltaTime() * fOUTSIDE_GRAVITY);

		// Handle jump
		if(HyEngine::Input().IsActionDown(INPUT_Jump) && m_bIsGrounded)
		{
			m_vVelocity.y = fJUMP_PWR;
			m_bIsGrounded = false;
		}

		if(m_vVelocity.x < 0.0f)
		{
			FlipX(false);
			SetMoonState(MOONSTATE_SideWalk);
		}
		else if(m_vVelocity.x > 0.0f)
		{
			FlipX(true);
			SetMoonState(MOONSTATE_SideWalk);
		}
		else
			SetMoonState(MOONSTATE_SideIdle);
	}
	else // Inside
	{
		if(m_vVelocity.x == 0.0f && m_vVelocity.y == 0.0f)
		{
			if(m_bFaceUpwards)
				SetMoonState(MOONSTATE_UpIdle);
			else
				SetMoonState(MOONSTATE_SideIdle);
		}
		else
		{
			float fDirection = HyMath::AngleFromVector(m_vVelocity);
			if(fDirection > 0.0f && fDirection < 180.0f)
			{
				m_bFaceUpwards = true;
				FlipX(false);
				if(m_vVelocity.y == 0.0f)
					SetMoonState(MOONSTATE_UpIdle);
				else
					SetMoonState(MOONSTATE_UpWalk);
			}
			else
			{
				m_bFaceUpwards = false;
				if(m_vVelocity.x < 0.0f)
				{
					FlipX(false);
					SetMoonState(MOONSTATE_SideWalk);
				}
				else if(m_vVelocity.x > 0.0f)
				{
					FlipX(true);
					SetMoonState(MOONSTATE_SideWalk);
				}
				else
				{
					if(abs(m_vVelocity.y) > 0.0f)
						SetMoonState(MOONSTATE_SideWalk);
					else
						SetMoonState(MOONSTATE_SideIdle);
				}
			}
		}
	}
}

void Player::EnableInput(bool bEnable)
{
	HySetVec(m_vVelocity, 0.0f, 0.0f);

	if(m_bInputEnabled == bEnable)
		return;

	m_bInputEnabled = bEnable;
	physics.SetEnabled(m_bInputEnabled);
}

bool Player::IsOutside()
{
	if(ParentGet() && ParentGet()->GetTag() == TAG_Outside)
		return true;

	return false;
}

HySprite2d &Player::GetMoonSprite()
{
	return m_Moon;
}

MoonState Player::GetMoonState() const
{
	return static_cast<MoonState>(m_Moon.GetState());
}

void Player::SetMoonState(uint32 uiStateIndex)
{
	m_Moon.SetState(uiStateIndex);
	if(uiStateIndex == MOONSTATE_Pickup)
		m_Moon.SetAnimCtrl(HYANIMCTRL_Reset);
}

void Player::FlipX(bool bFlip)
{
	m_Moon.scale.Set(bFlip ? -1.0f : 1.0, 1.0f);
}

IItem *Player::GetEquipedItem()
{
	return m_pEquipedItem;
}

void Player::SetEquipedItem(IItem *pItem)
{
	if(m_pEquipedItem == pItem)
		return;

	if(m_pEquipedItem)
	{
		ChildRemove(m_pEquipedItem);
		m_pEquipedItem->pos.Set(pos.Get());
		m_pEquipedItem->scale.Set(scale.Get());
	}

	m_pEquipedItem = pItem;
	if(m_pEquipedItem)
	{
		ChildInsert(m_Moon, *m_pEquipedItem);
		m_pEquipedItem->pos.Set(0.0f, 0.0f);
	}
}

void Player::OnTouchGround()
{
	HyLog("OnTouchGround");
	m_vVelocity.y = 0.0f;
	m_bIsGrounded = true;
}

void Player::OnLeaveGround()
{
	HyLog("OnLeaveGround");
	m_bIsGrounded = false;
}
