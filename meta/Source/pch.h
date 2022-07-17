#ifndef pch_h__
#define pch_h__

#include "Harmony/HyEngine.h"

#define DISPLAYORDER_Clock			9999999
#define DISPLAYORDER_Computer		999999
#define DISPLAYORDER_ItemSetup		999999
#define DISPLAYORDER_DarkOverlay	99999

enum Tag
{
	// Main Classes
	TAG_Player = 1,
	TAG_Outside,
	TAG_Inside,

	// Inside Collision
	TAG_Computer,
	TAG_Kitchen,
	TAG_Homework,
	TAG_Exit,
	
	// Outside Collision
	TAG_Ground,
	TAG_Cum,
	TAG_Gun
};

enum InputAction
{
	INPUT_DebugCamUp = 0,
	INPUT_DebugCamDown,
	INPUT_DebugCamLeft,
	INPUT_DebugCamRight,
	INPUT_DebugSpawnCum,
	INPUT_DebugSpawnGun,

	INPUT_MoveLeft,
	INPUT_MoveRight,
	INPUT_MoveUp,
	INPUT_MoveDown,
	
	INPUT_Jump,
	INPUT_Action,

	INPUT_Menu,
};

enum MoonState
{
	MOONSTATE_SideIdle = 0,
	MOONSTATE_SideWalk,
	MOONSTATE_Action,
	MOONSTATE_UpIdle,
	MOONSTATE_UpWalk,
	MOONSTATE_Pickup
};

enum ItemState
{
	ITEMSTATE_Packaged = 0,
	ITEMSTATE_Held,
	ITEMSTATE_SetupInit,
	ITEMSTATE_SetupLoop,
	ITEMSTATE_Active
};

#endif // pch_h__
