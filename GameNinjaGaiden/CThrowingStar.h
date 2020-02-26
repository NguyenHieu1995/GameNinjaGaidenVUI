#pragma once

#include "CGameObject.h"

class CThrowingStart : public CGameObject
{
public:
	CThrowingStart(int id);
	CThrowingStart(int id, int x, int y);
	~CThrowingStart();

private:

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
};

