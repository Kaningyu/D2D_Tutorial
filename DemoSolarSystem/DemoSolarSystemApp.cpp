#include "pch.h"
#include "DemoSolarSystemApp.h"
#include "../D2DEngine/BitmapScene.h"


DemoSolarSystemApp::DemoSolarSystemApp()
{

}

DemoSolarSystemApp::~DemoSolarSystemApp()
{

}

void DemoSolarSystemApp::Initialize()
{
	__super::Initialize();	 // ������ ���� , Direct2D �ʱ�ȭ
	// �¾�, ����,��	�̹��� �ε�

	// �¾�,����,�� �θ� �ڽ� ���� ���� 
}

void DemoSolarSystemApp::Update(float fTimeElapsed)
{
	__super::Update(fTimeElapsed);

	// BitmapScene World Transform ������Ʈ
}

void DemoSolarSystemApp::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	// ���Ŀ� ������ �ۼ��Ѵ�. �� ���� ������
	m_Sun.Render(pRenderTarget);
	
}
