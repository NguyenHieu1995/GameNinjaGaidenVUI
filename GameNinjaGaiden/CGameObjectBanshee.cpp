#include "CGameObjectBanshee.h"
#include "CGameObjects.h"

CGameObjectBanshee::CGameObjectBanshee(int id) : CGameObject(id)
{
	this->_width = BANSHEE_COLLISION_WIDTH;
	this->_height = BANSHEE_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(104));
	_animation.push_back(CAnimations::GetInstance()->Get(105));

	this->_animationCurrent = _animation[0];

	this->_vX = BANSHEE_SPEED;

	this->_currentState = eStateBanshee::RUNBANSHEE;

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::BANSHEE;

	_idKnife = 0;
	_isAttack = false;
	_timeAttack = 0;
	//this->_isReset = true;
}

CGameObjectBanshee::CGameObjectBanshee(int id, int x, int y, bool direction) : CGameObject(id, x, y)
{
	this->_width = BANSHEE_COLLISION_WIDTH;
	this->_height = BANSHEE_COLLISION_HEIGHT;
	_animation.push_back(CAnimations::GetInstance()->Get(104));
	_animation.push_back(CAnimations::GetInstance()->Get(105));

	this->_animationCurrent = _animation[0];

	if (direction)
	{
		_nx = 1;
		this->_vX = BANSHEE_SPEED;
	}
	else
	{
		_nx = -1;
		this->_vX = -BANSHEE_SPEED;
	}

	this->_currentState = eStateBanshee::RUNBANSHEE;

	this->_positionCutEnemi.x = 0;
	this->_positionCutEnemi.y = 0;

	this->_tag = eObjectType::BANSHEE;

	_timeAttack = 0;
	_idKnife = 0;
	_isAttack = false;
	//this->_isReset = true;
}

CGameObjectBanshee::~CGameObjectBanshee()
{

}

void CGameObjectBanshee::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	if (_isFreeze)
	{
		if (_positionX == _positionStartX)
		{
			SetState(eStateBanshee::DIEBANSHEE);
		}
		//return;
	}

	//this->_isReset = false;
	/*if (!_isWeapon)
	{
		(*coObject).push_back(_weapon);
		_isWeapon = true;
	}*/
	//if (_weapon->GetState() == eStateKnifeBanshee::HIDEKNIFEBANSHEE)
	//{
	//	_weapon->SetState(eStateKnifeBanshee::SHOWKNIFEBANSHEE);
	//	if (_nx >= 0)
	//	{
	//		_weapon->SetPostion(_positionX + _width * 0.5f, _positionY + _height);
	//	}
	//	else
	//	{
	//		_weapon->SetPostion(_positionX + _width * 0.5f , _positionY + _height);
	//	}
	//	//_weapon->SetVx(KNIFEBANSHEE_SPEED);
	//	//_weapon->SetVy(KNIFEBANSHEE_JUMP);
	//	//_weapon->SetVx(0.0f);
	//	_weapon->SetVy(0.2f);
	//	_weapon->SetVx(_nx * 0.02f);
	//}

	if ((_positionX < CCamera::GetInstance()->GetBound().left - SCREEN_WIDTH / 2) ||
		(_positionX > CCamera::GetInstance()->GetBound().right + SCREEN_WIDTH / 2))
	{
		SetState(eStateBanshee::DIEBANSHEE);
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

	if (_currentState == eStateBanshee::DIEBANSHEE)
	{
		return;
	}

	_timeAttack += dt;

	/*CKnifeBanshee* knifebanshee = nullptr;*/

	if (_timeAttack > 2000)
	{
		_idKnife++;
		if (_idKnife > 9)
		{
			_idKnife = 0;
		}
		CKnifeBanshee* knifebanshee = new CKnifeBanshee(_id * 100 + _idKnife, _positionX + _width / 2, _positionStartY + _height);
		//(*coObject).push_back(knifebanshee);
		CGameObjects::GetInstance()->AddObject(knifebanshee);
		_timeAttack = 0;
		knifebanshee = nullptr;

		_isAttack = true;
		SetState(eStateBanshee::ATTACKBANSHEE);
	}

	if (!_isFreeze)
	{
		this->_vX = _nx * BANSHEE_SPEED;

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
		_vX = _nx * BANSHEE_SPEED;

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
				SetState(eStateBanshee::DIEBANSHEE);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CDartsRed*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateBanshee::DIEBANSHEE);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CDartsSmall*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateBanshee::DIEBANSHEE);
				CGameSound::GetInstance()->playSound("cutenemi", false, 1);
				continue;
			}

			if (dynamic_cast<CFirebullet*>(e->obj))
			{
				_isCutEnemi = true;
				_timeCutEnemi = 0;
				this->_positionCutEnemi.x = _positionX + _width / 2.0f;
				this->_positionCutEnemi.y = _positionY + _height / 2.0f;
				SetState(eStateBanshee::DIEBANSHEE);
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
	//UpdateAnimation(dt);
}

RectEx CGameObjectBanshee::GetBoundingBox()
{
	RectEx rect(
		_positionY + this->_height,
		_positionX,
		_positionY,
		_positionX + this->_width
	);

	return rect;
}

void CGameObjectBanshee::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}

void CGameObjectBanshee::Render()
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
					if (_currentState == eStateBanshee::ATTACKBANSHEE)
					{
						SetState(eStateBanshee::RUNBANSHEE);
						_isAttack = false;
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

void CGameObjectBanshee::SetState(int state)
{
	CGameObject::SetState(state);

	switch (_currentState)
	{
	case eStateBanshee::DIEBANSHEE:
		_vX = 0;
		_vY = 0;
		this->_width = 0;
		this->_height = 0;
		//this->_isAlive = false;
		//this->_positionX = this->_positionStartX;
		//this->_positionY = this->_positionStartY;
		this->_nx = this->_nxStart;
		this->_animationCurrent = NULL;
		break;

	case eStateBanshee::RUNBANSHEE:
		_vX = BANSHEE_SPEED;
		_vY = 0;
		this->_width = BANSHEE_COLLISION_WIDTH;
		this->_height = BANSHEE_COLLISION_HEIGHT;
		this->_animationCurrent = this->_animation[0];
		break;

	case eStateBanshee::ATTACKBANSHEE:
		_vX = BANSHEE_SPEED;
		_vY = 0;
		this->_width = BANSHEE_COLLISION_WIDTH;
		this->_height = BANSHEE_COLLISION_HEIGHT;
		this->_animationCurrent = this->_animation[1];
		break;

	default:
		break;
	}
}

void CGameObjectBanshee::Reset()
{
	CGameObject::Reset();
	this->_positionX = this->_positionStartX;
	this->_positionY = this->_positionStartY;
	this->_nx = this->_nxStart;
	SetState(eStateBanshee::RUNBANSHEE);
	//this->_isReset = true;
}

bool CGameObjectBanshee::IsAlive()
{
	if (_currentState == eStateBanshee::DIEBANSHEE)
	{
		return false;
	}
	else
	{
		return true;
	}
}