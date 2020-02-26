#include "CGameObject.h"

CGameObject::CGameObject(int id)
{
	this->_currentState = 0;

	this->_positionX = 0;
	this->_positionY = 0;

	this->_positionStartX = this->_positionX;
	this->_positionStartY = this->_positionY;

	this->_vX = 0.0f;
	this->_vY = 0.0f;

	this->_dx = 0;
	this->_dy = 0;

	this->_width = 0;
	this->_height = 0;

	this->_animationCurrent = NULL;

	this->_tag = eObjectType::NONE;

	this->_id = id;

	this->_currentFrame = -1;
	this->_frameTime = 0.0f;

	_nx = 1;
	_nxStart = _nx;

	this->_dt = 0;

	this->_isCutEnemi = false;
	this->_timeCutEnemi = 0;

	//this->_isReset = true;
	//this->_isAlive = true;

	_isFreeze = false;
}

CGameObject::CGameObject(int id, int x, int y)
{
	this->_currentState = 0;

	this->_positionX = (float)x;
	this->_positionY = (float)y;

	this->_positionStartX = this->_positionX;
	this->_positionStartY = this->_positionY;

	this->_vX = 0.0f;
	this->_vY = 0.0f;

	this->_dx = 0;
	this->_dy = 0;

	this->_width = 0;
	this->_height = 0;

	this->_animationCurrent = NULL;

	this->_tag = eObjectType::NONE;

	this->_id = id;

	this->_currentFrame = -1;
	this->_frameTime = 0.0f;

	_nx = 1;
	_nxStart = _nx;

	this->_dt = 0;

	this->_isCutEnemi = false;
	this->_timeCutEnemi = 0;

	//this->_isReset = true;
	//this->_isAlive = true;

	_isFreeze = false;
}

CGameObject::~CGameObject()
{
	_animation.clear();
	_animationCurrent = NULL;
}

LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPCGAMEOBJECT coO)
{
	// Bo va cham voi chinh doi tuong
	if (coO->GetID() == GetID())
	{
		CCollisionEvent* e = new CCollisionEvent(-1.0f, 0, 0, coO);
		return e;
	}

	// Bo va cham voi vat co kich thuoc bang 0
	if (_width == 0.0f ||
		_height == 0.0f ||
		coO->GetWidth() == 0.0f ||
		coO->GetHeight() == 0.0f)
	{
		CCollisionEvent* e = new CCollisionEvent(-1.0f, 0, 0, coO);
		return e;
	}


	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	GetBoundingBox(ml, mt, mr, mb);

	// Kiem tra 2 vat nam chong len nhau
	if (
		((std::abs((sr + sl) - (mr + ml)) / 2.0f) < ((sr - sl + mr - ml) / 2.0f ))
		&&
		((std::abs((st + sb) - (mt + mb)) / 2.0f) < ((st - sb + mt - mb) / 2.0f))
		)
	{
		t = 0.0f;
		nx = 1.0f;
		ny = 0.0f;
		CCollisionEvent* e = new CCollisionEvent(t, nx, ny, coO);
		return e;
	}

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx * _dt;
	float sdy = svy * _dt;

	float dx = this->_dx - sdx;
	float dy = this->_dy - sdy;

	CCollision::GetInstance()->SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t;
			nx = c->nx;
			min_ix = i;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t;
			ny = c->ny;
			min_iy = i;
		}
	}

	if (min_ix >= 0)
		coEventsResult.push_back(coEvents[min_ix]);

	if (min_iy >= 0)
		coEventsResult.push_back(coEvents[min_iy]);
}

void CGameObject::CalcPotentialCollisions(
	vector<LPCGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t >= 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

int CGameObject::GetScore()
{
	return _score;
}

void CGameObject::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	this->_dt = dt;
	_dx = _vX * dt;
	_dy = _vY * dt;

	//this->_isReset = false;
}

void CGameObject::Render()
{
	if (_animationCurrent != NULL)
	{
		_animationCurrent->Render(this->_positionX, this->_positionY, this->_currentFrame, 255);
	}
}

void CGameObject::SetPostion(float x, float y)
{
	this->_positionX = x;
	this->_positionY = y;
}

void CGameObject::GetSpeed(float& vx, float& vy)
{
	vx = this->_vX;
	vy = this->_vY;
}

D3DXVECTOR2 CGameObject::GetPosition()
{
	return D3DXVECTOR2(this->_positionX, this->_positionY);
}

void CGameObject::SetVx(float vx)
{
	_vX = vx;
}

void CGameObject::SetVy(float vy)
{
	_vY = vy;
}

D3DXVECTOR2 CGameObject::GetSpeed()
{
	return D3DXVECTOR2(this->_vX, this->_vY);
}

void CGameObject::RenderBoundingBox()
{
	RectEx rect(GetBoundingBox());

	CDirectX::GetInstance()->DrawBoundingBox(rect.GetRECT());
}

void CGameObject::RenderCollisionBox()
{
	//D3DXVECTOR3 p(_positionX, _positionY, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 cbox = CTextures::GetInstance()->Get(200);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)t - (int)b;


	CDirectX::GetInstance()->DrawSprite(_positionX, _positionY, cbox, rect, 128);
}

int CGameObject::GetState()
{
	return this->_currentState;
}

void CGameObject::SetState(int state)
{
	this->_currentState = state;
}

D3DXVECTOR2 CGameObject::GetD()
{
	return D3DXVECTOR2(_dx, _dy);
}

int CGameObject::GetID()
{
	return this->_id;
}

void CGameObject::UpdateAnimation(DWORD deltaTime)
{
	if ((_currentFrame == -1) || (_currentFrame > (_animationCurrent->GetTotalFrame() - 1)))
	{
		_currentFrame = 0;
		_frameTime = 0.0f;
	}
	else
	{
		_frameTime += deltaTime;

		if (_frameTime > _animationCurrent->GetFrameTime(_currentFrame))
		{
			_frameTime = 0.0f;

			if (_animationCurrent->IsFinishFrame(_currentFrame))
			{
				_currentFrame = 0;
			}
			else
			{
				_currentFrame++;
			}
		}
	}
}


int CGameObject::GetTag()
{
	return this->_tag;
}


int CGameObject::GetHeight()
{
	return (int)_height;
}

int CGameObject::GetWidth()
{
	return (int)_width;
}

void CGameObject::Reset()
{
	//this->_isReset = true;
	//this->_isAlive = true;
}

void CGameObject::SetDirection(int nx)
{
	_nx = nx;
}

int CGameObject::GetDirection()
{
	return _nx;
}

eActionObject CGameObject::GetAction()
{
	return _action;
}

// ================================================================================

//bool CGameObject::IsReset()
//{
//	return _isReset;
//}
//
bool CGameObject::IsAlive()
{
	return true;
}

D3DXVECTOR2 CGameObject::GetPositionStart()
{
	return D3DXVECTOR2(this->_positionStartX, this->_positionStartY);
}

int CGameObject::GetHealth()
{
	return _health;
}

void CGameObject::SetFreeze(bool freeze)
{
	_isFreeze = freeze;
}