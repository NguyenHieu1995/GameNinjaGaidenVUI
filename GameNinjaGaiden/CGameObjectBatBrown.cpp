#include "CGameObjectBatBrown.h"

CGameObjectBatBrown::CGameObjectBatBrown(int id) : CGameObject(id)
{
	this->_positionX = 100;
	this->_positionY = 100;

	this->_width = BATBROWN_COLLISION_WIDTH;
	this->_height = BATBROWN_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(103));

	this->_animationCurrent = _animation[0];

	//this->_vX = BAT_SPEED;

	SetState(eStateBat::FLYBAT);

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::BATBROWN;

	this->_angle = 0;
}

CGameObjectBatBrown::CGameObjectBatBrown(int id, int x, int y, bool direction) : CGameObject(id, x, y)
{
	this->_width = BATBROWN_COLLISION_WIDTH;
	this->_height = BATBROWN_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(103));

	this->_animationCurrent = _animation[0];

	if (direction == 1)
	{
		_nx = 1;
		SetState(eStateBat::DIEBAT);
	}
	else
	{
		_nx = -1;
		SetState(eStateBat::FLYBAT);
	}

	this->_nxStart = _nx;

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::BATBROWN;

	this->_angle = 0;
}

CGameObjectBatBrown::~CGameObjectBatBrown()
{
}

void CGameObjectBatBrown::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	if (_isFreeze)
	{
		if (_positionX == _positionStartX)
		{
			SetState(eStateBat::DIEBAT);
		}
		//return;
	}

	if ((_positionX < CCamera::GetInstance()->GetBound().left - SCREEN_WIDTH / 4) ||
		(_positionX > CCamera::GetInstance()->GetBound().right + SCREEN_WIDTH / 4) ||
		(_positionY > SCREEN_HEIGHT) ||
		(_positionY < 0))
	{
		SetState(eStateBat::DIEBAT);
	}

	if (_isCutEnemi)
	{
		_timeCutEnemi += dt;

		if (_timeCutEnemi > TIME_CUT_ENEMI)
		{
			_timeCutEnemi = 0;
			_isCutEnemi = false;
		}
	}

	if ((_nxStart > 0) && (_positionX == _positionStartX) && (_positionX < (CCamera::GetInstance()->GetBound().left)) && (_currentState == eStateBat::DIEBAT))
	{
		SetState(eStateBat::FLYBAT);
		return;
	}

	if (_currentState == eStateBat::DIEBAT)
	{
		return;
	}

	if (!_isFreeze)
	{
		this->_vX = _nx * BAT_SPEED;

		_angle += 20;
		if (_angle >= 360)
		{
			_angle -= 360;
		}
		this->_vY = 0.15f * sin(_angle * PI / 180);

		_frameTime += dt;
	}
	else
	{
		this->_vX = 0;
		this->_vY = 0;
	}
	CGameObject::Update(dt, coObject);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPCGAMEOBJECT> listMapObject;
	listMapObject.clear();

	for (UINT i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i)->GetTag() == eObjectType::SWORD ||
			coObject->at(i)->GetTag() == eObjectType::DARTSRED ||
			coObject->at(i)->GetTag() == eObjectType::DARTSSMALL ||
			coObject->at(i)->GetTag() == eObjectType::FIREBULLET)
		{
			listMapObject.push_back(coObject->at(i));
		}
	}

	CalcPotentialCollisions(&listMapObject, coEvents);
	listMapObject.clear();

	if (coEvents.size() == 0)
	{
		_positionX += _dx;
		_positionY += _dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		_positionX += min_tx * _dx + nx * 0.4f;
		_positionY += min_ty * _dy + ny * 0.4f;

		if (nx != 0)
			_vX = 0;
		else
			_vX = _nx * BAT_SPEED;

		if (ny != 0) _vY = 0;


		for (int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CSword*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateBirdBrown::DIEBIRDBROWN);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CDartsRed*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateBirdBrown::DIEBIRDBROWN);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CDartsSmall*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateBirdBrown::DIEBIRDBROWN);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CFirebullet*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateBirdBrown::DIEBIRDBROWN);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

RectEx CGameObjectBatBrown::GetBoundingBox()
{

	RectEx rect(
		_positionY + this->_height,
		_positionX,
		_positionY,
		_positionX + this->_width
	);

	return rect;
}

void CGameObjectBatBrown::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}

bool CGameObjectBatBrown::IsAlive()
{
	if (_currentState == eStateBat::DIEBAT)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void CGameObjectBatBrown::Render()
{
	if (_isCutEnemi)
	{
		float e = _timeCutEnemi * 0.1f;

		CSprites::GetInstance()->Get(24)->Draw(this->_positionCutEnemi.x - e, this->_positionCutEnemi.y + e, 255, false, false);
		CSprites::GetInstance()->Get(25)->Draw(this->_positionCutEnemi.x + e, this->_positionCutEnemi.y + e, 255, false, false);
		CSprites::GetInstance()->Get(46)->Draw(this->_positionCutEnemi.x - e, this->_positionCutEnemi.y - e, 255, false, false);
		CSprites::GetInstance()->Get(47)->Draw(this->_positionCutEnemi.x + e, this->_positionCutEnemi.y - e, 255, false, false);
	}

	if (this->_currentState == eStateBat::DIEBAT)
		return;

	bool flip;

	if (_nx >= 0)
		flip = false;
	else
		flip = true;


	if (_animationCurrent != NULL)
	{
		if ((_currentFrame == -1) || (_currentFrame > (_animationCurrent->GetTotalFrame() - 1)))
		{
			_currentFrame = 0;
			_frameTime = 0.0f;
		}
		else
		{
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

		_animationCurrent->Render(this->_positionX, this->_positionY, this->_currentFrame, 255, flip);
	}
}

void CGameObjectBatBrown::SetState(int state)
{
	CGameObject::SetState(state);
	switch (_currentState)
	{
	case eStateBat::DIEBAT:
		_vX = 0;
		_vY = 0;
		this->_width = 0;
		this->_height = 0;
		this->_nx = this->_nxStart;
		this->_animationCurrent = NULL;
		break;

	case eStateBat::FLYBAT:
		_vX = _nx * BAT_SPEED;
		_vY = 0;
		this->_width = BATBROWN_COLLISION_WIDTH;
		this->_height = BATBROWN_COLLISION_HEIGHT;
		this->_animationCurrent = _animation[0];
		break;

	default:
		break;
	}
}

void CGameObjectBatBrown::Reset()
{
	CGameObject::Reset();
	this->_positionX = this->_positionStartX;
	this->_positionY = this->_positionStartY;
	this->_nx = this->_nxStart;
	if (_nxStart > 0)
	{
		SetState(eStateBat::DIEBAT);
	}
	else
	{
		SetState(eStateBat::FLYBAT);
	}
}