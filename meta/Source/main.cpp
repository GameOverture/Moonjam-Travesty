#include "pch.h"
#include "MoonjamTravesty.h"

//--------------------------------------------------------------------------------------
// Entry point to MoonjamTravesty
//
// Initialize a HarmonyInit structure either by passing the path to the *.hyproj file,
// or override its settings using command line arguments or simply hard-coding the values.
//
// Instantiate your game class that extends from HyEngine, and initialize it with the
// HarmonyInit structure. return RunGame() to end the program with the proper exit code, and 
// any memory leaks will be written to output if using a supported IDE.
//--------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	HarmonyInit initStruct("MoonjamTravesty.hyproj");

	// Emscripten requires all initial memory to be on the heap (above 'initStruct' is copied internally)
	// and the main() function to exit in order for its artificial 'update loop' to work correctly in the browser
	MoonjamTravesty *pGame = HY_NEW MoonjamTravesty(initStruct);
	int32 iReturnCode = pGame->RunGame();
#ifndef HY_PLATFORM_BROWSER
	delete pGame;
#endif

	return iReturnCode;
}
