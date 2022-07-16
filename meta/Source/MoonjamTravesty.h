#ifndef MoonjamTravesty_h__
#define MoonjamTravesty_h__

#include "pch.h"
#include "Outside.h"

class MoonjamTravesty : public HyEngine
{
	HyCamera2d *		m_pCamera;

	enum InputAction
	{
		INPUT_DebugCamUp = 0,
		INPUT_DebugCamDown,
		INPUT_DebugCamLeft,
		INPUT_DebugCamRight,

		INPUT_Menu,
	};

	Outside				m_Outside;

	enum GameState
	{
		STATE_Loading = 0,
		STATE_Outside
	};
	GameState			m_eState;

public:
	MoonjamTravesty(HarmonyInit &initStruct);
	virtual ~MoonjamTravesty();

	virtual bool OnUpdate() override;
};

#endif // MoonjamTravesty_h__
