#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <algorithm> 
#include <stdlib.h>
#include "CConstant.h"
#include "CDebug.h"
#include "CDirectX.h"
#include "CTextures.h"

#include "CSprites.h"
#include "CAnimations.h"
#include <cmath>
#include "CStruct.h"
#include "CStateObject.h"
#include "CEnumsOfGame.h"
#include "CCollision.h"
#include "CGameSound.h"

class CGameObject;
typedef CGameObject* LPCGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPCGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPCGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};

class CGameObject
{
public:
	CGameObject(int id);
	CGameObject(int id, int x, int y); 

	virtual ~CGameObject();

protected:
	int _id;								// Id of Object (Phan biet giua cac doi tuong)	
	float _positionX, _positionY;			// Position of Object
	float _positionStartX, _positionStartY; // Vi tri ban dau cua doi tuong => dung de reset object
	float _vX, _vY;							// Speed of Object
	int _currentState;						// State of Object
	float _dx, _dy;							// Khoach cach di chuyen trong mot frame
	float _width, _height;					// Kich thuoc va cham cua doi tuong

	int _nx;								// Huong di chuyen cua doi tuong
	int _nxStart;

	int _currentFrame;
	float _frameTime;

	DWORD _dt;

	vector<LPCANIMATION> _animation;
	LPCANIMATION _animationCurrent;
	eObjectType _tag;				// Loai object

	bool _isCutEnemi;
	float _timeCutEnemi;
	eActionObject _action; 
	//bool _isReset;
	//bool _isAlive;
	int _health;
	bool _isFreeze;

	int _score;

public:
	int GetScore();

	virtual void Update(DWORD dt, vector<LPCGAMEOBJECT> *coObject);
	virtual void Render();
	virtual void Reset();

	void SetDirection(int nx);
	int GetDirection();

	void UpdateAnimation(DWORD deltaTime);

	void SetPostion(float x, float y);
	D3DXVECTOR2 GetPosition();
	D3DXVECTOR2 GetPositionStart();
	/*void AddAnimation(int animationId);*/
	virtual void SetVx(float vx);
	virtual void SetVy(float vy);
	D3DXVECTOR2 GetSpeed();
	void GetSpeed(float& vx, float& vy);
	D3DXVECTOR2 GetD();
	int GetTag();

	int GetHeight();
	int GetWidth();

	int GetState();

	virtual RectEx GetBoundingBox() = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void SetState(int state);
	void RenderBoundingBox();
	void RenderCollisionBox();

	LPCOLLISIONEVENT SweptAABBEx(LPCGAMEOBJECT coO);

	void CalcPotentialCollisions(vector<LPCGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);

	int GetID();


	eActionObject GetAction();

	//bool IsReset();
	virtual bool IsAlive();

	int GetHealth();

	void SetFreeze(bool freeze);
};

//typedef CGameObject* LPCGAMEOBJECT;

// =========================================================
// Database Object
