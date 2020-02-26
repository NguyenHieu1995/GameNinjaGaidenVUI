#include "CGameObjectBirdBrown.h"

CGameObjectBirdBrown::CGameObjectBirdBrown(int id) : CGameObject(id)
{
	this->_positionX = 100;
	this->_positionY = 100;

	this->_width = BIRDBROWN_COLLISION_WIDTH;
	this->_height = BIRDBROWN_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(100));

	this->_animationCurrent = _animation[0];

	this->_vX = BIRDBROWN_SPEED;

	this->_currentState = eStateBirdBrown::FLYBIRDBROWN;

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::BIRDBROWN;
}

CGameObjectBirdBrown::CGameObjectBirdBrown(int id, int x, int y, bool direction) : CGameObject(id, x, y)
{
	this->_width = BIRDBROWN_COLLISION_WIDTH;
	this->_height = BIRDBROWN_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(100));

	this->_animationCurrent = _animation[0];

	if (direction)
	{
		_nx = 1;
		this->_vX = BIRDBROWN_SPEED;
		SetState(eStateBirdBrown::DIEBIRDBROWN);
	}
	else
	{
		_nx = -1;
		this->_vX = -BIRDBROWN_SPEED;
		SetState(eStateBirdBrown::FLYBIRDBROWN);
	}

	_nxStart = _nx;

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::BIRDBROWN;

	//this->_currentState = eStateBirdBrown::FLYBIRDBROWN;
}

CGameObjectBirdBrown::~CGameObjectBirdBrown()
{
}

void CGameObjectBirdBrown::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	if (_isFreeze)
	{
		if (_positionX == _positionStartX)
		{
			SetState(eStateBirdBrown::DIEBIRDBROWN);
		}
		//return;
	}

	if ((_positionX < CCamera::GetInstance()->GetBound().left - SCREEN_WIDTH / 2) ||
		(_positionX > CCamera::GetInstance()->GetBound().right + SCREEN_WIDTH / 2) ||
		(_positionY > SCREEN_HEIGHT) ||
		(_positionY < 0))
	{
		SetState(eStateBirdBrown::DIEBIRDBROWN);
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

	if ((_nxStart > 0) && (_positionX == _positionStartX) && (_positionX < (CCamera::GetInstance()->GetBound().left)) && _currentState == eStateBirdBrown::DIEBIRDBROWN)
	{
		SetState(eStateBirdBrown::FLYBIRDBROWN);
		return;
	}

	if (_currentState == eStateBirdBrown::DIEBIRDBROWN)
	{
		//Reset();

		return;
	}

	//this->_vX = 0;
	//this->_vY = 0;

	if (_isFreeze)
	{
		this->_vX = 0;
		this->_vY = 0;
	}
	else
	{
		_frameTime += dt;
	}

	CGameObject::Update(dt, coObject);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPCGAMEOBJECT> listObject;
	listObject.clear();

	for (UINT i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i)->GetTag() == eObjectType::SWORD ||
			coObject->at(i)->GetTag() == eObjectType::DARTSRED ||
			coObject->at(i)->GetTag() == eObjectType::DARTSSMALL || 
			coObject->at(i)->GetTag() == eObjectType::FIREBULLET)
		{
			listObject.push_back(coObject->at(i));
		}
	}

	CalcPotentialCollisions(&listObject, coEvents);
	listObject.clear();

	

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
			_vX = _nx* BANSHEE_SPEED;

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

	if (std::abs(_positionX - _posCharacterX) > 50.0f)
	{
		if ((_positionX - _posCharacterX) >= 0)
		{
			_nx = -1;
			_vX = _nx * BIRDBROWN_SPEED;
		}
		else
		{
			_nx = 1;
			_vX = _nx * BIRDBROWN_SPEED;
		}

		if (_positionY != _posCharecterY)
		{
			/*if (_positionY > _posCharecterY)
			{
				_vY = -();
			}
			else
			{
				_vY = 1.0f;
			}*/
			_vY = (_posCharecterY - _positionY) / (std::abs(_positionX - _posCharacterX) / BIRDBROWN_SPEED);
		}
		else
		{
			_vY = 0;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

RectEx CGameObjectBirdBrown::GetBoundingBox()
{
	RectEx rect(
		_positionY + this->_height,
		_positionX,
		_positionY,
		_positionX + this->_width
	);
	
	return rect;
}

void CGameObjectBirdBrown::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}

void CGameObjectBirdBrown::Render()
{
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

	if (this->_currentState == eStateBanshee::DIEBANSHEE)
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
					/*if (_currentState == eStateBanshee::ATTACKBANSHEE)
					{
						SetState(eStateBanshee::RUNBANSHEE);
						_isAttack = false;
					}*/
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

void CGameObjectBirdBrown::SetState(int state)
{
	CGameObject::SetState(state);

	switch (_currentState)
	{
	case eStateBirdBrown::DIEBIRDBROWN:
		_vX = 0;
		_vY = 0;
		this->_width = 0;
		this->_height = 0;
		//this->_isAlive = false;
		//this->_positionX = this->_positionStartX;
		//this->_positionY = this->_positionStartY;
		this->_nx = this->_nxStart;
		break;

	case eStateBirdBrown::FLYBIRDBROWN:
		_vX = _nx * BIRDBROWN_SPEED;
		_vY = 0;
		this->_width = BIRDBROWN_COLLISION_WIDTH;
		this->_height = BIRDBROWN_COLLISION_HEIGHT;
		//this->_animationCurrent = this->_animation[0];
		break;

	default:
		break;
	}
}

void CGameObjectBirdBrown::Reset()
{
	CGameObject::Reset();
	this->_positionX = this->_positionStartX;
	this->_positionY = this->_positionStartY;
	this->_nx = this->_nxStart;
	//SetState(eStateBirdBrown::FLYBIRDBROWN);
	if (_nxStart > 0)
	{
		SetState(eStateBirdBrown::DIEBIRDBROWN);
	}
	else
	{
		SetState(eStateBirdBrown::FLYBIRDBROWN);
	}
}

void CGameObjectBirdBrown::SetPositionCharacter(float x, float y)
{
	this->_posCharacterX = x;
	this->_posCharecterY = y;
}

bool CGameObjectBirdBrown::IsAlive()
{
	if (_currentState == eStateBirdBrown::DIEBIRDBROWN)
	{
		return false;
	}
	else
	{
		return true;
	}
}