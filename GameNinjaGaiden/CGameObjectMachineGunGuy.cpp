#include "CGameObjectMachineGunGuy.h"

CGameObjectMachineGunGuy::CGameObjectMachineGunGuy(int id) : CGameObject(id)
{
	this->_positionX = 100;
	this->_positionY = 100;

	this->_width = MACHINEGUNGUY_COLLISION_WIDTH;
	this->_height = MACHINEGUNGUY_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(106));
	_animation.push_back(CAnimations::GetInstance()->Get(107));

	this->_animationCurrent = _animation[0];

	this->_vX = MACHINEGUNGUY_SPEED;

	this->_currentState = eStateMachineGunGuy::RUNMACHINEGUNGUY;

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::MACHINEGUNGUY;

	_isAttack = false;
	_idBullet = 0;
	_numberBullet = NUMBER_MACHINEGUNGUY;
	this->_timeAttack = 0;
}

CGameObjectMachineGunGuy::CGameObjectMachineGunGuy(int id, int x, int y, bool direction) : CGameObject(id, x, y)
{
	this->_width = MACHINEGUNGUY_COLLISION_WIDTH;
	this->_height = MACHINEGUNGUY_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(106));
	_animation.push_back(CAnimations::GetInstance()->Get(107));

	this->_animationCurrent = _animation[0];

	if (direction)
	{
		_nx = 1;
		this->_vX = MACHINEGUNGUY_SPEED;
	}
	else
	{
		_nx = -1;
		this->_vX = -MACHINEGUNGUY_SPEED;
	}

	this->_currentState = eStateMachineGunGuy::RUNMACHINEGUNGUY;

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::MACHINEGUNGUY;

	_isAttack = false;
	_idBullet = 0;
	_numberBullet = NUMBER_MACHINEGUNGUY;

	this->_timeAttack = 0;
}

CGameObjectMachineGunGuy::~CGameObjectMachineGunGuy()
{
}

void CGameObjectMachineGunGuy::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	if (_isFreeze)
	{
		if (_positionX == _positionStartX)
		{
			SetState(eStateMachineGunGuy::DIEMACHINEGUNGUY);
		}
		//return;
	}

	if ((_positionX < CCamera::GetInstance()->GetBound().left - SCREEN_WIDTH / 2) ||
		(_positionX > CCamera::GetInstance()->GetBound().right + SCREEN_WIDTH / 2))
	{
		SetState(eStateMachineGunGuy::DIEMACHINEGUNGUY);
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

	if (_currentState == eStateMachineGunGuy::DIEMACHINEGUNGUY)
	{
		//Reset();
		return;
	}

	_timeAttack += dt;

	if (_timeAttack > 2000)
	{
		SetState(eStateMachineGunGuy::ATTACKMACHINEGUNGUY);
		_timeAttack = 0;
	}

	// TEST
	// =====
	/*if ((_positionX - _positionStartX) < -50 && _nx < 0)
	{
		_nx = 1;
		SetState(eStateMachineGunGuy::ATTACKMACHINEGUNGUY);
	}
	if ((_positionX - _positionStartX) > 50 && _nx > 0)
	{
		_nx = -1;
		SetState(eStateMachineGunGuy::ATTACKMACHINEGUNGUY);
	}*/
	// =====

	//this->_vX = _nx * MACHINEGUNGUY_SPEED;

	if (!_isFreeze)
	{
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

		_positionX += _dx;
		//_positionY += _dy;

		//_positionX += min_tx * _dx + nx * 0.4f;
		_positionY += min_ty * _dy + ny * 0.4f;

		/*if (!_isAttack)
		{
			if (nx != 0)
				_vX = 0;
			else
				_vX = _nx * MACHINEGUNGUY_SPEED;
		}*/

		_vX = _nx * MACHINEGUNGUY_SPEED;

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
				SetState(eStateMachineGunGuy::DIEMACHINEGUNGUY);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CDartsRed*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateMachineGunGuy::DIEMACHINEGUNGUY);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CDartsSmall*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateMachineGunGuy::DIEMACHINEGUNGUY);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CFirebullet*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateMachineGunGuy::DIEMACHINEGUNGUY);
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
				CGameObjectGround* wall = dynamic_cast<CGameObjectGround*>(e->obj);

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
		}

	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	//UpdateAnimation(dt);

	//if (_isAttack)
	//{
	//	if ((_numberBullet == NUMBER_MACHINEGUNGUY) ||
	//		((_numberBullet > 0) && (_numberBulletCurrent != _numberBullet)))
	//	{
	//		_numberBulletCurrent = _numberBullet;
	//		//DebugOut(L"\nAdd Bullet! %d", _numberBullet);
	//		_idBullet++;
	//		if (_idBullet > 50)
	//		{
	//			_idBullet = 0;
	//		}

	//		CBulletMachineGunGuy* bullet = new CBulletMachineGunGuy(2000 + _idBullet, 100, 100);
	//		CGameObjects::GetInstance()->AddObject(bullet);
	//	}
	//}
}

