#include "pch.h"
#include <ctime>
#include "Game.h"

void StartHeapControl();
int CustomizeReportHook(int reportType, char* message, int* returnValue);

int SDL_main(int argv, char** args)
{
	srand(static_cast<unsigned int>(time(nullptr)));

	StartHeapControl();

	Game* pGame{ new Game{ Window{ "Hollow Knight - Onmaz, 'Mort' Yasin - 1DAE12", 1280.f , 800.f } } };
	pGame->Run();
	delete pGame;

	return 0;
}

void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Customize output of the dump
	_CrtSetReportHook(CustomizeReportHook);

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 156 );
#endif
}

int CustomizeReportHook(int reportType, char* message, int* returnValue)
{
	if (reportType == _CRT_WARN) {
		OutputDebugStringA(">>Warning: Memory Leak!<< \n");
		*returnValue = 0;
		return 1;
	}

	// Return 0 to use the default report handler for other types of reports
	return 0;
}