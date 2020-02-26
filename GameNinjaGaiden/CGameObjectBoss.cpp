#include "CGameObjectBoss.h"

CGameObjectBoss::CGameObjectBoss(int id) : CGameObject(id)
{
	this->_width = BOSS_COLLISION_WIDTH;
	this->_height = BOSS_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(2000));
	_animation.push_back(CAnimations::GetInstance()->Get(2001));

	this->_animationCurrent = _animation[0];
	this->_tag = eObjectType::BOSS;
	this->_currentState = eStateBoss::STANDBOSS;

	_nx = 1;
	_vX = _nx * BOSS_SPEED;
	_vY = BOSS_JUMP;

	_timeDelay = 0;

	_numberJump = 0;

	_health = ENEMI_HEALTH;

	_animationExplode = CAnimations::GetInstance()->Get(5000);
	_currentFrameExplode = 0;
	_frameTimeExplode = 0;
}

CGameObjectBoss::CGameObjectBoss(int id, int x, int y, bool direction) : CGameObject(id, x, y)
{
	this->_width = BOSS_COLLISION_WIDTH;
	this->_height = BOSS_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(2000));
	_animation.push_back(CAnimations::GetInstance()->Get(2001));

	this->_animationCurrent = _animation[0];

	//this->_vX = BANSHEE_SPEED;

	if (direction)
	{
		_nx = 1;
		this->_vX = BOSS_SPEED;
	}
	else
	{
		_nx = -1;
		this->_vX = -BOSS_SPEED;
	}
	_vY = BOSS_JUMP;

	//this->_currentState = eStateBoss::STANDBOSS;
	SetState(eStateBoss::JUMPBOSS);

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::BOSS;

	_timeDelay = 0;

	_numberJump = 0;

	_health = ENEMI_HEALTH;

	_animationExplode = CAnimations::GetInstance()->Get(5000);
	_currentFrameExplode = 0;
	_frameTimeExplode = 0;

	_timeDie = 4000;
}

CGameObjectBoss::~CGameObjectBoss()
{
}

