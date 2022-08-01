#include "pch.h"
#include "Outside.h"
#include "MoonjamTravesty.h"
#include "EnemyGums.h"
#include "EnemyBorpa.h"

#define NUM_SKY_SPRITES 4

#define ACTOR_FOREGROUND_ZOOM 1.4f
#define ACTOR_BACKGROUND_ZOOM 1.0f

#define ACTOR_DOOR_POSX 0.0f
#define ACTOR_DOOR_POSY 25.0f
#define ACTOR_DOOR_DURATION 1.0f

#define ACTOR_ITEM_POSY -50.0f

const float fSETUP_INIT_DURATION = 1.0f;
const float fSETUP_LOOP_DURATION = 4.0f;

const float fMINIMUM_DIST_FROM_DOOR = 200.0f; // Valid item placement

const float fItemHeldPosY = 55.0f;
const float fItemHeldScale = 0.7f;
const float fItemSetupOffsetX = 20.0f;

Outside::Outside(Player &playerRef, HyEntity2d *pParent /*= nullptr*/) :
	HyPhysicsGrid2d(glm::vec2(0.0f, 0.0f), 120.0f),
	m_PlayerRef(playerRef),
	m_eOutsideState(STATE_Inactive),
	m_eAttackState(ATTACKSTATE_Inactive),
	m_iHouseDamage(0),
	m_AudGums("Sounds", "Gums", this),
	m_AudBorpa("Sounds", "Borpa", this),
	m_AudShoot("Sounds", "Shoot", this),
	m_AudTurretTalk("Sounds", "TurretTalk", this),
	m_AudTurretExplode("Sounds", "TurretExplode", this),
	m_AudHouseDamage("Sounds", "HouseDamage", this)
{
	SetTag(TAG_Outside);

	m_b2World.SetContactListener(&m_OutsideContactListener);

	float fStartX = -2000.0f;
	for(uint32 i = 0; i < NUM_SKY_SPRITES; i++)
	{
		HySprite2d *pNewSky = HY_NEW HySprite2d("Outside", "Sky", this);
		pNewSky->pos.Set(fStartX + (i * pNewSky->GetFrameWidth()), 0.0f);
		m_SkyList.push_back(pNewSky);
	}

	for(uint32 i = 0; i < 4; i++)
	{
		HySprite2d *pNewGrass = HY_NEW HySprite2d("Outside", "Grass", this);
		pNewGrass->pos.Set(fStartX + (i * pNewGrass->GetFrameWidth()), 50.0f);
		m_GrassList.push_back(pNewGrass);
	}

	fStartX = -2122.0f;
	for(uint32 i = 0; i < 15; i++)
	{
		HySprite2d *pNewPath = HY_NEW HySprite2d("Outside", "Path", this);
		if(i == 7) // Entry path
			pNewPath->SetState(1);
		pNewPath->pos.Set(fStartX, 0.0f);
		fStartX += pNewPath->GetFrameWidth();
		
		m_PathList.push_back(pNewPath);
	}

	m_Cottage.Init("Outside", "Cottage", this);

	m_Ground.SetTag(TAG_Ground);
	m_Ground.SetVisible(false);
	m_Ground.shape.SetAsBox(4000.0f, 75.0f);
	m_Ground.pos.Set(-2000.0f, -100.0f);
	m_Ground.physics.Init(HYPHYS_Static);
	m_Ground.physics.SetEnabled(true);
	ChildAppend(m_Ground);

	m_LeftWall.shape.SetAsBox(2.0f, 1000.0f);
	m_LeftWall.pos.Set(fLEFT_BOUNDS, 0.0f);
	ChildAppend(m_LeftWall);

	m_RightWall.shape.SetAsBox(2.0f, 1000.0f);
	m_RightWall.pos.Set(fRIGHT_BOUNDS, 0.0f);
	ChildAppend(m_RightWall);

	m_NightDarkness.UseWindowCoordinates();
	m_NightDarkness.shape.SetAsBox(HyEngine::Window().GetWidthF(), HyEngine::Window().GetHeightF());
	m_NightDarkness.SetTint(HyColor::Black);
	m_NightDarkness.alpha.Set(0.0f);
	m_NightDarkness.SetDisplayOrder(DISPLAYORDER_DarkOverlay);
	ChildAppend(m_NightDarkness);

	m_AirText.Init("", "Main", this);
	m_AirText.SetDisplayOrder(DISPLAYORDER_DarkOverlay + 1);
	m_AirText.UseWindowCoordinates();
	m_AirText.SetTextAlignment(HYALIGN_Center);
	m_AirText.pos.Set(HyEngine::Window().GetWidthF(0.5f), HyEngine::Window().GetHeightF(0.75f));
	m_AirText.alpha.Set(0.0f);
}

