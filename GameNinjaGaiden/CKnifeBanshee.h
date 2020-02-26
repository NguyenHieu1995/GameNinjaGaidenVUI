#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "CGameObject.h"

class CKnifeBanshee : public CGameObject
{
public:
	CKnifeBanshee(int id);
	CKnifeBanshee(int id, int x, int y);
	virtual ~CKnifeBanshee();

private:
	int _angle; //

public:
	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();

	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void SetState(int state);
};
