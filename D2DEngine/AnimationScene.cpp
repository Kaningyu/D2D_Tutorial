#include "pch.h"
#include "AnimationScene.h"
#include "AnimationAsset.h"
#include "D2DRenderer.h"


AnimationScene::AnimationScene()
{

}

AnimationScene::~AnimationScene()
{

}

void AnimationScene::LoadAnimationAsset(const std::wstring strAssetName)
{

}

void AnimationScene::Update(float fTimeElapsed)
{
	__super::Update(fTimeElapsed);	
	assert(m_pAnimationAsset != nullptr);  // asset�� ������ debug��忡�� ����
	if (m_pAnimationInfo == nullptr)
		return;

	const FRAME_INFO& Frame = m_pAnimationInfo->m_Frames[m_FrameIndexCurr];
	size_t MaxFrameCount = m_pAnimationInfo->m_Frames.size();

	///////////////     
    // m_FrameTime�� fTimeElapsed�� ��������  Frame.Duration���� ũ�� 
	// m_FrameIndexCurr�� ������Ű�� m_FrameTime�� 0���� �ʱ�ȭ�Ѵ�.
	// �ϴ� ������ �����ϰ� ó���Ѵ�.
	////////////////	


	m_SrcRect = Frame.Source;		
	m_DstRect = { 0,0,m_SrcRect.right - m_SrcRect.left,m_SrcRect.bottom - m_SrcRect.top };
	
	if (m_bMirror) //x �� �������� �¿� ���� , Translation �� ����� �̹����� ���� ����
	{	
		m_RenderTransform = D2D1::Matrix3x2F::Scale(-1.0f,1.0f, D2D1::Point2F(0, 0)) *
			D2D1::Matrix3x2F::Translation(Frame.Center.x, Frame.Center.y);
	}
	else
	{
		m_RenderTransform = D2D1::Matrix3x2F::Scale(1.0f,1.0f, D2D1::Point2F(0, 0)) * 
			D2D1::Matrix3x2F::Translation(Frame.Center.x * -1, Frame.Center.y);
	}
}

void AnimationScene::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	if (m_pAnimationInfo == nullptr)
		return;

	D2D1_MATRIX_3X2_F Transform = m_RenderTransform * m_WorldTransform * D2DRenderer::m_CameraTransform;
	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawBitmap(m_pBitmap, m_DstRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_SrcRect);	
}

void AnimationScene::SetAnimation(int index,bool mirror)
{
	assert(m_pAnimationAsset != nullptr);

	ANIMATION_INFO* pFound = m_pAnimationAsset->GetAnimationInfo(index);
	if (pFound == nullptr)
		return;

	m_pAnimationInfo = pFound;
	m_bMirror = mirror;
	m_FrameIndexCurr = 0;
	m_FrameIndexPrev = 0;
	m_FrameTime = 0.0f;
}
