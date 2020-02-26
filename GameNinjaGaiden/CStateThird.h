#pragma once

#include "CStates.h"
#include "CGameObject.h"
#include "CGameObjectRyu.h"
#include "CDartsRed.h"
#include "CMap.h"
#include "CGridMap.h"
#include "CSampleKeyHandler.h"
#include "CGameSound.h"
#include "CTime.h"

class CStateThird : public CState
{
public:
	CStateThird();
	CStateThird(int score, int p, int typeweapon);
	~CStateThird();

private:
	vector<LPCGAMEOBJECT> _listObject;	// list object
	int _score;
	int _time;
	int _idWeapon;
	int _number_P;
	int _spiritualStrengthPoint;
	int _stageFirst;
	int _stageSecond;
	int _healthNinja;
	int _healthEnemy;
	int _timeFrameCurrent_Timer;

	bool _isFinnish;

	LPCMAP _map;

	CGameObjectRyu* _objectRyu;
	CDartsRed* _objectDarts;
	CSword* _objectSword;

	CGridMap* _gridMapTest;

public:
	void Init();
	void Update(DWORD dt);
	void Render();
	void Exit();
};