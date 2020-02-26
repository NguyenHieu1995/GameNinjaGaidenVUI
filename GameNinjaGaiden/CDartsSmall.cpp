#include "CDartsSmall.h"

CDartsSmall::CDartsSmall(int id) : CGameObject(id)
{
	this->_width = 0;
	this->_height = 0;

	_animation.push_back(CAnimations::GetInstance()->Get(3001));

	this->_animationCurrent = _animation[0];

	this->_angle = 0;

	SetState(eStateDartsSmall::SHOWDARTSSMALL);
	this->_tag = eObjectType::DARTSSMALL;

	_isCutEnemi = false;

	this->_vX = DARTSSMALL_SPEED;
	this->_vY = 0; 
	this->_score = 0;
}

CDartsSmall::CDartsSmall(int id, int x, int y, bool direction) : CGameObject(id, x, y)
{
	this->_width = 0;
	this->_height = 0;

	_animation.push_back(CAnimations::GetInstance()->Get(3001));

	this->_animationCurrent = _animation[0];

	this->_angle = 0;

	SetState(eStateDartsSmall::SHOWDARTSSMALL);
	this->_tag = eObjectType::DARTSSMALL;

	_isCutEnemi = false;

	//this->_vX = DARTSSMALL_SPEED;
	this->_vY = 0;

	if (direction)
	{
		_nx = 1;
		this->_vX = DARTSSMALL_SPEED;
	}
	else
	{
		_nx = -1;
		this->_vX = -DARTSSMALL_SPEED;
	}
	this->_score = 0;
}

CDartsSmall::~CDartsSmall()
{
}

