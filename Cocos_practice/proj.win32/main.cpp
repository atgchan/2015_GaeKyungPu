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


GameSceneManager에 게임 로직이 같이 섞여 들어 있는데, 로직과 씬을 구성해주는 부분은 점차적으로 리팩토링 해서 분리해주는게 좋다.. MVC 패턴 공부해볼 것.

---------------------------------------------------------
지난주에 언급했던 코멘트를 수정이 제대로 안된 부분이 많네??
수정 한 다음에는 ///# 코멘트 부분 모두 지워주삼

*/