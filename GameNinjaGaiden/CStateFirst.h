#pragma once

#include "CStates.h"
#include "CCamera.h"
#include "CGameSound.h"
#include "CMap.h"

#include "CSword.h"
#include "CDartsRed.h"
#include "CGameObjectRyu.h"
#include "CGridMap.h"

#include "CDirectX.h"
#include "CFunction.h"
#include "CTextures.h"
#include "CSprites.h"
#include "CAnimations.h"
#include "CTime.h"

#include "CInput.h"
#include "CCollision.h"
#include "CGameObject.h"

#include "CSampleKeyHandler.h"

class CStateFirst : public CState
{
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

	// sound test
	//CGameSound* _testSound;
	//LPDIRECTSOUNDBUFFER _DSBuffer;

	LPCMAP _map;

	CGameObjectRyu* _objectRyu;
	//CGameObjectBirdBrown* _objectBirdBrown;
	//CGameObjectGround* _objectGround;
	CDartsRed* _objectDarts;
	CSword* _objectSword;

	CGridMap* _gridMapTest;

public:
	CStateFirst();
	~CStateFirst();

public:
	void Init();
	void Update(DWORD dt);
	void Render();
	void Exit();
};
