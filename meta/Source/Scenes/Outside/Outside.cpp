#include "pch.h"
#include "Outside.h"
#include "MoonjamTravesty.h"

#define ACTOR_FOREGROUND_ZOOM 1.4f
#define ACTOR_BACKGROUND_ZOOM 1.0f

#define ACTOR_DOOR_POSX 0.0f
#define ACTOR_DOOR_POSY 25.0f
#define ACTOR_DOOR_DURATION 1.0f

#define ACTOR_ITEM_POSY -50.0f

const float fSETUP_INIT_DURATION = 1.0f;
const float fSETUP_LOOP_DURATION = 4.0f;

const float fMINIMUM_DIST_FROM_DOOR = 100.0f; // Valid item placement

const float fItemHeldPosY = 55.0f;
const float fItemHeldScale = 0.7f;
const float fItemSetupOffsetX = 20.0f;

Outside::Outside(Player &playerRef, HyEntity2d *pParent /*= nullptr*/) :
	HyPhysicsGrid2d(glm::vec2(0.0f, 0.0f), 120.0f),
	m_PlayerRef(playerRef),
	m_eOutsideState(STATE_Inactive)
{
	SetTag(TAG_Outside);

	m_b2World.SetContactListener(&m_OutsideContactListener);

	float fStartX = -2000.0f;
	for(uint32 i = 0; i < 4; i++)
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

	m_LeftWall.shape.SetAsBox(75.0f, 1000.0f);
	m_LeftWall.pos.Set(-2000.0f, -100.0f);
	m_LeftWall.physics.Init(HYPHYS_Static);
	m_LeftWall.physics.SetEnabled(true);
	ChildAppend(m_LeftWall);

	m_RightWall.shape.SetAsBox(75.0f, 1000.0f);
	m_RightWall.pos.Set(2000.0f, -100.0f);
	m_RightWall.physics.Init(HYPHYS_Static);
	m_RightWall.physics.SetEnabled(true);
	ChildAppend(m_RightWall);
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
			if(HyEngine::Input().IsActionDown(INPUT_Action))
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
				if(HyEngine::Input().IsActionDown(INPUT_Action) && m_PlayerRef.pos.X() < -fMINIMUM_DIST_FROM_DOOR)
				{
					m_PlayerRef.EnableInput(false);
					HyLog("EnableInput: false - item in setup init");
					m_PlayerRef.SetMoonState(MOONSTATE_Pickup);

					bool bFlipped = (m_PlayerRef.GetMoonSprite().scale.X() < 0.0f);
					pItem->GetPackage().pos.Tween(bFlipped ? fItemSetupOffsetX : -fItemSetupOffsetX, fItemHeldPosY, fSETUP_INIT_DURATION, HyTween::BounceInOut);
					pItem->GetPackage().rot.Tween(bFlipped ? -170.0f : 170.0f, fSETUP_INIT_DURATION);
					pItem->SetItemState(ITEMSTATE_SetupInit);
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
	}

	if(HyEngine::Input().IsActionReleased(INPUT_DebugSpawnCum))
		SpawnCum();
	if(HyEngine::Input().IsActionReleased(INPUT_DebugSpawnGun))
		SpawnGun();
}

void Outside::Init()
{
	SetVisible(true);
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

	m_eOutsideState = STATE_LeavingHouse;
}

void Outside::Hide()
{
	SetVisible(false);
}

void Outside::SpawnCum()
{
	Cum *pNewCum = HY_NEW Cum(this);
	pNewCum->pos.Set(HyRand::Range(50.0f, 200.0f), ACTOR_ITEM_POSY);
	pNewCum->Load();
	m_CumList.push_back(pNewCum);
}

void Outside::SpawnGun()
{
	Gun *pNewGun = HY_NEW Gun(this);
	pNewGun->pos.Set(HyRand::Range(50.0f, 200.0f), ACTOR_ITEM_POSY);
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