/*virtual*/ Outside::~Outside()
{
	for(auto *pNode : m_SkyList)
		delete pNode;
	for(auto *pNode : m_GrassList)
		delete pNode;
	for(auto *pNode : m_PathList)
		delete pNode;

	for(auto *pNode : m_CumList)
		delete pNode;
	for(auto *pNode : m_GunList)
		delete pNode;
}

/*virtual*/ void Outside::OnUpdate() /*override*/
{
	m_OutsideContactListener.ProcessQueue(*this);

	float fPercDayLeft = MoonjamTravesty::GetGame().GetPercentOfDayLeft();
	m_NightDarkness.alpha.Set(0.72f * (1.0f - fPercDayLeft));
	for(auto *pSkySprite : m_SkyList)
		pSkySprite->SetTint(HyColor(fPercDayLeft, fPercDayLeft, fPercDayLeft));

	if(m_eOutsideState != STATE_Inactive)
	{
		if(m_PlayerRef.pos.Y() < -42.0f)
			m_PlayerRef.pos.SetY(120.0f);
	}

	switch(m_eOutsideState)
	{
	case STATE_Inactive:
		break;

	case STATE_LeavingHouse:
		if(m_PlayerRef.scale.IsAnimating() == false)
		{
			m_PlayerRef.EnableInput(true);
			m_eOutsideState = STATE_Play;
		}
		break;

	case STATE_Play: {

		// Camera logic
		HyCamera2d *pCamera = HyEngine::Window().GetCamera2d(0);
		const float fDeadZoneAmt = HyEngine::Window().GetWidthF(0.4f);
		auto worldBoundsAabb = pCamera->GetWorldViewBounds();
		float fWorldBoundsLeft = worldBoundsAabb.lowerBound.x + fDeadZoneAmt;
		float fWorldBoundsRight = worldBoundsAabb.upperBound.x - fDeadZoneAmt;

		if(m_PlayerRef.pos.X() < fWorldBoundsLeft)
			pCamera->pos.Offset(m_PlayerRef.pos.X() - fWorldBoundsLeft, 0.0f);
		if(m_PlayerRef.pos.X() > fWorldBoundsRight)
			pCamera->pos.Offset(m_PlayerRef.pos.X() - fWorldBoundsRight, 0.0f);

		if(m_PlayerRef.pos.X() < fLEFT_BOUNDS)
			m_PlayerRef.pos.SetX(fLEFT_BOUNDS);
		if(m_PlayerRef.pos.X() > fRIGHT_BOUNDS)
			m_PlayerRef.pos.SetX(fRIGHT_BOUNDS);

		// Enter House logic
		if(HyEngine::Input().IsActionDown(INPUT_MoveUp) &&
			m_PlayerRef.GetEquipedItem() == nullptr &&
			m_PlayerRef.pos.X() > -32.0f &&
			m_PlayerRef.pos.X() < 32.0f)
		{
			m_PlayerRef.EnableInput(false);
			m_PlayerRef.pos.SetX(ACTOR_DOOR_POSX);
			m_PlayerRef.pos.Tween(ACTOR_DOOR_POSX, ACTOR_DOOR_POSY, ACTOR_DOOR_DURATION);
			m_PlayerRef.scale.Tween(ACTOR_BACKGROUND_ZOOM, ACTOR_BACKGROUND_ZOOM, ACTOR_DOOR_DURATION);
			m_PlayerRef.SetMoonState(MOONSTATE_UpWalk);
			m_eOutsideState = STATE_EnteringHouse;
		}

		// Item handling logic
		if(m_PlayerRef.GetEquipedItem() == nullptr)
		{
			if(m_PlayerRef.IsGrounded() && HyEngine::Input().IsActionDown(INPUT_Action))
			{
				// Try and pick up item
				const float fMINIMUM_DIST = 20.0f;
				float fDistAway = 0.0f;
				IItem *pItemToPickup = FindClosestItem(ITEMSTATE_Packaged, m_PlayerRef.pos.X(), fDistAway);
				if(pItemToPickup && fDistAway <= fMINIMUM_DIST)
				{
					m_PlayerRef.SetEquipedItem(pItemToPickup);
					m_PlayerRef.EnableInput(false);
					HyLog("EnableInput: false - Picking up item");
					m_PlayerRef.SetMoonState(MOONSTATE_Pickup);

					pItemToPickup->GetPackage().pos.Set(0.0f, fItemHeldPosY);
					pItemToPickup->GetPackage().scale.Set(fItemHeldScale, fItemHeldScale);
				}
			}
		}
		else // Has item equipped
		{
			IItem *pItem = m_PlayerRef.GetEquipedItem();
			switch(pItem->GetItemState())
			{
			case ITEMSTATE_Packaged:
				if(m_PlayerRef.GetMoonSprite().IsAnimFinished())
				{
					m_PlayerRef.SetMoonState(MOONSTATE_SideIdle);
					m_PlayerRef.EnableInput(true);
					HyLog("EnableInput: true - Finished item pickup");

					pItem->SetItemState(ITEMSTATE_Held);
				}
				break;

			case ITEMSTATE_Held:
				if(m_PlayerRef.IsGrounded() && HyEngine::Input().IsActionDown(INPUT_Action))
				{
					if(m_PlayerRef.pos.X() < -fMINIMUM_DIST_FROM_DOOR)
					{
						m_PlayerRef.EnableInput(false);
						HyLog("EnableInput: false - item in setup init");
						m_PlayerRef.SetMoonState(MOONSTATE_Pickup);

						bool bFlipped = (m_PlayerRef.GetMoonSprite().scale.X() < 0.0f);
						pItem->GetPackage().pos.Tween(bFlipped ? fItemSetupOffsetX : -fItemSetupOffsetX, fItemHeldPosY, fSETUP_INIT_DURATION, HyTween::BounceInOut);
						pItem->GetPackage().rot.Tween(bFlipped ? -170.0f : 170.0f, fSETUP_INIT_DURATION);
						pItem->SetItemState(ITEMSTATE_SetupInit);
					}
					else
					{
						m_PlayerRef.GetLabel().SetText("Too close to house!");
						m_PlayerRef.GetLabel().SetVisible(true);
						m_PlayerRef.GetLabel().alpha.Tween(1.0f, 1.42f, HyTween::QuadOut, [](IHyNode *pThis) { static_cast<HyLabel *>(pThis)->alpha.Tween(0.0f, 0.33f); });
					}
				}
				break;

			case ITEMSTATE_SetupInit:
				if(HyEngine::Input().IsActionDown(INPUT_Action) == false)
				{
					// Stop setting up item and reset
					pItem->GetPackage().pos.Set(0.0f, fItemHeldPosY);
					pItem->GetPackage().scale.Set(fItemHeldScale, fItemHeldScale);
					pItem->GetPackage().rot.Set(0.0f);
					pItem->SetItemState(ITEMSTATE_Held);

					m_PlayerRef.SetMoonState(MOONSTATE_SideIdle);
					m_PlayerRef.EnableInput(true);
					HyLog("EnableInput: true - canceling item setup");
				}
				else if(pItem->GetPackage().pos.IsAnimating() == false)
				{
					m_PlayerRef.SetMoonState(MOONSTATE_Action);

					bool bFlipped = (m_PlayerRef.GetMoonSprite().scale.X() < 0.0f);

					pItem->GetPackage().pos.Tween((bFlipped ? fItemSetupOffsetX : -fItemSetupOffsetX) * 0.5f, fItemHeldPosY - 5, fSETUP_LOOP_DURATION, HyTween::BounceInOut);
					pItem->SetDisplayOrder(DISPLAYORDER_ItemSetup);
					pItem->SetItemState(ITEMSTATE_SetupLoop);
					pItem->StartSetupLoop(fSETUP_LOOP_DURATION);
				}
				break;

			case ITEMSTATE_SetupLoop:
				if(pItem->GetPackage().pos.IsAnimating() == false)
				{
					pItem->GetPackage().alpha.Tween(0.0f, 0.2f);
					// Finished setting up
					m_PlayerRef.EnableInput(true);
					HyLog("EnableInput: true - item activated");
					m_PlayerRef.SetEquipedItem(nullptr);

					pItem->SetItemState(ITEMSTATE_Active);

					if(pItem->GetTag() == TAG_Gun)
					{
						m_PlayerRef.pos.Set(m_PlayerRef.pos.X(), 100.0f);
						pItem->shape.SetAsCircle(glm::vec2(0.0f, 25.0f), 25.0f);
						//pItem->shape.SetAsBox(50.0f, 50.0f);
						pItem->physics.Init(HYPHYS_Static);
						ChildAppend(*pItem);
					}
					else // Cum
					{
						pItem->shape.SetAsBox(pItem->GetRange() * 0.5f, 50.0f, glm::vec2(0.0f, 0.0f), 0.0f);
						pItem->physics.Init(HYPHYS_Static);
						pItem->physics.SetSensor(true);
						ChildAppend(*pItem);
					}
				}
				break;
			}
		}
		break; }

	case STATE_EnteringHouse:
		if(m_PlayerRef.pos.IsAnimating() == false)
		{
			MoonjamTravesty::EnterHouse();
			m_eOutsideState = STATE_Inactive;
		}
		break;

	case STATE_Attack:
		AttackUpdate();
		break;
	}

	//if(HyEngine::Input().IsActionReleased(INPUT_DebugSpawnCum))
	//	SpawnCum();
	//if(HyEngine::Input().IsActionReleased(INPUT_DebugSpawnGun))
	//	SpawnGun();
}

