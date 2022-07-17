#ifndef MoonjamTravesty_h__
#define MoonjamTravesty_h__

#include "pch.h"
#include "Player.h"
#include "Outside.h"
#include "Inside.h"
#include "Clock.h"

class MoonjamTravesty : public HyEngine
{
	static MoonjamTravesty *	sm_pInstance;
	HyCamera2d *				m_pCamera;

	Player						m_Player;

	Outside						m_Outside;
	Inside						m_Inside;

	Clock						m_Clock;

public:
	MoonjamTravesty(HarmonyInit &initStruct);
	virtual ~MoonjamTravesty();

	virtual bool OnUpdate() override;

	static void LeaveHouse();
	static void EnterHouse();
};

#endif // MoonjamTravesty_h__