void CGameObjectBoss::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	if (this->_health == 0)
	{
		SetState(eStateBoss::DIEBOSS);
		_timeDie -= dt;
	}

	if (_currentState == eStateBoss::DIEBOSS)
	{
		//Reset();
		if (_currentState == eStateBoss::DIEBOSS)
		{
			_frameTimeExplode += dt;
		}
		return;
	}

	_vY += GRAVITY * dt;

	_frameTime += dt;	

	CGameObject::Update(dt, coObject);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPCGAMEOBJECT> listMapObject;
	listMapObject.clear();

	for (UINT i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i)->GetTag() == eObjectType::GROUND ||
			coObject->at(i)->GetTag() == eObjectType::WALL)
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

		//if (((_positionStartX - _positionX) >= JUMP_DISTANCE_BOSS) || ((_positionStartX - _positionX) <= 0))d
		{
			_timeDelay += dt;

			if (_timeDelay >= TIME_DELAY_JUMP_BOSS)
			{
				if (_nx >= 0)
				{
					_nx = -1;
				}
				else
				{
					_nx = 1;
				}

				_vY = BOSS_JUMP;

				_timeDelay = 0;

				SetState(eStateBoss::JUMPBOSS);

				_numberJump++;
				if (_numberJump >= 3)
				{
					_numberJump = 0;

					_idBullet += 4;

					if (_idBullet > 100)
					{
						_idBullet = 0;
					}

					if (_nx > 0)
					{
						CBulletBoss* bulletBoss1 = new CBulletBoss(_id * 10000 + _idBullet + 0, _positionX + _width, _positionY + (_height * 0.25f), true);
						CGameObjects::GetInstance()->AddObject(bulletBoss1);

						CBulletBoss* bulletBoss2 = new CBulletBoss(_id * 10000 + _idBullet + 1, _positionX + _width, _positionY + (_height * 0.5f), true);
						CGameObjects::GetInstance()->AddObject(bulletBoss2);

						CBulletBoss* bulletBoss3 = new CBulletBoss(_id * 10000 + _idBullet + 2, _positionX + _width, _positionY + (_height * 0.75f), true);
						CGameObjects::GetInstance()->AddObject(bulletBoss3);
					}
					else
					{
						CBulletBoss* bulletBoss1 = new CBulletBoss(_id * 10000 + _idBullet + 0, _positionX + _width, _positionY + (_height * 0.25f), false);
						CGameObjects::GetInstance()->AddObject(bulletBoss1);

						CBulletBoss* bulletBoss2 = new CBulletBoss(_id * 10000 + _idBullet + 1, _positionX + _width, _positionY + (_height * 0.5f), false);
						CGameObjects::GetInstance()->AddObject(bulletBoss2);

						CBulletBoss* bulletBoss3 = new CBulletBoss(_id * 10000 + _idBullet + 2, _positionX + _width, _positionY + (_height * 0.75f), false);
						CGameObjects::GetInstance()->AddObject(bulletBoss3);
					}
				}
			}
			else
			{
				_vX = 0;
				nx = 1;

				SetState(eStateBoss::STANDBOSS);
			}

			if (nx != 0)
			{
				_vX = 0;
			}
			else
			{
				_vX = _nx * BOSS_SPEED;
			}

			if (ny <= 0) _vY = 0;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	vector<LPCGAMEOBJECT> listObjectCollision;
	listObjectCollision.clear();
	for (UINT i = 0; i < coObject->size(); i++)
	{

		if (coObject->at(i)->GetTag() == eObjectType::SWORD ||
			coObject->at(i)->GetTag() == eObjectType::DARTSRED ||
			coObject->at(i)->GetTag() == eObjectType::DARTSSMALL ||
			coObject->at(i)->GetTag() == eObjectType::FIREBULLET)
		{
			listObjectCollision.push_back(coObject->at(i));
		}
	}

	vector<LPCOLLISIONEVENT> coEventsObjectCollision;
	vector<LPCOLLISIONEVENT> coEventsResultObjectCollision;

	coEventsObjectCollision.clear();

	CalcPotentialCollisions(&listObjectCollision, coEventsObjectCollision);
	listObjectCollision.clear();

	if (coEventsObjectCollision.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEventsObjectCollision, coEventsResultObjectCollision, min_tx, min_ty, nx, ny);

		//this->_isBeingAttacked = false;

		for (int i = 0; i < coEventsResultObjectCollision.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResultObjectCollision[i];

			switch (e->obj->GetTag())
			{
			case eObjectType::SWORD:
			{
				_health -= 1;
				break;
			}

			case eObjectType::DARTSRED:
			{
				_health -= 1;
				break;
			}

			case eObjectType::DARTSSMALL:
			{
				_health -= 1;
				break;
			}

			case eObjectType::FIREBULLET:
			{
				_health -= 1;
				break;
			}

			default:
				break;
			}
		}
	}

	if (_health < 0)
		_health = 0;
}

