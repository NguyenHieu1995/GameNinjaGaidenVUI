#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "CGameObject.h"
#include "CGameObjectCat.h"
#include "CGameObjectRyu.h"

class CDartsRed : public CGameObject
{
public:
	CDartsRed(int id);
	CDartsRed(int id, int x, int y);
	~CDartsRed();

private:
	int _angle; // Goc xoay cua phi tieu 0 < _angle < 360
	//D3DXVECTOR2 _positionCutEnemi;
	bool _isCatch;

	float _posCharacterX;
	float _posCharecterY;

	//int _score;

public:
	//int GetScore();

	void Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject);
	void Render();

	virtual RectEx GetBoundingBox();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	virtual void SetState(int state);

	void SetPositionCharacter(float x, float y);
};
