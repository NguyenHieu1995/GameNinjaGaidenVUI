#pragma once

#include "CGameObject.h"

class CSpiritualStrengthBlue : public CGameObject
{
public:
	CSpiritualStrengthBlue(int id);
	CSpiritualStrengthBlue(int id, int x, int y);
	~CSpiritualStrengthBlue();

private:

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();
	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void SetState(int state);
};

