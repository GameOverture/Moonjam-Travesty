#include "pch.h"
#include "Inside.h"
#include "MoonjamTravesty.h"

Inside::Inside(Player &playerRef, HyEntity2d *pParent /*= nullptr*/) :
	HyPhysicsGrid2d(glm::vec2(0.0f, 0.0f), 120.0f),
	m_PlayerRef(playerRef),
	m_Map("Inside", "Inside", this),
	m_Sensor_Computer(this),
	m_Sensor_Kitchen(this),
	m_Sensor_Homework(this),
	m_Sensor_Exit(this),
	m_Wall_Left(this),
	m_Wall_Right(this),
	m_Wall_UpperKitchen(this),
	m_Wall_UpperMain(this),
	m_Wall_UpperComputer(this),
	m_Wall_KitchenCounter(this),
	m_Wall_LowLeft(this),
	m_Wall_LowRight(this),
	m_eInsideState(STATE_Inactive)
{
	SetTag(TAG_Inside);
	m_b2World.SetContactListener(&m_InsideContactListener);

	float fDebugShowAmt = 0.0f;

	m_Sensor_Computer.SetTag(TAG_Computer);
	m_Sensor_Computer.SetTint(HyColor::Blue);
	m_Sensor_Computer.alpha.Set(fDebugShowAmt);
	m_Sensor_Computer.shape.SetAsBox(64.0f, 64.0f, glm::vec2(1078.0f, 543.0f), 0.0f);
	m_Sensor_Computer.physics.Init(HYPHYS_Static);
	m_Sensor_Computer.physics.SetSensor(true);

	m_Sensor_Kitchen.SetTag(TAG_Kitchen);
	m_Sensor_Kitchen.SetTint(HyColor::Blue);
	m_Sensor_Kitchen.alpha.Set(fDebugShowAmt);
	m_Sensor_Kitchen.shape.SetAsBox(160.0f, 64.0f, glm::vec2(182.0f, 543.0f), 0.0f);
	m_Sensor_Kitchen.physics.Init(HYPHYS_Static);
	m_Sensor_Kitchen.physics.SetSensor(true);

	m_Sensor_Homework.SetTag(TAG_Homework);
	m_Sensor_Homework.SetTint(HyColor::Blue);
	m_Sensor_Homework.alpha.Set(fDebugShowAmt);
	m_Sensor_Homework.shape.SetAsBox(125.0f, 64.0f, glm::vec2(304.0f, 194.0f), 0.0f);
	m_Sensor_Homework.physics.Init(HYPHYS_Static);
	m_Sensor_Homework.physics.SetSensor(true);

	m_Sensor_Exit.SetTag(TAG_Exit);
	m_Sensor_Exit.SetTint(HyColor::Blue);
	m_Sensor_Exit.alpha.Set(fDebugShowAmt);
	m_Sensor_Exit.shape.SetAsBox(125.0f, 64.0f, glm::vec2(535.0f, -60.0f), 0.0f);
	m_Sensor_Exit.physics.Init(HYPHYS_Static);
	m_Sensor_Exit.physics.SetSensor(true);

	m_Wall_Left.SetTint(HyColor::Red);
	m_Wall_Left.alpha.Set(fDebugShowAmt);
	m_Wall_Left.shape.SetAsBox(64.0f, 400.0f, glm::vec2(-25.0f, 400.0f), 0.0f);
	m_Wall_Left.physics.Init(HYPHYS_Static);

	m_Wall_Right.SetTint(HyColor::Red);
	m_Wall_Right.alpha.Set(fDebugShowAmt);
	m_Wall_Right.shape.SetAsBox(64.0f, 400.0f, glm::vec2(1275.0f, 400.0f), 0.0f);
	m_Wall_Right.physics.Init(HYPHYS_Static);

	m_Wall_UpperKitchen.SetTint(HyColor::Red);
	m_Wall_UpperKitchen.alpha.Set(fDebugShowAmt);
	m_Wall_UpperKitchen.shape.SetAsBox(200.0f, 64.0f, glm::vec2(200.0f, 620.0f), 0.0f);
	m_Wall_UpperKitchen.physics.Init(HYPHYS_Static);

	m_Wall_UpperMain.SetTint(HyColor::Red);
	m_Wall_UpperMain.alpha.Set(fDebugShowAmt);
	m_Wall_UpperMain.shape.SetAsBox(285.0f, 163.0f, glm::vec2(637.0f, 572.0f), 0.0f);
	m_Wall_UpperMain.physics.Init(HYPHYS_Static);

	m_Wall_UpperComputer.SetTint(HyColor::Red);
	m_Wall_UpperComputer.alpha.Set(fDebugShowAmt);
	m_Wall_UpperComputer.shape.SetAsBox(179.0f, 100.0f, glm::vec2(1084.0f, 647.0f), 0.0f);
	m_Wall_UpperComputer.physics.Init(HYPHYS_Static);

	m_Wall_KitchenCounter.SetTint(HyColor::Red);
	m_Wall_KitchenCounter.alpha.Set(fDebugShowAmt);
	m_Wall_KitchenCounter.shape.SetAsBox(95.0f, 40.0f, glm::vec2(320.0f, 413.0f), 0.0f);
	m_Wall_KitchenCounter.physics.Init(HYPHYS_Static);

	m_Wall_LowLeft.SetTint(HyColor::Red);
	m_Wall_LowLeft.alpha.Set(fDebugShowAmt);
	m_Wall_LowLeft.shape.SetAsBox(236.0f, 30.0f, glm::vec2(233.0f, 30.0f), 0.0f);
	m_Wall_LowLeft.physics.Init(HYPHYS_Static);
	
	m_Wall_LowRight.SetTint(HyColor::Red);
	m_Wall_LowRight.alpha.Set(fDebugShowAmt);
	m_Wall_LowRight.shape.SetAsBox(342.0f, 30.0f, glm::vec2(954.0f, 30.0f), 0.0f);
	m_Wall_LowRight.physics.Init(HYPHYS_Static);
}

