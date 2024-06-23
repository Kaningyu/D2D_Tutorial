#pragma once
#include "BitmapScene.h"

class AnimationAsset;
struct ANIMATION_INFO;


// �ִϸ��̼� �ν��Ͻ� ����
class AnimationScene :
    public BitmapScene
{
public:
	AnimationScene();
	virtual ~AnimationScene();
	
	// �����ϴ� �ִϸ��̼� ����
	AnimationAsset* m_pAnimationAsset;  // �����ϴ� �ִϸ��̼� ����
	
	// �ν��Ͻ����� �ٸ� �ִϸ��̼� ����
	ANIMATION_INFO* m_pAnimationInfo;	// ���� �ִϸ��̼� ������ ����
	std::wstring m_strAnimationAsset;
	float m_FrameTime = 0.0f;	// ������ ����ð�
	int m_FrameIndexCurr;		// ���� ������ �ε���
	int m_FrameIndexPrev;		// ���� ������ �ε���
	int m_AnimationIndex = -1;	// ���� �ִϸ��̼� �ε���
	D2D1_RECT_F m_SrcRect;		// D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect;		// RenderTarget�� Destination ����		

	bool m_bMirror;				// �¿� ���� ����
	D2D1_MATRIX_3X2_F	m_ImageTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f 

	void LoadAnimationAsset(const std::wstring strAssetName);
	void Update(float fTimeElapsed);
	void Render(ID2D1HwndRenderTarget* pRenderTarget);	
	void SetAnimation(int index,bool mirror);
};

