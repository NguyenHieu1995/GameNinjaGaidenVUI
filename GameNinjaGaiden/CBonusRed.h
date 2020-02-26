#pragma once

#include <Windows.h>
#include "CGameObject.h"

class CBonusRed : public CGameObject
{
public:
	CBonusRed(int id);
	CBonusRed(int id, int x, int y);
	~CBonusRed();

private:


public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT> *coObject);
	void Render();		
	virtual RectEx GetBoundingBox();	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
};