RectEx CGameObjectMachineGunGuy::GetBoundingBox()
{

	RectEx rect(
		_positionY + this->_height,
		_positionX,
		_positionY,
		_positionX + this->_width
	);

	return rect;
}

void CGameObjectMachineGunGuy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}

void CGameObjectMachineGunGuy::Render()
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

	if (this->_currentState == eStateMachineGunGuy::DIEMACHINEGUNGUY)
	{
		return;
	}

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

					if (_currentState == eStateMachineGunGuy::ATTACKMACHINEGUNGUY)
					{
						//SetState(eStateMachineGunGuy::RUNMACHINEGUNGUY);
						if (_numberBullet < 1)
						{
							_isAttack = false;
							SetState(eStateMachineGunGuy::RUNMACHINEGUNGUY);
						}
						else
						{
							_numberBullet--;

							_idBullet++;
							if (_idBullet > 50)
							{
								_idBullet = 0;
							}
							if (_nx >= 0)
							{
								CBulletMachineGunGuy* bullet = new CBulletMachineGunGuy(_id * 100 + _idBullet, _positionX + _width, _positionY + _height * 0.5f);
								bullet->SetDirection(1.0f);
								CGameObjects::GetInstance()->AddObject(bullet);
							}
							else
							{
								CBulletMachineGunGuy* bullet = new CBulletMachineGunGuy(_id * 100 + _idBullet, _positionX, _positionY + _height * 0.5f);
								bullet->SetDirection(-1.0f);
								CGameObjects::GetInstance()->AddObject(bullet);
							}

						}
					}
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

void CGameObjectMachineGunGuy::SetState(int state)
{
	CGameObject::SetState(state);

	switch (_currentState)
	{
	case eStateMachineGunGuy::DIEMACHINEGUNGUY:
		this->_vX = 0;
		this->_vY = 0;
		this->_width = 0;
		this->_height = 0;
		//this->_isAlive = false;
		//this->_positionX = this->_positionStartX;
		//this->_positionY = this->_positionStartY;
		_animationCurrent = NULL;
		this->_nx = this->_nxStart;
		break;

	case eStateMachineGunGuy::RUNMACHINEGUNGUY:
		this->_vX = _nx * MACHINEGUNGUY_SPEED;
		//this->_vY = 0.0f;
		this->_width = MACHINEGUNGUY_COLLISION_WIDTH;
		this->_height = MACHINEGUNGUY_COLLISION_HEIGHT;
		this->_animationCurrent = this->_animation[0];
		break;

	case eStateMachineGunGuy::ATTACKMACHINEGUNGUY:
		_vX = 0.0f;
		//_vY = 0.0f;
		this->_width = MACHINEGUNGUY_COLLISION_WIDTH;
		this->_height = MACHINEGUNGUY_COLLISION_HEIGHT;
		this->_animationCurrent = this->_animation[1];
		this->_isAttack = true;
		this->_numberBullet = NUMBER_MACHINEGUNGUY;
		break;

	default:
		break;
	}
}

void CGameObjectMachineGunGuy::Reset()
{
	CGameObject::Reset();
	this->_positionX = this->_positionStartX;
	this->_positionY = this->_positionStartY;
	this->_nx = this->_nxStart;
	SetState(eStateMachineGunGuy::RUNMACHINEGUNGUY);
}

bool CGameObjectMachineGunGuy::IsAlive()
{
	if (_currentState == eStateMachineGunGuy::DIEMACHINEGUNGUY)
	{
		return false;
	}
	else
	{
		return true;
	}
}