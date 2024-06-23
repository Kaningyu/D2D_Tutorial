#include "pch.h"
#include "WinGameApp.h"
#include "D2DRenderer.h"
#include "ResourceManager.h"

WinGameApp::WinGameApp()
{
	m_pRenderer = new D2DRenderer;
	m_pResourceManager = new ResourceManager;
}

WinGameApp::~WinGameApp()
{
	if (m_pResourceManager)
	{
		delete m_pResourceManager;
		m_pResourceManager = nullptr;
	}

	if (m_pRenderer)
	{
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

void WinGameApp::Initialize()
{
	// �������� ����ϴ� ������ ����,�����κ��� �ۼ��Ѵ�.

	// Direct2D�ʱ�ȭ�� �ۼ��Ѵ�.
	m_pRenderer->Initialize();
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
			float deltaTime = 0.016f;
			Update(deltaTime);					
			Render(m_pRenderer->GetRenderTarget());
		}
	}
}

void WinGameApp::Uninitialize()
{
	// Direct2D ������ ȣ���Ѵ�.
	m_pRenderer->Uninitialize();
}


void WinGameApp::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
	pRenderTarget->EndDraw();
}

