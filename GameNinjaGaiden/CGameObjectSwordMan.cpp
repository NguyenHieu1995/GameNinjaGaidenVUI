#include "CGameObjectSwordMan.h"

CGameObjectSwordMan::CGameObjectSwordMan(int id) : CGameObject(id)
{
	this->_positionX = 100;
	this->_positionY = 100;

	this->_width = SWORDMAN_COLLISION_WIDTH;
	this->_height = SWORDMAN_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(102));

	this->_animationCurrent = _animation[0];

	this->_vX = SWORDMAN_SPEED;

	this->_currentState = eStateSwordMan::RUNSWORDMAN;

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::SWORDMAN;
}

CGameObjectSwordMan::CGameObjectSwordMan(int id, int x, int y, bool direction) : CGameObject(id, x, y)
{
	this->_width = SWORDMAN_COLLISION_WIDTH;
	this->_height = SWORDMAN_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(102));

	this->_animationCurrent = _animation[0];

	if (direction)
	{
		this->_vX = SWORDMAN_SPEED;
		_nx = 1;
		_nxStart = _nx;
	}
	else
	{
		this->_vX = -SWORDMAN_SPEED;
		_nx = -1;
		_nxStart = _nx;
	}

	this->_currentState = eStateSwordMan::RUNSWORDMAN;

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::SWORDMAN;
}

CGameObjectSwordMan::~CGameObjectSwordMan()
{
}

void CGameObjectSwordMan::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	if ((_positionX < CCamera::GetInstance()->GetBound().left) && (_nx < 0))
	{
		_nx = 1;
	}

	if ((_positionX > CCamera::GetInstance()->GetBound().right) && (_nx > 0))
	{
		_nx = -1;
	}

	if (_isFreeze)
	{
		if (_positionX == _positionStartX)
		{
			SetState(eStateSwordMan::DIESWORDMAN);
		}
		//return;
	}

	if ((_positionX < CCamera::GetInstance()->GetBound().left - SCREEN_WIDTH / 2) ||
		(_positionX > CCamera::GetInstance()->GetBound().right + SCREEN_WIDTH / 2))
	{
		SetState(eStateSwordMan::DIESWORDMAN);
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

	if (_currentState == eStateCat::DIE)
	{
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

		//CGameObject::Update(dt, coObject);
		//UpdateAnimation(dt);
		this->_vX = _nx * SWORDMAN_SPEED;
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

	//this->_dx = _vX * dt;
	//this->_dy = _vY * dt;

	//_positionX += _vX * dt;

	//_positionY += _vY * dt;		

	if (coEvents.size() == 0)
	{
		_positionX += _dx;
		_positionY += _dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		_positionX += _dx;
		//_positionY += _dy;

		//_positionX += min_tx * _dx + nx * 0.4f;
		_positionY += min_ty * _dy + ny * 0.4f;

		/*if (nx != 0)
			_vX = 0;
		else*/
		_vX = SWORDMAN_SPEED;

		if (ny >= 0) _vY = 0;

		for (int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CSword*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateSwordMan::DIESWORDMAN);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CDartsRed*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateSwordMan::DIESWORDMAN);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CDartsSmall*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateSwordMan::DIESWORDMAN);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CFirebullet*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateSwordMan::DIESWORDMAN);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CGameObjectWall*>(e->obj))
			{
				CGameObjectWall* wall = dynamic_cast<CGameObjectWall*>(e->obj);

				if ((_nx < 0) && (_positionX <= wall->GetPosition().x))
				{
					_nx = 1.0f;
				}
				else
				{
					if ((_nx >= 0) && (_positionX + _width >= (wall->GetPosition().x + wall->GetWidth())))
					{
						_nx = -1.0f;
					}
				}
			}

			if (dynamic_cast<CGameObjectGround*>(e->obj))
			{
				CGameObjectGround* ground = dynamic_cast<CGameObjectGround*>(e->obj);

				if ((_nx < 0) && ((_positionX + (_width * 0.5f)) <= ground->GetPosition().x) && (e->obj->GetPosition().y < _positionY))
				{
					_nx = 1.0f;
				}
				else
				{
					if ((_nx >= 0) && (_positionX + _width - (_width * 0.5f) >= (ground->GetPosition().x + ground->GetWidth())) && (e->obj->GetPosition().y < _positionY))
					{
						_nx = -1.0f;
					}
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

RectEx CGameObjectSwordMan::GetBoundingBox()
{

	RectEx rect(
		_positionY + this->_height,
		_positionX,
		_positionY,
		_positionX + this->_width
	);

	return rect;
}

void CGameObjectSwordMan::Render()
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

	if (this->_currentState == eStateSwordMan::DIESWORDMAN)
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

void CGameObjectSwordMan::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}

void CGameObjectSwordMan::SetState(int state)
{
	CGameObject::SetState(state);
	switch (_currentState)
	{
	case eStateSwordMan::DIESWORDMAN:
		_vX = 0;
		_vY = 0;
		this->_width = 0;
		this->_height = 0;
		//this->_isAlive = false;
		//this->_positionX = this->_positionStartX;
		//this->_positionY = this->_positionStartY;
		this->_nx = this->_nxStart;
		break;

	case eStateSwordMan::RUNSWORDMAN:
		_vX = SWORDMAN_SPEED;
		_vY = 0;
		this->_width = SWORDMAN_COLLISION_WIDTH;
		this->_height = SWORDMAN_COLLISION_HEIGHT;
		break;

	default:
		break;
	}
}

void CGameObjectSwordMan::Reset()
{
	CGameObject::Reset();
	this->_positionX = this->_positionStartX;
	this->_positionY = this->_positionStartY;
	this->_nx = this->_nxStart;
	SetState(eStateSwordMan::RUNSWORDMAN);
}

bool CGameObjectSwordMan::IsAlive()
{
	if (_currentState == eStateSwordMan::DIESWORDMAN)
	{
		return false;
	}
	else
	{
		return true;
	}
}