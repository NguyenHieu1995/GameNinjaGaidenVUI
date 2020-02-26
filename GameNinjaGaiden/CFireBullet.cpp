#include "CFireBullet.h"

const float FIREBULLET_COLLISION_WIDTH = 40.0f;
const float FIREBULLET_COLLISION_HEIGHT = 40.0f;

const float FIREBULLET_SPEED = 0.1f;


CFirebullet::CFirebullet(int id) : CGameObject(id)
{
	_animation.push_back(CAnimations::GetInstance()->Get(3002));

	this->_animationCurrent = _animation[0];

	this->_angle = 0;

	SetState(eStateFireBullet::SHOWFIREBULLET);
	this->_tag = eObjectType::FIREBULLET;

	this->_vX = 0;
	this->_vY = 0;
	this->_score = 0;
}

CFirebullet::CFirebullet(int id, int x, int y, float vx, float vy, bool direction) : CGameObject(id, x, y)
{
	_animation.push_back(CAnimations::GetInstance()->Get(3002));

	this->_animationCurrent = _animation[0];

	this->_angle = 0;

	SetState(eStateFireBullet::SHOWFIREBULLET);
	this->_tag = eObjectType::FIREBULLET;

	if (direction)
	{
		_nx = 1;
	}
	else
	{
		_nx = -1;
	}

	_vX = _nx * vx;
	_vY = vy;

	_timeAngle = 0;
	this->_score = 0;
}

CFirebullet::~CFirebullet() {}

void CFirebullet::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	this->_score = 0;

	if (abs(_positionX - _positionStartX) > 200.0f)
	{
		SetState(eStateFireBullet::HIDEFIREBULLET);
	}

	if (_currentState == eStateFireBullet::HIDEFIREBULLET)
		return;

	_frameTime += dt;

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

	//int x1, y1, x2, y2, x3, y3;

	//_x1 = 40.0f * cos((PI / 12.0f) * (dt / 1000.0f) - (PI / 6.0f));

	//DebugOut(L"%f - %d\n", _x1, dt);
	_timeAngle += 0.3;

	if (_timeAngle >= 6)
		_timeAngle = 0;

	_x1 = 15 * cos(((60 * PI) / 180.0f) * _timeAngle + ((0 * PI) / 180.0f));
	_y1 = 15 * sin(((60 * PI) / 180.0f) * _timeAngle + ((0 * PI) / 180.0f));

	_x2 = 15 * cos(((60 * PI) / 180.0f) * _timeAngle + ((120 * PI) / 180.0f));
	_y2 = 15 * sin(((60 * PI) / 180.0f) * _timeAngle + ((120 * PI) / 180.0f));

	_x3 = 15 * cos(((60 * PI) / 180.0f) * _timeAngle + ((240 * PI) / 180.0f));
	_y3 = 15 * sin(((60 * PI) / 180.0f) * _timeAngle + ((240 * PI) / 180.0f));


	//DebugOut(L"%f, %f, %f, %f, %f, %f\n", _x1, _y1, _x2, _y2, _x3, _y3);
}

void CFirebullet::Render()
{
	if (_currentState == eStateFireBullet::HIDEFIREBULLET)
		return;

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

	_animationCurrent->Render(int(this->_positionX + _width * 0.5f - 4 + _x1), int(this->_positionY + _height * 0.5f - 6 + _y1), this->_currentFrame, 255);
	_animationCurrent->Render(int(this->_positionX + _width * 0.5f - 4 + _x2), int(this->_positionY + _height * 0.5f - 6 + _y2), this->_currentFrame, 255);
	_animationCurrent->Render(int(this->_positionX + _width * 0.5f - 4 + _x3), int(this->_positionY + _height * 0.5f - 6 + _y3), this->_currentFrame, 255);
}

RectEx CFirebullet::GetBoundingBox()
{
	RectEx rect(
		_positionY + _height,
		_positionX,
		_positionY,
		_positionX + _width
	);
	return rect;
}

void CFirebullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}

void CFirebullet::SetState(int state)
{
	if (_currentState == state)
		return;

	CGameObject::SetState(state);

	switch (this->_currentState)
	{
	case eStateFireBullet::HIDEFIREBULLET:
		this->_width = 0;
		this->_height = 0;
		//this->_vX = 0;
		//this->_vY = 0;
		break;

	case eStateFireBullet::SHOWFIREBULLET:
		this->_width = FIREBULLET_COLLISION_WIDTH;
		this->_height = FIREBULLET_COLLISION_HEIGHT;
		//this->_vX = float(_nx * FIREBULLET_SPEED);
		//this->_vY = 0.0f;
		break;

	default:
		break;
	}
}



//void CFirebullet::Reset()
//{
//	_positionX = _positionStartX;
//	_positionY = _positionStartY;
//}