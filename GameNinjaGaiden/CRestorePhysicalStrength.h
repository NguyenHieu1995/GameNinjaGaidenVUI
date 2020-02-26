#pragma once
#include "CGameObject.h"

class CRestorePhysicalStrength : public CGameObject
{
public:
	CRestorePhysicalStrength(int id);
	CRestorePhysicalStrength(int id, int x, int y);
	~CRestorePhysicalStrength();

private:

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
};
