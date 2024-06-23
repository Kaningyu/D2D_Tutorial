#include "pch.h"
#include "BitmapScene.h"



BitmapScene::BitmapScene()
{

}

BitmapScene::~BitmapScene()
{
	if (m_pBitmap)
	{
		m_pBitmap->Release();
		m_pBitmap = nullptr;
	}
}
void BitmapScene::LoadD2DBitmap(const std::wstring& strFileName)
{
	// ���ҽ� �Ŵ����� ���� ��Ʈ���� �ε��Ѵ�.
}

void BitmapScene::Update(float fTimeElapsed)
{
	UpdateTrasnform();
}

void BitmapScene::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	assert(m_pBitmap != nullptr);
	pRenderTarget->SetTransform(m_WorldTransform);
	pRenderTarget->DrawBitmap(m_pBitmap);
}

