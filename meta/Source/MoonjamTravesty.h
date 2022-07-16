#ifndef MoonjamTravesty_h__
#define MoonjamTravesty_h__

#include "pch.h"

class MoonjamTravesty : public HyEngine
{
	HyCamera2d *	m_pCamera;

	enum InputAction
	{
		INPUT_ExitGame = 0,
	};

public:
	MoonjamTravesty(HarmonyInit &initStruct);
	virtual ~MoonjamTravesty();

	virtual bool OnUpdate() override;
};

#endif // MoonjamTravesty_h__
