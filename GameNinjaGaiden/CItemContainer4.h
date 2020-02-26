#pragma once

#include <Windows.h>
#include "CGameObject.h"

class CItemContainer4 : public CGameObject
{
public:
	CItemContainer4(int id);
	CItemContainer4(int id, int x, int y);
	~CItemContainer4();

private:

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
};
