#pragma once

#include "CGameObject.h"

class CTimeFreeze : public CGameObject
{
public:
	CTimeFreeze(int id);
	CTimeFreeze(int id, int x, int y);
	~CTimeFreeze();

private:

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
};