int32 Outside::GetHouseDamage()
{
	return m_iHouseDamage;
}

void Outside::Init()
{
	SetVisible(true);
	HyEngine::Window().GetCamera2d(0)->SetZoom(1.0f);
	HyEngine::Window().GetCamera2d(0)->pos.Set(0.0f, 275.0f);

	m_PlayerRef.physics.SetEnabled(false);
	ChildAppend(m_PlayerRef);
	m_PlayerRef.EnableInput(false);
	m_PlayerRef.SetMoonState(MOONSTATE_SideWalk);
	m_PlayerRef.pos.Set(ACTOR_DOOR_POSX, ACTOR_DOOR_POSY);
	m_PlayerRef.scale.Set(ACTOR_BACKGROUND_ZOOM, ACTOR_BACKGROUND_ZOOM);
	m_PlayerRef.rot.Set(0.0f);

	m_PlayerRef.pos.Tween(0.0f, 0.0f, ACTOR_DOOR_DURATION);
	m_PlayerRef.scale.Tween(ACTOR_FOREGROUND_ZOOM, ACTOR_FOREGROUND_ZOOM, ACTOR_DOOR_DURATION);

	m_LeftWall.alpha.Set(1.0f);

	m_eOutsideState = STATE_LeavingHouse;
}

void Outside::Hide()
{
	SetVisible(false);
}