void CDartsSmall::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	this->_score = 0;
	_frameTime += dt;

	/*if (_isCutEnemi)
	{
		_timeCutEnemi += dt;

		if (_timeCutEnemi > TIME_CUT_ENEMI)
		{
			_timeCutEnemi = 0;
			_isCutEnemi = false;
		}
	}*/

	if (std::abs(_positionX - _positionStartX) > 100.0f)
	{
		SetState(eStateDartsSmall::HIDEDARTSSMALL);
	}

	if (_currentState == eStateDartsSmall::SHOWDARTSSMALL)
	{
		CGameObject::Update(dt, coObject);

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObject, coEvents);

		_positionX += _dx;
		_positionY += _dy;

		float min_tx, min_ty, nx = 0, ny;

		//FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (int i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];

			switch (e->obj->GetTag())
			{
				/*case eObjectType::CAT:
				{
					if (dynamic_cast<CGameObjectCat*>(e->obj))
					{
						_isCutEnemi = true;
						_positionCutEnemi.x = _positionX;
						_positionCutEnemi.y = _positionY;
					}
					break;
				}*/

			case eObjectType::BONUSRED:
			{
				if (dynamic_cast<CBonusRed*>(e->obj))
				{
					CBonusRed* bonusred = dynamic_cast<CBonusRed*>(e->obj);
					if (bonusred->GetState() == eStateItem::HIDEITEM)
					{
						bonusred->SetState(eStateItem::SHOWITEM);
					}
				}
				break;
			}

			case eObjectType::BONUSBLUE:
			{
				if (dynamic_cast<CBonusBlue*>(e->obj))
				{
					CBonusBlue* bonusblue = dynamic_cast<CBonusBlue*>(e->obj);
					if (bonusblue->GetState() == eStateItem::HIDEITEM)
					{
						bonusblue->SetState(eStateItem::SHOWITEM);
					}
				}
				break;
			}

			case eObjectType::ITEMCONTAINER4:
			{
				if (dynamic_cast<CItemContainer4*>(e->obj))
				{
					CItemContainer4* itemContainer4 = dynamic_cast<CItemContainer4*>(e->obj);
					if (itemContainer4->GetState() == eStateItem::SHOWITEM)
					{
						itemContainer4->SetState(eStateItem::DISAPPEARITEM);
					}
				}
				break;
			}

			case eObjectType::FIREWHEEL:
			{
				if (dynamic_cast<CFireWheel*>(e->obj))
				{
					CFireWheel* fireWheel = dynamic_cast<CFireWheel*>(e->obj);
					if (fireWheel->GetState() == eStateItem::HIDEITEM)
					{
						fireWheel->SetState(eStateItem::SHOWITEM);
					}
				}
				break;
			}

			case eObjectType::RESTOREPHYSICALSTRENGTH:
			{
				if (dynamic_cast<CRestorePhysicalStrength*>(e->obj))
				{
					CRestorePhysicalStrength* restorePhysicalStrength = dynamic_cast<CRestorePhysicalStrength*>(e->obj);
					if (restorePhysicalStrength->GetState() == eStateItem::HIDEITEM)
					{
						restorePhysicalStrength->SetState(eStateItem::SHOWITEM);
					}
				}
				break;
			}

			case eObjectType::SPIRITUALSTRENGTHBLUE:
			{
				if (dynamic_cast<CSpiritualStrengthBlue*>(e->obj))
				{
					CSpiritualStrengthBlue* spiritualStrengthBlue = dynamic_cast<CSpiritualStrengthBlue*>(e->obj);
					if (spiritualStrengthBlue->GetState() == eStateItem::HIDEITEM)
					{
						spiritualStrengthBlue->SetState(eStateItem::SHOWITEM);
					}
				}
				break;
			}

			case eObjectType::SPIRITUALSTRENGTHRED:
			{
				if (dynamic_cast<CSpiritualStrengthRed*>(e->obj))
				{
					CSpiritualStrengthRed* spiritualStrengthRed = dynamic_cast<CSpiritualStrengthRed*>(e->obj);
					if (spiritualStrengthRed->GetState() == eStateItem::HIDEITEM)
					{
						spiritualStrengthRed->SetState(eStateItem::SHOWITEM);
					}
				}
				break;
			}

			case eObjectType::THROWINGSTAR:
			{
				if (dynamic_cast<CThrowingStart*>(e->obj))
				{
					CThrowingStart* throwingStart = dynamic_cast<CThrowingStart*>(e->obj);
					if (throwingStart->GetState() == eStateItem::HIDEITEM)
					{
						throwingStart->SetState(eStateItem::SHOWITEM);
					}
				}
				break;
			}

			case eObjectType::TIMEFREEZE:
			{
				if (dynamic_cast<CTimeFreeze*>(e->obj))
				{
					CTimeFreeze* timeFreeze = dynamic_cast<CTimeFreeze*>(e->obj);
					if (timeFreeze->GetState() == eStateItem::HIDEITEM)
					{
						timeFreeze->SetState(eStateItem::SHOWITEM);
					}
				}
				break;
			}

			case eObjectType::FIRE:
			{
				if (dynamic_cast<CFire*>(e->obj))
				{
					CFire* timeFreeze = dynamic_cast<CFire*>(e->obj);
					if (timeFreeze->GetState() == eStateItem::HIDEITEM)
					{
						timeFreeze->SetState(eStateItem::SHOWITEM);
					}
				}
				break;
			}

			case eObjectType::BULLETBOSS:
			{
				if (dynamic_cast<CBulletBoss*>(e->obj))
				{
					CBulletBoss* bulletBoss = dynamic_cast<CBulletBoss*>(e->obj);
					if (bulletBoss->GetState() == eStateBulletBoss::SHOWBULLETBOSS)
					{
						bulletBoss->SetState(eStateBulletBoss::HIDEBULLETBOSS);
					}
				}
				break;
			}

			case eObjectType::KNIFEBANSHEE:
			{
				if (dynamic_cast<CKnifeBanshee*>(e->obj))
				{
					CKnifeBanshee* bulletBoss = dynamic_cast<CKnifeBanshee*>(e->obj);
					if (bulletBoss->GetState() == eStateKnifeBanshee::SHOWKNIFEBANSHEE)
					{
						bulletBoss->SetState(eStateKnifeBanshee::HIDEKNIFEBANSHEE);
					}
				}
				break;
			}

			case eObjectType::BULLETMACHINEGUNGUY:
			{
				if (dynamic_cast<CBulletMachineGunGuy*>(e->obj))
				{
					CBulletMachineGunGuy* bulletBoss = dynamic_cast<CBulletMachineGunGuy*>(e->obj);
					if (bulletBoss->GetState() == eStateBulletMachineGunGuy::SHOWBULLETMACHINEGUNGUY)
					{
						bulletBoss->SetState(eStateBulletMachineGunGuy::HIDEBULLETMACHINEGUNGUY);
					}
				}
				break;
			}

			case eObjectType::BANSHEE:
			{
				this->_score += 100;
				break;
			}
			case eObjectType::BATBROWN:
			{
				this->_score += 100;
				break;
			}
			case eObjectType::BIRDBROWN:
			{
				this->_score += 100;
				break;
			}
			case eObjectType::CAT:
			{
				this->_score += 100;
				break;
			}
			case eObjectType::MACHINEGUNGUY:
			{
				this->_score += 100;
				break;
			}
			case eObjectType::SWORDMAN:
			{
				this->_score += 100;
				break;
			}

			default:
				break;
			}
		}

		/*for (int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGameObjectCat*>(e->obj))
			{
				_isCutEnemi = true;
				_positionCutEnemi.x = _positionX;
				_positionCutEnemi.y = _positionY;
				continue;
			}			
		}*/
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}		
}

