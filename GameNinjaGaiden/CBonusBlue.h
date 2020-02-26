#pragma once

#include <Windows.h>
#include "CGameObject.h"
#include "CDebug.h"

class CBonusBlue : public CGameObject
{
public:
	CBonusBlue(int id);
	CBonusBlue(int id, int x, int y);
	~CBonusBlue();

private:


public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
};

