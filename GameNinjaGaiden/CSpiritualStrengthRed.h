#pragma once

#include "CGameObject.h"

class CSpiritualStrengthRed : public CGameObject
{
public:
	CSpiritualStrengthRed(int id);
	CSpiritualStrengthRed(int id, int x, int y);
	~CSpiritualStrengthRed();

private:

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
};

