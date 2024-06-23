#pragma once
#include "Scene.h"


class D2DRenderer;
class BitmapScene :
	public Scene
{
public:
	BitmapScene();
	virtual ~BitmapScene();

	bool LoadD2DBitmap(const std::wstring& strFileName);

	std::wstring m_strFileName;
	ID2D1Bitmap* m_pBitmap = nullptr;	
	

	void Update(float fTimeElapsed);
	void Render(ID2D1HwndRenderTarget* pRenderTarget);
};




