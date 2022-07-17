#ifndef Inside_h__
#define Inside_h__

#include "pch.h"
#include "Player.h"
#include "InsideContactListener.h"

class Inside : public HyPhysicsGrid2d
{
	Player &					m_PlayerRef;
	InsideContactListener		m_InsideContactListener;

	HySprite2d					m_Map;
	
	HyPrimitive2d				m_Sensor_Computer;
	HyPrimitive2d				m_Sensor_Kitchen;
	HyPrimitive2d				m_Sensor_Homework;
	HyPrimitive2d				m_Sensor_Exit;

	HyPrimitive2d				m_Wall_Left;
	HyPrimitive2d				m_Wall_Right;
	HyPrimitive2d				m_Wall_UpperKitchen;
	HyPrimitive2d				m_Wall_UpperMain;
	HyPrimitive2d				m_Wall_UpperComputer;
	HyPrimitive2d				m_Wall_KitchenCounter;
	HyPrimitive2d				m_Wall_LowLeft;
	HyPrimitive2d				m_Wall_LowRight;

	enum InsideState
	{
		STATE_Inactive,
		STATE_EnteringHouse,
		STATE_Play,
		STATE_PlayComputer,
		STATE_PlayKitchen,
		STATE_PlayHomework,
	};
	InsideState					m_eInsideState;

public:
	Inside(Player &playerRef, HyEntity2d *pParent = nullptr);
	virtual ~Inside();

	virtual void OnUpdate() override;

	void Init();
	void Hide();

	void OnEnterComputer();
	void OnLeaveComputer();
	void OnEnterKitchen();
	void OnLeaveKitchen();
	void OnEnterHomework();
	void OnLeaveHomework();
	void OnExitHouse();
};

#endif // Inside_h__
