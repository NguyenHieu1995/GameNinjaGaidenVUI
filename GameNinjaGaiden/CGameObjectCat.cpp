#include "CGameObjectCat.h"
#include "CGameObjectGround.h"

CGameObjectCat::CGameObjectCat(int id) : CGameObject(id)
{
	this->_positionX = 100;
	this->_positionY = 100;

	this->_width = CAT_COLLISION_WIDTH;
	this->_height = CAT_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(101));

	this->_animationCurrent = _animation[0];

	this->_vX = CAT_SPEED;

	this->_currentState = eStateCat::RUN;

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::CAT;
}

CGameObjectCat::CGameObjectCat(int id, int x, int y, bool direction) : CGameObject(id, x, y)
{
	this->_width = CAT_COLLISION_WIDTH;
	this->_height = CAT_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(101));

	this->_animationCurrent = _animation[0];

	if (direction == 1)
	{
		_nx = 1;
		_nxStart = _nx;
		//this->_vX = CAT_SPEED;
		SetState(eStateCat::DIE);
	}
	else
	{
		_nx = -1;
		_nxStart = _nx;
		//this->_vX = -CAT_SPEED;
		SetState(eStateCat::RUN);
	}

	//this->_currentState = eStateCat::RUN;

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::CAT;
}

CGameObjectCat::~CGameObjectCat()
{
}

void CGameObjectCat::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	if (_isFreeze)
	{
		if (_positionX == _positionStartX)
		{
			SetState(eStateCat::DIE);
		}
		//return;
	}

	if ((_positionX < CCamera::GetInstance()->GetBound().left - SCREEN_WIDTH / 4) ||
		(_positionX > CCamera::GetInstance()->GetBound().right + SCREEN_WIDTH / 4) ||
		(_positionY > SCREEN_HEIGHT) ||
		(_positionY < 0))
	{
		SetState(eStateCat::DIE);
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

	if ((_nxStart > 0) && (_positionX == _positionStartX) && (_positionX < (CCamera::GetInstance()->GetBound().left)) && _currentState == eStateCat::DIE)
	{
		SetState(eStateCat::RUN);
		return;
	}

	if (_currentState == eStateCat::DIE)
	{
		/*SetState(eStateCat::RUN);
		_positionX = 600;
		_positionY = 200;*/

		//Reset();

		return;
	}

	//===
	// TEST
	/*if (_positionX < 10 && _nx < 0)
	{
		_nx = 1;
	}
	if (_positionX > 1300 && _nx > 0)
	{
		_nx = -1;
	}*/
	//===
	if (!_isFreeze)
	{
		this->_vX = _nx * CAT_SPEED;
		//this->_vX = 0;

		if (_vY == 0)
			_vY = CAT_JUMP;

		_vY += GRAVITY * dt;

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
		if (coObject->at(i)->GetTag() == eObjectType::GROUND ||
			coObject->at(i)->GetTag() == eObjectType::WALL ||
			coObject->at(i)->GetTag() == eObjectType::SWORD ||
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
			_vX = _nx * CAT_SPEED;

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
				SetState(eStateCat::DIE);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CDartsRed*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateCat::DIE);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CDartsSmall*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateCat::DIE);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CFirebullet*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateCat::DIE);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

RectEx CGameObjectCat::GetBoundingBox()
{
	RectEx rect(
		_positionY + this->_height,
		_positionX,
		_positionY,
		_positionX + this->_width
	);

	return rect;
}

void CGameObjectCat::Render()
{
	// Update animation and render

	if (_isCutEnemi)
	{
		float e = _timeCutEnemi * 0.1f;
		//int px = _positionX + _width / 2.0f;
		//int py = _positionY + _height / 2.0f;

		CSprites::GetInstance()->Get(24)->Draw(this->_positionCutEnemi.x - e, this->_positionCutEnemi.y + e, 255, false, false);
		CSprites::GetInstance()->Get(25)->Draw(this->_positionCutEnemi.x + e, this->_positionCutEnemi.y + e, 255, false, false);
		CSprites::GetInstance()->Get(46)->Draw(this->_positionCutEnemi.x - e, this->_positionCutEnemi.y - e, 255, false, false);
		CSprites::GetInstance()->Get(47)->Draw(this->_positionCutEnemi.x + e, this->_positionCutEnemi.y - e, 255, false, false);
	}

	if (this->_currentState == eStateCat::DIE)
		return;

	/*if (_nxStart > 0 && _positionX == _positionStartX && _positionX > CCamera::GetInstance()->GetBound().left)
	{
		return;
	}*/

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

void CGameObjectCat::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}

void CGameObjectCat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (_currentState)
	{
	case eStateCat::DIE:
		_vX = 0;
		_vY = 0;
		this->_width = 0;
		this->_height = 0;
		//this->_isAlive = false;
		//this->_positionX = this->_positionStartX;
		//this->_positionY = this->_positionStartY;
		this->_nx = this->_nxStart;
		break;

	case eStateCat::RUN:
		_vX = _nx * CAT_SPEED;
		_vY = 0;
		this->_width = CAT_COLLISION_WIDTH;
		this->_height = CAT_COLLISION_HEIGHT;
		break;

	default:
		break;
	}
}

void CGameObjectCat::Reset()
{
	CGameObject::Reset();
	this->_positionX = this->_positionStartX;
	this->_positionY = this->_positionStartY;
	this->_nx = this->_nxStart;
	//SetState(eStateCat::RUN);
	if (_nxStart > 0)
	{
		SetState(eStateCat::DIE);
	}
	else
	{
		SetState(eStateCat::RUN);
	}
}

bool CGameObjectCat::IsAlive()
{
	if (_currentState == eStateCat::DIE)
	{
		return false;
	}
	else
	{
		return true;
	}
}