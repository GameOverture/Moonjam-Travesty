#ifndef pch_h__
#define pch_h__

#include "Harmony/HyEngine.h"

#define DISPLAYORDER_LoadCover		999999999
#define DISPLAYORDER_Bills			999999990
#define DISPLAYORDER_Clock			99999999
#define DISPLAYORDER_Computer		9999999
#define DISPLAYORDER_DarkOverlay	999999
#define DISPLAYORDER_ItemSetup		999995
#define DISPLAYORDER_Enemies		99999

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
	TAG_Gun,

	// Enemy
	TAG_Gums,
	TAG_Borpa
};

enum InputAction
{
	//INPUT_DebugCamUp = 0,
	//INPUT_DebugCamDown,
	//INPUT_DebugCamLeft,
	//INPUT_DebugCamRight,
	//INPUT_DebugSpawnCum,
	//INPUT_DebugSpawnGun,

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

enum BillyFeels
{
	BILLY_Okage = 0,
	BILLY_Hunger,
	BILLY_Sick,
	BILLY_Juicer
};

enum BillyGrade
{
	BILLYGRADE_A = 4,
	BILLYGRADE_B = 3,
	BILLYGRADE_C = 2,
	BILLYGRADE_D = 1,
	BILLYGRADE_F = 0,
};

enum GameOverType
{
	GAMEOVER_Bankruptcy = 0,
	GAMEOVER_Juicer,
	GAMEOVER_Win
};

#endif // pch_h__
