#include "pch.h"
#include "main.h"
#include "AppDelegate.h"




USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc();
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}

/*
GameSceneManager에 게임 로직이 같이 섞여 들어 있는데, 로직과 씬을 구성해주는 부분은 점차적으로 리팩토링 해서 분리해주는게 좋다.. MVC 패턴 공부해볼 것.
*/