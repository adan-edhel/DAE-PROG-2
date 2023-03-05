#include "pch.h"
#include <ctime>
#include "Game.h"


void StartHeapControl();
void DumpMemoryLeaks();

int SDL_main(int argv, char** args)
{
	srand(static_cast<unsigned int>(time(nullptr)));

	StartHeapControl();

	Game* pGame{ new Game{ Window{ "Project name - Name, first name - 1DAEXX", 846.f , 500.f } } };
	pGame->Run();
	delete pGame;

	DumpMemoryLeaks();
	return 0;
}


void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 156 );
#endif
}

int CustomizeReportHook(int reportType, char* message, int* returnValue)
{
	if (reportType == _CRT_WARN) {

		// Best method, as it will log actual red errors, but it has .NET dependency,
		// which I'm not sure is worth it to add for this functionality.
		//System.Diagnostics.Debug.WriteLine(">>Warning: Memory Leak!<< \n");

		// Alternative without .NET dependency
		OutputDebugStringA(">>Warning: Memory Leak!<< \n");
		*returnValue = 0;
		return 1;
	}

	// Return 0 to use the default report handler for other types of reports
	return 0;
}

void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetReportHook(CustomizeReportHook);
	_CrtDumpMemoryLeaks();
#endif
}