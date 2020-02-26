#pragma once

#define WIN32_LEAN_AND_MEAN

#include <d3d9.h>
#include <d3dx9.h>
#include "CConstant.h"
#include "CDebug.h"
#include "CDirectX.h"
#include "Tiny/tinyxml.h"
#include "CFunction.h"
#include "CTextures.h"
#include "CSprites.h"
#include "CAnimations.h"
#include "CTime.h"
#include <mmsystem.h>
#include "CInput.h"
#include "CCamera.h"
#include "CCollision.h"
#include "CGameObject.h"
#include "CMap.h"
#include "CGameObjectRyu.h"
#include "CGameObjectGround.h"
#include "CGridMap.h"
#include "CGameObjects.h"


#include "CGameObjectBirdBrown.h"
#include "CGameObjectBanshee.h"
#include "CGameObjectBatBrown.h"
#include "CGameObjectCat.h"
#include "CGameObjectSwordMan.h"
#include "CGameObjectMachineGunGuy.h"
#include "CBulletMachineGunGuy.h"
#include "CDartsSmall.h"

#include "CSword.h"
#include "CDartsRed.h"
#include "CFireBullet.h"

#include "CGameSound.h"




class CGame
{
private:
	LARGE_INTEGER _timeStart;		// Performance Counter start value
	LARGE_INTEGER _timeEnd;			// Performance Counter end value
	LARGE_INTEGER _timerFreq;		// Performance Counter frequency
	float _frameTime;				// time required for last frame
	float _fps;						// frames per second
	DWORD _sleepTime;				// number of milli-seconds to sleep between frames
	bool _paused;					// true if game is paused
	bool _initialized;				// true if game initialized;
	vector<LPCGAMEOBJECT> _listObject;	// list object
	//unordered_map<int, LPCGAMEOBJECT> _listObject;

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


private:
	// Object in Game
	//CGameObject *test;
	CCollisionInfo* collisionTest;
	//CInput* _testInput;

	CMap* _map;

	CGame();

private:
	static CGame* _instance;

	// List object
public:
	CGameObjectRyu* _objectRyu;
	//CGameObjectBirdBrown* _objectBirdBrown;
	//CGameObjectGround* _objectGround;
	CDartsRed* _objectDarts;
	CSword* _objectSword;
	// Test
public:
	CGridMap* _gridMapTest;

	// 

public:
	~CGame();
	static CGame* GetInstance();
	bool Init(); // Khoi tao chuong tinh
	void Run();

private:
	void Update(DWORD dt);
	void Render();
	void LoadResource();
};

