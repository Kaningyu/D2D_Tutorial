#pragma once
#include "ReferenceCounter.h"

// 애니메이션 기본 프레임의 기본 정보
struct FRAME_INFO
{
	D2D1_RECT_F		Source;			// 이미지에서 하나의 장면이 어느 영역에 있는지
	D2D1_VECTOR_2F	Center;			// 하나의 FRAME에서 좌측상단 0,0 기준  중점의 좌표
	FLOAT			Duration;		// 하나의 장면을 그릴 시간

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
	하나의 동작에 대한 정보
*/
struct ANIMATION_INFO
{
	std::string m_Name; // 애니메이션의 이름	이름으로 검색하여 재생한다.
	std::vector<FRAME_INFO> m_Frames; // 프레임의 모음
	ANIMATION_INFO()
		:m_Name("Default")
	{

	}
};

// 이름을 뭐로하던 애니메이션 정보를 가지고 있는 클래스
class AnimationAsset : public ReferenceCounter
{	
protected:
	AnimationAsset() {};
	virtual ~AnimationAsset();
public:
	std::vector<ANIMATION_INFO> m_Animations;  // 애니메이션의 모음

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