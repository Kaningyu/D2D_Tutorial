﻿#include <windows.h>
#include <d2d1.h>
#include <comdef.h>
#include <d2d1_1helper.h>
#include <string>
#include <dwrite.h>

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")
#pragma comment(lib,"dxgi.lib")

// 전역 변수:
HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;

//  D2D 개체 인터페이스 포인터 변수
ID2D1Factory* g_pD2DFactory;

//무언가 그릴수있는 렌더타겟, 장치 의존 리소스
ID2D1HwndRenderTarget* g_pRenderTarget;

// 렌더타겟이 생성하는 리소스 역시 장치의존
ID2D1SolidColorBrush* g_pBlackBrush;

// DWrite
IDWriteFactory* g_pDWriteFactory;
IDWriteTextFormat* g_pDWriteTextFormat;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

BOOL InitDirect2D()
{
    HRESULT hr = S_OK;
    // COM 사용 시작
    hr = CoInitialize(NULL);
    if (FAILED(hr))
        return FALSE;

    /*	장치에 바인딩되지 않은 리소스를 만듭니다.수명은 앱이 지속되는 동안 효과적으로 연장됩니다.
        이러한 리소스에는 Direct2D 및 DirectWrite 팩터리와
        DirectWrite 텍스트 형식 개체(특정 글꼴 특성을 식별하는 데 사용됨)가 포함됩니다.
    */
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
    if (FAILED(hr))
        return FALSE;


    /*
        Direct3D 장치에 바인딩된 리소스를 만듭니다.
    */
    RECT rc;
    GetClientRect(g_hWnd, &rc);

    D2D1_SIZE_U size = D2D1::SizeU(
        rc.right - rc.left,
        rc.bottom - rc.top);

    // Create a Direct2D render target.
    hr = g_pD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(g_hWnd, size),
        &g_pRenderTarget);
	if (FAILED(hr))
		return FALSE;

    hr = g_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &g_pBlackBrush);
	if (FAILED(hr))
		return FALSE;
        

    // DirectWrite 팩터리를 만듭니다.
	hr = DWriteCreateFactory(
	    DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(g_pDWriteFactory),
		reinterpret_cast<IUnknown**>(&g_pDWriteFactory));

    if (FAILED(hr))
	    return FALSE;

    // DirectWrite 텍스트 형식 개체를 만듭니다.
	hr = g_pDWriteFactory->CreateTextFormat(
			L"Cooper", // FontName    제어판-모든제어판-항목-글꼴-클릭 으로 글꼴이름 확인가능
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			50.0f,   // Font Size
			L"", //locale
			&g_pDWriteTextFormat
		);
	if (FAILED(hr))
		return FALSE;

    // 텍스트를 수평 및 수직으로 중앙에 맞춥니다.
    g_pDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    g_pDWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    return TRUE;
}

void UninitDirect2D()
{
    if (g_pDWriteTextFormat) g_pDWriteTextFormat->Release();
    if (g_pDWriteFactory) g_pDWriteFactory->Release();
    if (g_pBlackBrush) g_pBlackBrush->Release();
    if (g_pRenderTarget) g_pRenderTarget->Release();
    if (g_pD2DFactory) g_pD2DFactory->Release();

    // COM 사용 끝
    CoUninitialize();
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 윈도우 클래스 구조체 초기화
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;	// 윈도우 프로시저 함수
	wc.hInstance = hInstance;   // 인스턴스 핸들
	// NULL을 사용하면 현재 실행 중인 프로그램의 인스턴스 핸들을 사용하게 됩니다.두 번째 인자는 로드할 커서의 ID입니다.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = L"BasicWindowClass";

	// 윈도우 클래스 등록
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"윈도우 클래스 등록 실패", L"에러", MB_OK | MB_ICONERROR);
		return 1;
	}

	// 원하는 크기가 조정되어 리턴
	SIZE clientSize = { 1920, 1280 };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	// 윈도우 생성
	g_hWnd = CreateWindowEx(
		0,
		L"BasicWindowClass",
		L"간단한 윈도우",
		WS_OVERLAPPEDWINDOW,	// OR연산으로 조합된 윈도우창 스타일
		0, 0,	// 시작위치
		clientRect.right - clientRect.left, clientRect.bottom - clientRect.top, // 너비, 높이
		NULL, NULL, hInstance, NULL
	);

	if (!g_hWnd)
	{
		MessageBox(NULL, L"윈도우 생성 실패", L"에러", MB_OK | MB_ICONERROR);
		return 1;
	}

	// 윈도우 표시
	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);

	if (!InitDirect2D())
		return FALSE;

	MSG msg;
	// 기본 메시지 루프입니다:
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			//윈도우 메시지 처리 
			TranslateMessage(&msg); // 키입력관련 메시지 변환  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&msg);
		}
		else
		{
			g_pRenderTarget->BeginDraw();
			g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));

			D2D1_SIZE_F size = g_pRenderTarget->GetSize();
			
			WCHAR sc_helloWorld[] = L"Hello, World! Abg";
			g_pRenderTarget->DrawText(
				sc_helloWorld,
				ARRAYSIZE(sc_helloWorld) - 1,
				g_pDWriteTextFormat,
				D2D1::RectF(0, 0, size.width, size.height/2),
				g_pBlackBrush
			);

			g_pRenderTarget->EndDraw();

		}
	}

	UninitDirect2D();
    return (int) msg.wParam;
}

// 윈도우 프로시저 함수 정의
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}