void Outside::SpawnCum()
{
	Cum *pNewCum = HY_NEW Cum(this);
	pNewCum->pos.Set(HyRand::Range(50.0f, fRIGHT_BOUNDS - 100.0f), ACTOR_ITEM_POSY);
	pNewCum->Load();
	m_CumList.push_back(pNewCum);
}

void Outside::SpawnGun()
{
	Gun *pNewGun = HY_NEW Gun(this);
	pNewGun->pos.Set(HyRand::Range(50.0f, fRIGHT_BOUNDS - 100.0f), ACTOR_ITEM_POSY);
	pNewGun->Load();
	m_GunList.push_back(pNewGun);
}

IItem *Outside::FindClosestItem(ItemState eItemState, float fPosX, float &fDistAwayOut)
{
	IItem *pItemToPickup = nullptr;
	for(auto *pItem : m_CumList)
	{
		if(pItem->GetItemState() != ITEMSTATE_Packaged)
			continue;

		float fDist = abs(fPosX - pItem->pos.X());

		if(pItemToPickup)
		{
			float fCurItemDist = abs(fPosX - pItemToPickup->pos.X());
			if(fDist < fCurItemDist)
			{
				pItemToPickup = pItem;
				fDistAwayOut = fDist;
			}
		}
		else
		{
			pItemToPickup = pItem;
			fDistAwayOut = fDist;
		}
	}
	for(auto *pItem : m_GunList)
	{
		if(pItem->GetItemState() != ITEMSTATE_Packaged)
			continue;

		float fDist = abs(fPosX - pItem->pos.X());

		if(pItemToPickup)
		{
			float fCurItemDist = abs(fPosX - pItemToPickup->pos.X());
			if(fDist < fCurItemDist)
			{
				pItemToPickup = pItem;
				fDistAwayOut = fDist;
			}
		}
		else
		{
			pItemToPickup = pItem;
			fDistAwayOut = fDist;
		}
	}

	return pItemToPickup;
}

