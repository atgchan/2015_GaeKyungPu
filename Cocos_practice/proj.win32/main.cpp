#include "pch.h"
#include "main.h"
#include "AppDelegate.h"
///# VLD 같은 외부 라이브러리 쓰면 반드시 프로젝트에 포함하거나, 설치할 수 있도록 명시해야 함!!


USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
	//_CrtSetBreakAlloc();
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}