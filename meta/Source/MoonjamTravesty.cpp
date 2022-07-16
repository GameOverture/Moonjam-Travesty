#include "pch.h"
#include "MoonjamTravesty.h"

MoonjamTravesty::MoonjamTravesty(HarmonyInit &initStruct) :
	HyEngine(initStruct),
	m_pCamera(HyEngine::Window().CreateCamera2d())
{
	HyEngine::Input().MapBtn(INPUT_ExitGame, HYKEY_Escape);
}

MoonjamTravesty::~MoonjamTravesty()
{
}

/*virtual*/ bool MoonjamTravesty::OnUpdate() /*override*/
{
	return !HyEngine::Input().IsActionReleased(INPUT_ExitGame);
}
