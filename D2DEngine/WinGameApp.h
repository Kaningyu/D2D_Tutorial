#pragma once
#include "D2DRenderer.h"

class WinGameApp
{
public:
	// �ڽ� Ŭ������ ������ �����ϵ��� virtual keyword �� ���δ�.
	virtual void Initialize();
	virtual void Run();
	virtual void Uninitialize();

	virtual void Update(float fTimeElapsed) {};
	virtual void Render() {};

	D2DRenderer m_Renderer;
};

