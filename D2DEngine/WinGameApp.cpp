#include "pch.h"
#include "WinGameApp.h"

void WinGameApp::Initialize()
{
	// �������� ����ϴ� ������ ����,�����κ��� �ۼ��Ѵ�.

	// Direct2D�ʱ�ȭ�� �ۼ��Ѵ�.
}

void WinGameApp::Run()
{
	// �������� ����ϴ� ������ ���� ������ �ۼ��Ѵ�.
	MSG msg;
	// �⺻ �޽��� �����Դϴ�:
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			//������ �޽��� ó�� 
			TranslateMessage(&msg); // Ű�Է°��� �޽��� ��ȯ  WM_KEYDOWN -> WM_CHAR
			DispatchMessage(&msg);
		}
		else
		{
			ID2D1HwndRenderTarget* pRenderTarget = m_Renderer.GetRenderTarget();
			pRenderTarget->BeginDraw();
			pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
			Render(pRenderTarget);
			pRenderTarget->EndDraw();
		}
	}
}

void WinGameApp::Uninitialize()
{
	// Direct2D ������ ȣ���Ѵ�.
}


void WinGameApp::Render(ID2D1HwndRenderTarget* pRenderTarget)
{

}

