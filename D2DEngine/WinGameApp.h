#pragma once
#include "D2DRenderer.h"

class WinGameApp
{
public:
	// �ڽ� Ŭ������ ������ �����ϵ��� virtual keyword �� ���δ�.
	virtual void Initialize();
	virtual void Run();
	virtual void Uninitialize();

	virtual void Update(float fTimeElapsed)=0;
	virtual void Render()=0;

	D2DRenderer m_Renderer;
};