void CDartsSmall::Render()
{
	/*if (_isCutEnemi)
	{
		float e = _timeCutEnemi * 0.1f;
		CSprites::GetInstance()->Get(24)->Draw(_positionCutEnemi.x - e, _positionCutEnemi.y + e, 255, false, false);
		CSprites::GetInstance()->Get(25)->Draw(_positionCutEnemi.x + e, _positionCutEnemi.y + e, 255, false, false);
		CSprites::GetInstance()->Get(46)->Draw(_positionCutEnemi.x - e, _positionCutEnemi.y - e, 255, false, false);
		CSprites::GetInstance()->Get(47)->Draw(_positionCutEnemi.x + e, _positionCutEnemi.y - e, 255, false, false);
	}*/

	if (_currentState == eStateDartsSmall::HIDEDARTSSMALL)
	{
		return;
	}

	if (_animationCurrent != NULL)
	{
		if ((_currentFrame == -1) || (_currentFrame > (_animationCurrent->GetTotalFrame() - 1)))
		{
			_currentFrame = 0;
			_frameTime = 0.0f;

			_angle += 45;

			if (_angle >= 360)
				_angle -= 360;
		}
		else
		{
			if (_frameTime > _animationCurrent->GetFrameTime(_currentFrame))
			{
				_frameTime = 0.0f;

				_angle += 45;

				if (_angle >= 360)
					_angle -= 360;

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

	_animationCurrent->Render(this->_positionX, this->_positionY, this->_currentFrame, 255, false, false, (float)_angle);
}

RectEx CDartsSmall::GetBoundingBox()
{
	RectEx rect(
		_positionY + _height,
		_positionX,
		_positionY,
		_positionX + _width
	);
	return rect;
}

void CDartsSmall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}

void CDartsSmall::SetState(int state)
{
	if (_currentState == state)
		return;

	CGameObject::SetState(state);

	switch (this->_currentState)
	{
	case eStateDartsSmall::HIDEDARTSSMALL:
		this->_width = 0;
		this->_height = 0;
		this->_vX = 0;
		this->_vY = 0;
		break;

	case eStateDartsSmall::SHOWDARTSSMALL:
		this->_width = DARTSSMALL_COLLISION_WIDTH;
		this->_height = DARTSSMALL_COLLISION_HEIGHT;
		this->_vX = _nx * DARTSSMALL_SPEED;
		this->_vY = 0;
		break;

	default:
		break;
	}
}

