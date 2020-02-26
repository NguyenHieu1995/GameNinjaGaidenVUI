#include "CDartsRed.h"

CDartsRed::CDartsRed(int id) : CGameObject(id)
{
	this->_width = 0;
	this->_height = 0;

	_animation.push_back(CAnimations::GetInstance()->Get(3000));

	this->_animationCurrent = _animation[0];

	this->_angle = 0;

	SetState(eStateDarts::HIDEDARTS);
	this->_tag = eObjectType::DARTSRED;

	_isCutEnemi = false;

	this->_vX = 0;
	this->_vY = 0;

	this->_isCatch = true;

	this->_score = 0;
}

CDartsRed::CDartsRed(int id, int x, int y) : CGameObject(id, x, y)
{
	this->_width = 0;
	this->_height = 0;

	_animation.push_back(CAnimations::GetInstance()->Get(3000));

	this->_animationCurrent = _animation[0];

	this->_angle = 0;

	SetState(eStateDarts::HIDEDARTS);
	//SetState(eStateDarts::SHOWDARTS);

	this->_tag = eObjectType::DARTSRED;

	_isCutEnemi = false;

	this->_vX = 0;
	this->_vY = 0;

	this->_isCatch = true;
	this->_score = 0;
}

CDartsRed::~CDartsRed()
{

}


void CDartsRed::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	this->_score = 0;
	_frameTime += dt;

	if (_isCutEnemi)
	{
		_timeCutEnemi += dt;

		if (_timeCutEnemi > TIME_CUT_ENEMI)
		{
			_timeCutEnemi = 0;
			_isCutEnemi = false;
		}
	}

	if (_currentState == eStateDarts::SHOWDARTS)
	{
		CGameObject::Update(dt, coObject);

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObject, coEvents);

		_positionX += _dx;
		_positionY += _dy;

		// ====
		// Test

		if (std::abs(_positionX - _posCharacterX) > 100.0f)
		{
			//SetState(eStateDarts::HIDEDARTS);
			if ((_positionX - _posCharacterX) >= 0)
			{
				_vX = -DARTS_SPEED;
			}
			else
			{
				_vX = DARTS_SPEED;
			}
			_isCatch = true;

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
				_vY = (_posCharecterY - _positionY) / (std::abs(_positionX - _posCharacterX) / DARTS_SPEED);
			}
			else
			{
				_vY = 0;
			}
		}

		//====

		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			switch (e->obj->GetTag())
			{
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

			case eObjectType::RYU:
			{
				if (_isCatch)
				{
					SetState(eStateDarts::HIDEDARTS);
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

			//if (dynamic_cast<CGameObjectCat*>(e->obj))
			//{
			//	_isCutEnemi = true;
			//	//_positionCutEnemi.x = _positionX;
			//	//_positionCutEnemi.y = _positionY;
			//	continue;
			//}

			/*if (dynamic_cast<CGameObjectRyu*>(e->obj))
			{
				if (_isCatch)
				{
					SetState(eStateDarts::HIDEDARTS);
				}
				continue;
			}*/
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void CDartsRed::Render()
{
	/*if (_isCutEnemi)
	{
		float e = _timeCutEnemi * 0.1f;
		CSprites::GetInstance()->Get(24)->Draw(_positionCutEnemi.x - e, _positionCutEnemi.y + e, 255, false, false);
		CSprites::GetInstance()->Get(25)->Draw(_positionCutEnemi.x + e, _positionCutEnemi.y + e, 255, false, false);
		CSprites::GetInstance()->Get(46)->Draw(_positionCutEnemi.x - e, _positionCutEnemi.y - e, 255, false, false);
		CSprites::GetInstance()->Get(47)->Draw(_positionCutEnemi.x + e, _positionCutEnemi.y - e, 255, false, false);
	}*/

	if (_currentState == eStateDarts::HIDEDARTS)
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

RectEx CDartsRed::GetBoundingBox()
{
	RectEx rect(
		_positionY + _height,
		_positionX,
		_positionY,
		_positionX + _width
	);
	return rect;
}

void CDartsRed::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}

void CDartsRed::SetState(int state)
{
	if (_currentState == state)
		return;

	CGameObject::SetState(state);

	switch (this->_currentState)
	{
	case eStateDarts::HIDEDARTS:
		this->_width = 0;
		this->_height = 0;
		this->_vX = 0;
		this->_vY = 0;	
		this->_isCatch = true;
		break;

	case eStateDarts::SHOWDARTS:
		this->_width = DARTSRED_COLLISION_WIDTH;
		this->_height = DARTSRED_COLLISION_HEIGHT;
		this->_vX = float(_nx * DARTS_SPEED);
		this->_vY = 0.0f;
		this->_isCatch = false;
		break;

	default:
		break;
	}
}

void CDartsRed::SetPositionCharacter(float x, float y)
{
	this->_posCharacterX = x;
	this->_posCharecterY = y;
}