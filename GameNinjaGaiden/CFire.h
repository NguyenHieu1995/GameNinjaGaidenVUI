#pragma once

#include <Windows.h>
#include "CGameObject.h"

class CFire : public CGameObject
{
public:
	CFire(int id);
	CFire(int id, int x, int y);
	~CFire();

private:


public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();

	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void SetState(int state);
};