/*virtual*/ Inside::~Inside()
{
}

/*virtual*/ void Inside::OnUpdate() /*override*/
{
	m_InsideContactListener.ProcessQueue(*this);

	switch(m_eInsideState)
	{
	case STATE_Inactive:
		break;

	case STATE_EnteringHouse:
		if(m_PlayerRef.pos.IsAnimating() == false)
		{
			m_PlayerRef.EnableInput(true);
			m_eInsideState = STATE_Play;
		}
		break;

	case STATE_PlayComputer:
	case STATE_Play:
	case STATE_PlayKitchen:
	case STATE_PlayHomework:
		// Camera logic
		HyCamera2d *pCamera = HyEngine::Window().GetCamera2d(0);
		const float fDeadZoneAmt = HyEngine::Window().GetWidthF(0.2f);

		//auto worldBoundsAabb = pCamera->GetWorldViewBounds();
		//float fWorldBoundsLeft = worldBoundsAabb.lowerBound.x + fDeadZoneAmt;
		//float fWorldBoundsRight = worldBoundsAabb.upperBound.x - fDeadZoneAmt;

		//if(m_PlayerRef.pos.X() < fWorldBoundsLeft)
		//	pCamera->pos.Offset(m_PlayerRef.pos.X() - fWorldBoundsLeft, 0.0f);
		//if(m_PlayerRef.pos.X() > fWorldBoundsRight)
		//	pCamera->pos.Offset(m_PlayerRef.pos.X() - fWorldBoundsRight, 0.0f);
		break;
	}
}

void Inside::Init()
{
	SetVisible(true);
	HyEngine::Window().GetCamera2d(0)->pos.Set(635, 354);

	HyEngine::Window().GetCamera2d(0)->SetZoom(1.2f);

	m_PlayerRef.physics.SetEnabled(false);
	ChildAppend(m_PlayerRef);
	m_PlayerRef.EnableInput(false);
	m_PlayerRef.SetMoonState(MOONSTATE_SideWalk);
	m_PlayerRef.scale.Set(1.5f, 1.5f);
	m_PlayerRef.rot.Set(0.0f);
	
	m_PlayerRef.pos.Set(585.0f, -100.0f);

	const float fWalkInDur = 1.0f;
	m_PlayerRef.pos.Tween(585.0f, 128.0f, fWalkInDur);

	m_eInsideState = STATE_EnteringHouse;
}

void Inside::Hide()
{
	SetVisible(false);
}

void Inside::OnEnterComputer()
{
	MoonjamTravesty::GetGame().ShowComputer();
}

void Inside::OnLeaveComputer()
{
	MoonjamTravesty::GetGame().HideComputer();
}

void Inside::OnEnterKitchen()
{
	m_eInsideState = STATE_PlayKitchen;
}

void Inside::OnLeaveKitchen()
{
	m_eInsideState = STATE_Play;
}

void Inside::OnEnterHomework()
{
	m_eInsideState = STATE_PlayHomework;
}

void Inside::OnLeaveHomework()
{
	m_eInsideState = STATE_Play;
}

void Inside::OnExitHouse()
{
	MoonjamTravesty::LeaveHouse();
	m_eInsideState = STATE_Inactive;
}
