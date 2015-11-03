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

전반적으로 코딩 컨벤션을 맞추고 
   멤버 변수는 앞에 m을 붙인다던지,, { } 위치를 맞춘다든지, 한줄 코드 앞뒤로 줄내림을 하고 {} 할것인지, 대소문자를 어떤식으로 쓸 것인지 등등

멤버 변수는 후에 어떤 함수에서 초기화하더라도, 생성시에는 반드시 디폴트 값을 가질 수 있도록 초기화 하는 습관을 만들 것.

나머지 부분은 
    "///#"로 검색 ㄱㄱ

*/