void CGameObjectBoss::Render()
{
	bool flip;

	if (_nx >= 0)
		flip = false;
	else
		flip = true;

	if (_timeDie <= 0)
	{
		//this->_animationCurrent = NULL;
		CGameSound::GetInstance()->stopSound("bossdie");
		_width = 0;
		_height = 0;
		return;
	}

	if (_currentState == eStateBoss::DIEBOSS && _animationCurrent != NULL)
	{
		CGameSound::GetInstance()->playSound("bossdie", true, 1);
		if (_animationExplode != NULL)
		{
			if ((_currentFrameExplode == -1) || (_currentFrameExplode > (_animationExplode->GetTotalFrame() - 1)))
			{
				_currentFrameExplode = 0;
				_frameTimeExplode = 0.0f;
			}
			else
			{
				if (_frameTimeExplode > _animationExplode->GetFrameTime(_currentFrameExplode))
				{
					_frameTimeExplode = 0.0f;
					if (_animationExplode->IsFinishFrame(_currentFrameExplode))
					{
						_currentFrameExplode = 0;
					}
					else
					{
						_currentFrameExplode++;
					}
				}
			}
			_animationExplode->Render(this->_positionX + _width / 2 - 32, this->_positionY + _height / 2 - 32, this->_currentFrameExplode, 255);
			_animationExplode->Render(this->_positionX + _width / 2 - 32, this->_positionY + _height / 2 - 0, this->_currentFrameExplode, 255);
			_animationExplode->Render(this->_positionX + _width / 2 - 0, this->_positionY + _height / 2 - 32, this->_currentFrameExplode, 255);
			_animationExplode->Render(this->_positionX + _width / 2 - 0, this->_positionY + _height / 2 - 0, this->_currentFrameExplode, 255);
		}
	}

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
					/*if (_currentState == eStateBoss::ATTACKBOSS)
					{
						SetState(eStateBanshee::RUNBANSHEE);
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

RectEx CGameObjectBoss::GetBoundingBox()
{
	RectEx rect(
		_positionY + this->_height,
		_positionX,
		_positionY,
		_positionX + this->_width
	);

	return rect;
}

void CGameObjectBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + this->_width;
	top = bottom + this->_height;
}

void CGameObjectBoss::SetState(int state)
{
	CGameObject::SetState(state);

	switch (_currentState)
	{
	case eStateBoss::STANDBOSS:
		this->_width = BOSS_COLLISION_WIDTH;
		this->_height = BOSS_COLLISION_HEIGHT;
		this->_animationCurrent = _animation[0];
		break;

	case eStateBoss::ATTACKBOSS:
		this->_width = BOSS_COLLISION_WIDTH;
		this->_height = BOSS_COLLISION_HEIGHT;
		this->_animationCurrent = _animation[0];
		break;

	case eStateBoss::JUMPBOSS:
		this->_width = BOSS_COLLISION_WIDTH;
		this->_height = BOSS_COLLISION_HEIGHT;
		this->_animationCurrent = _animation[1];
		break;

	case eStateBoss::DIEBOSS:
		this->_width = BOSS_COLLISION_WIDTH;
		this->_height = BOSS_COLLISION_HEIGHT;
		this->_animationCurrent = _animation[0];
		break;

	default:
		break;
	}
}

void CGameObjectBoss::Reset()
{
	this->_positionX = this->_positionStartX;
	this->_positionY = this->_positionStartY;
	this->_nx = this->_nxStart;
	SetState(eStateBoss::STANDBOSS);
	_timeDelay = 0;
	_health = ENEMI_HEALTH;
}




//||
//coObject->at(i)->GetTag() == eObjectType::SWORD ||
//coObject->at(i)->GetTag() == eObjectType::DARTSRED ||
//coObject->at(i)->GetTag() == eObjectType::DARTSSMALL
//
//
//if (nx != 0)
//{
//	_vX = 0;
//}
//else
//{
//	_vX = _nx * BOSS_SPEED;
//}
//
//if (ny <= 0) _vY = 0;
//
//
//for (int i = 0; i < coEventsResult.size(); i++)
//{
//	LPCOLLISIONEVENT e = coEventsResult[i];
//
//	if (dynamic_cast<CSword*>(e->obj))
//	{
//		//_isCutEnemi = true;
//		//_timeCutEnemi = 0;
//		//this->_positionCutEnemi.x = _positionX + _width / 2.0f;
//		//this->_positionCutEnemi.y = _positionY + _height / 2.0f;
//		//SetState(eStateCat::DIE);
//
//		_health--;
//
//		continue;
//	}
//
//	if (dynamic_cast<CDartsRed*>(e->obj))
//	{
//		//_isCutEnemi = true;
//		//_timeCutEnemi = 0;
//		//this->_positionCutEnemi.x = _positionX + _width / 2.0f;
//		//this->_positionCutEnemi.y = _positionY + _height / 2.0f;
//		//SetState(eStateCat::DIE);
//		continue;
//	}
//
//	if (dynamic_cast<CGameObjectWall*>(e->obj))
//	{
//		CGameObjectWall* wall = dynamic_cast<CGameObjectWall*>(e->obj);
//
//		if ((_nx < 0) && (_positionX <= wall->GetPosition().x))
//		{
//			_nx = 1.0f;
//		}
//		else
//		{
//			if ((_nx >= 0) && (_positionX + _width >= (wall->GetPosition().x + wall->GetWidth())))
//			{
//				_nx = -1.0f;
//			}
//		}
//	}
//
//	if (dynamic_cast<CGameObjectGround*>(e->obj))
//	{
//		CGameObjectGround* wall = dynamic_cast<CGameObjectGround*>(e->obj);
//
//		if ((_nx < 0) && (_positionX <= wall->GetPosition().x))
//		{
//			_nx = 1.0f;
//		}
//		else
//		{
//			if ((_nx >= 0) && (_positionX + _width >= (wall->GetPosition().x + wall->GetWidth())))
//			{
//				_nx = -1.0f;
//			}
//		}
//	}
//}