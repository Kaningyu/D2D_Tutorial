#include "DemoSolarSystemApp.h"
#include "../D2DEngine/D2DRenderer.h"

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

void DemoSolarSystemApp::Render()
{
	// ���Ŀ� ������ �ۼ��Ѵ�. �� ���� ������
}
