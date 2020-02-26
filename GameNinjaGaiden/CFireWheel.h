#pragma once
#include "CGameObject.h"

class CFireWheel : public CGameObject
{
public:
	CFireWheel(int id);
	CFireWheel(int id, int x, int y);
	~CFireWheel();

private:

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
};