void Outside::SetupAttack(uint32 uiDayIndex)
{
	for(auto *pEnemy : m_EnemyList)
		delete pEnemy;
	m_EnemyList.clear();

	switch(uiDayIndex)
	{
	case 0:
		m_EnemyList.push_back(HY_NEW EnemyGums(2, 0.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(2, 2.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyBorpa(2, 4.0f, this));
		break;

	case 1:
		m_EnemyList.push_back(HY_NEW EnemyGums(2, 0.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(2, 2.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyBorpa(2, 4.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(2, 6.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(2, 8.0f, this));
		break;

	case 2:
		m_EnemyList.push_back(HY_NEW EnemyBorpa(2, 0.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(2, 2.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(2, 3.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyBorpa(2, 4.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(2, 6.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(2, 7.0f, this));
		break;

	case 3:
		m_EnemyList.push_back(HY_NEW EnemyGums(3, 0.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyBorpa(3, 1.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(3, 2.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyBorpa(3, 3.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(3, 4.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(3, 5.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyBorpa(3, 6.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(3, 7.0f, this));
		break;

	default:
		m_EnemyList.push_back(HY_NEW EnemyGums(4, 0.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(4, 1.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyBorpa(4, 2.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(4, 3.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyBorpa(4, 4.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(4, 5.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(4, 6.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyBorpa(4, 7.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyBorpa(4, 8.0f, this));
		m_EnemyList.push_back(HY_NEW EnemyGums(4, 9.0f, this));
		break;
	}
	for(auto *pEnemy : m_EnemyList)
	{
		pEnemy->SetDisplayOrder(DISPLAYORDER_Enemies);
		pEnemy->pos.Set(-2000.0f, 0.0f);
		pEnemy->Load();
	}

	SetVisible(true);
	HyEngine::Window().GetCamera2d(0)->SetZoom(1.0f);
	HyEngine::Window().GetCamera2d(0)->pos.Set(0.0f, 275.0f);

	m_LeftWall.alpha.Set(0.0f);

	m_PlayerRef.pos.Set(850.0f, 200.0f);

	m_iHouseDamage = 0;
	m_AttackStopwatch.Reset();
	m_AttackStopwatch.Start();
	m_eOutsideState = STATE_Attack;
	m_eAttackState = ATTACKSTATE_Intro;
}

void Outside::AttackUpdate()
{
	switch(m_eAttackState)
	{
	case ATTACKSTATE_Inactive:
		break;

	case ATTACKSTATE_Intro:
		if(m_AttackStopwatch.TimeElapsed() >= 2.0f)
		{
			m_AirText.SetText("Meanwhile...");
			m_AirText.alpha.Set(0.0f);
			m_AirText.alpha.Tween(1.0f, 0.5f);
			HyEngine::Window().GetCamera2d(0)->pos.Tween(-1200.0f, 275.0f, 2.0f, HyTween::QuadInOut);
			m_eAttackState = ATTACKSTATE_IntroPan;
		}
		break;

	case ATTACKSTATE_IntroPan:
		if(HyEngine::Window().GetCamera2d(0)->pos.IsAnimating() == false)
		{
			m_AirText.alpha.Tween(0.0f, 0.5f);

			m_AttackStopwatch.Reset();
			m_AttackStopwatch.Start();
			m_eAttackState = ATTACKSTATE_Attacking;
		}
		break;

	case ATTACKSTATE_Attacking: {
		for(auto *pEnemy : m_EnemyList)
		{
			if(m_AttackStopwatch.TimeElapsed() > pEnemy->GetDeferTime())
			{
				if(pEnemy->HasWarcry() == false)
				{
					if(pEnemy->GetTag() == TAG_Borpa)
						m_AudBorpa.Play();
					else
						m_AudGums.Play();
					pEnemy->DoWarcry();
				}

				pEnemy->AttackUpdate();
			}
		}

		bool bAttackOngoing = false;
		for(auto *pEnemy : m_EnemyList)
		{
			if(pEnemy->CanAttack())
			{
				if(HyEngine::Window().GetCamera2d(0)->pos.X() < pEnemy->pos.X())
					HyEngine::Window().GetCamera2d(0)->pos.SetX(pEnemy->pos.X());

				if(pEnemy->pos.X() > -32.0f)
				{
					m_AudHouseDamage.Play();
					pEnemy->AttackHouse();
					m_iHouseDamage++;
				}
				else
					bAttackOngoing = true;
			}
		}

		// Update shooting
		for(auto *pGun : m_GunList)
		{
			if(pGun->CanShoot() == false || pGun->GetItemState() != ITEMSTATE_Active)
				continue;

			float fFireThreshold = pGun->pos.X();
			fFireThreshold -= pGun->GetRange();

			for(auto *pEnemy : m_EnemyList)
			{
				if(pEnemy->CanAttack() && pEnemy->pos.X() >= fFireThreshold)
				{
					m_AudShoot.Play();
					pGun->Shoot(pEnemy->pos.X());
					pEnemy->TakeDamage();
					break;
				}
			}
		}

		if(bAttackOngoing == false)
		{
			m_AttackStopwatch.Reset();
			m_AttackStopwatch.Start();
			m_eAttackState = ATTACKSTATE_Outro;
		}
		break; }

	case ATTACKSTATE_Outro:
		if(m_AttackStopwatch.TimeElapsed() > 6.0f)
		{
			for(auto *pEnemy : m_EnemyList)
				delete pEnemy;
			m_EnemyList.clear();

			m_eAttackState = ATTACKSTATE_Finished;
		}
		break;

	case ATTACKSTATE_Finished:
		break;
	}
}

void Outside::DestroyCum()
{
	float fLeftMostPosX = 999.0f;
	Cum *pCumToDelete = nullptr;
	for(auto *pItem : m_CumList)
	{
		if(pItem->pos.X() < fLeftMostPosX)
		{
			pCumToDelete = pItem;
			fLeftMostPosX = pItem->pos.X();
		}
	}

	if(pCumToDelete)
	{
		for(auto iter = m_CumList.begin(); iter != m_CumList.end(); ++iter)
		{
			if(pCumToDelete == (*iter))
			{
				delete (*iter);
				m_CumList.erase(iter);
				break;
			}
		}
	}

	// Find rightmost borpa to remove
	float fRightMostPosX = -9999.0f;
	EnemyBorpa *pBorpa = nullptr;
	for(auto iter = m_EnemyList.begin(); iter != m_EnemyList.end(); ++iter)
	{
		if((*iter)->GetTag() == TAG_Borpa)
		{
			if((*iter)->pos.X() > fRightMostPosX)
			{
				pBorpa = static_cast<EnemyBorpa *>(*iter);
				fRightMostPosX = (*iter)->pos.X();
			}
		}
	}
	if(pBorpa)
		pBorpa->RunAway();
}

void Outside::DestroyGun()
{
	float fLeftMostPosX = 999.0f;
	Gun *pGunToDelete = nullptr;
	for(auto *pItem : m_GunList)
	{
		if(pItem->pos.X() < fLeftMostPosX)
		{
			pGunToDelete = pItem;
			fLeftMostPosX = pItem->pos.X();
		}
	}

	if(pGunToDelete)
	{
		m_AudTurretTalk.Play();
		m_AudTurretExplode.Play();

		for(auto iter = m_GunList.begin(); iter != m_GunList.end(); ++iter)
		{
			if(pGunToDelete == (*iter))
			{
				delete (*iter);
				m_GunList.erase(iter);
				break;
			}
		}
	}


	// Consume enemy that destroyed gun
	float fRightMostPosX = -9999.0f;
	IEnemy *pEnemy = nullptr;
	for(auto iter = m_EnemyList.begin(); iter != m_EnemyList.end(); ++iter)
	{
		if((*iter)->pos.X() > fRightMostPosX)
		{
			pEnemy = (*iter);
			fRightMostPosX = (*iter)->pos.X();
		}
	}
	if(pEnemy)
		pEnemy->Kill();
}

bool Outside::IsAttackFinished()
{
	return m_eAttackState == ATTACKSTATE_Finished;
}
