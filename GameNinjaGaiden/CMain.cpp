#include <Windows.h>
#include <stdlib.h>
#include "CWindow.h"
#include "CGame.h"
#include "CConstant.h"
#include "CGameNinjaGaiden.h"

// Main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Check for memory leak if debug build
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	MSG msg;

	try
	{
		// Create the window
		if (CWindow::GetInstance()->CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT) == false)
			return 1;

		// Game run
		//if (CGame::GetInstance()->Init() == false)
			//return 0;

		bool done = false;

		CGameNinjaGaiden* gameNinjaGaiden = new CGameNinjaGaiden();
		if (gameNinjaGaiden->Init() == false)
		{
			done = true;
		}		

		while (!done && (gameNinjaGaiden->IsAlive()))
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
					done = true;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}			
			else
			{
				//CGame::GetInstance()->Run();
				gameNinjaGaiden->Run();
			}
		}

		gameNinjaGaiden->Destroy();
		delete gameNinjaGaiden;

		// detroy all poiter 
		//delete CGame::GetInstance();
		delete CWindow::GetInstance();

		return (int)msg.wParam;
	}
	catch (...)
	{
		MessageBox(NULL, L"Unknown error occured in game.", L"Error", MB_OK);
	}

	//delete CGame::GetInstance();
	delete CWindow::GetInstance();
	return 0;
}

