#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>

#include <SFML\System\Clock.hpp>

#include "guicon.h"
#include "AppManager.hpp"

int __stdcall WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
{
	AppManager& appMgr = AppManager::GetSingleton();

	if(!appMgr.Initialise())
		return 1;

	//RedirectIOToConsole();
	
	sf::Clock clock;
	while(!appMgr.CheckQuitting())
	{
		appMgr.PollEvents();
		appMgr.Update(clock.restart().asSeconds());
		//
		if(!appMgr.Render())
			break;
	}

    return 0;
}
