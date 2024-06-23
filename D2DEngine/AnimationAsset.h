#pragma once
#include "ReferenceCounter.h"

// �ִϸ��̼� �⺻ �������� �⺻ ����
struct FRAME_INFO
{
	D2D1_RECT_F		Source;			// �̹������� �ϳ��� ����� ��� ������ �ִ���
	D2D1_VECTOR_2F	Center;			// �ϳ��� FRAME���� ������� 0,0 ����  ������ ��ǥ
	FLOAT			Duration;		// �ϳ��� ����� �׸� �ð�

	FRAME_INFO()
	{
		Source.left = 0;
		Source.top = 0;
		Source.right = 0;
		Source.bottom = 0;
		Duration = 0;
		Center.x = 0;
		Center.y = 0;
	}

	FRAME_INFO(float left, float top, float right, float bottom, float centerX, float centerY, float time)
	{
		Source.left = left;
		Source.top = top;
		Source.right = right;
		Source.bottom = bottom;
		Center.x = centerX;
		Center.y = centerY;
		Duration = time;
	}
	FRAME_INFO(D2D1_RECT_F rect, float centerX, float centerY, float time)
	{
		Source = rect;
		Center.x = centerX;
		Center.y = centerY;
		Duration = time;
	}
};

/*
	�ϳ��� ���ۿ� ���� ����
*/
struct ANIMATION_INFO
{
	std::string m_Name; // �ִϸ��̼��� �̸�	�̸����� �˻��Ͽ� ����Ѵ�.
	std::vector<FRAME_INFO> m_Frames; // �������� ����
	ANIMATION_INFO()
		:m_Name("Default")
	{

	}
};

// �̸��� �����ϴ� �ִϸ��̼� ������ ������ �ִ� Ŭ����
class AnimationAsset : public ReferenceCounter
{	
protected:
	AnimationAsset() {};
	virtual ~AnimationAsset();
public:
	std::vector<ANIMATION_INFO> m_Animations;  // �ִϸ��̼��� ����

	ANIMATION_INFO* GetAnimationInfo(int index) 
	{ 
	    assert(index >= 0 && index < m_Animations.size());
		return &m_Animations[index]; 
	}
	ANIMATION_INFO* GetAnimationInfo(std::string AnimationName)
	{
		for (auto& iter : m_Animations)
		{
			if (iter.m_Name == AnimationName)
			{
				return &iter;
			}
		}
		return nullptr;
	}
};