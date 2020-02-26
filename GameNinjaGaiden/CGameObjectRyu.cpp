#include "CGameObjectRyu.h"
#include "CGameSound.h"

CGameObjectRyu::CGameObjectRyu(int id) : CGameObject(id)
{
	this->_width = 27;
	this->_height = 32;

	_animation.push_back(CAnimations::GetInstance()->Get(0));
	_animation.push_back(CAnimations::GetInstance()->Get(1));
	_animation.push_back(CAnimations::GetInstance()->Get(2));
	_animation.push_back(CAnimations::GetInstance()->Get(3));
	_animation.push_back(CAnimations::GetInstance()->Get(4));
	_animation.push_back(CAnimations::GetInstance()->Get(5));
	_animation.push_back(CAnimations::GetInstance()->Get(6));
	_animation.push_back(CAnimations::GetInstance()->Get(7));
	_animation.push_back(CAnimations::GetInstance()->Get(8));
	_animation.push_back(CAnimations::GetInstance()->Get(9));
	_animation.push_back(CAnimations::GetInstance()->Get(10));

	this->_animationCurrent = _animation[0];
	//this->_currentState = eStateRyu::STAND_STATE;
	this->SetState(eStateRyu::STAND_STATE);

	this->_tag = eObjectType::RYU;

	this->_untouchable_start = 0;
	this->_untouchable = false;

	this->_isAttackSword = false;
	this->_timeCutEnemi = 0;
	this->_isCutEnemi = false;

	this->_isBeingAttacked = false;
	this->_isAttackDartsSmall = false;
	this->_isAttackDarts = false;

	this->_action = eActionObject::STAND;

	this->_untouchable = true;

	this->_idWeapon = eTypeWeaponRyu::NONEWEAPON;
	this->_health = RYU_HEALTH;
	this->_numberRevival = 2;
	this->_bonus = 0;
	this->_spiritualStrength = 0;

	this->_idDart = 0;

	_TimeFreeze = 0;

	_isResetTime = false;
}

CGameObjectRyu::CGameObjectRyu(int id, int x, int y) : CGameObject(id, x, y)
{
	this->_width = 27;
	this->_height = 32;

	_animation.push_back(CAnimations::GetInstance()->Get(0));
	_animation.push_back(CAnimations::GetInstance()->Get(1));
	_animation.push_back(CAnimations::GetInstance()->Get(2));
	_animation.push_back(CAnimations::GetInstance()->Get(3));
	_animation.push_back(CAnimations::GetInstance()->Get(4));
	_animation.push_back(CAnimations::GetInstance()->Get(5));
	_animation.push_back(CAnimations::GetInstance()->Get(6));
	_animation.push_back(CAnimations::GetInstance()->Get(7));
	_animation.push_back(CAnimations::GetInstance()->Get(8));
	_animation.push_back(CAnimations::GetInstance()->Get(9));
	_animation.push_back(CAnimations::GetInstance()->Get(10));

	this->_animationCurrent = _animation[0];
	//this->_currentState = eStateRyu::STAND_STATE;
	this->SetState(eStateRyu::STAND_STATE);

	this->_tag = eObjectType::RYU;

	this->_untouchable_start = 0;
	this->_untouchable = false;

	this->_isAttackSword = false;

	//_positionCutEnemi.x = 50;
	//_positionCutEnemi.y = 50;

	this->_timeCutEnemi = 0;
	this->_isCutEnemi = false;

	this->_isBeingAttacked = false;
	this->_isAttackDartsSmall = false;
	this->_isAttackDarts = false;

	this->_action = eActionObject::STAND;

	this->_untouchable = true;

	this->_idWeapon = eTypeWeaponRyu::NONEWEAPON;
	//_idWeapon = eTypeWeaponRyu::FIREWEAPON;
	this->_health = RYU_HEALTH;
	this->_numberRevival = 2;
	this->_bonus = 0;
	this->_spiritualStrength = 0;

	this->_idDart = 0;
	this->_TimeFreeze = 0;

	_isResetTime = false;
}


CGameObjectRyu::~CGameObjectRyu()
{
}


void CGameObjectRyu::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	if (_positionY < 0)
	{
		Reset();
		_isResetTime = true;
		return;
	}
	else
	{
		_isResetTime = false;
	}

	if (_TimeFreeze > 0)
	{
		_TimeFreeze -= dt;
		if (_TimeFreeze < 0)
		{
			_TimeFreeze = 0;
		}
	}


	this->_bonus = 0;

	if (_positionY < 0)
		_health = 0;

	if (_health <= 0)
	{
		Reset();

		return;
	}

	_frameTime += dt;

	if (_action == eActionObject::CLIMB)
	{
		_vY = 0.0f;
	}
	else
	{
		_vY += GRAVITY * dt;

		if (_vX > 0)
		{
			_vX += -FRICTION;

			if (_vX < 0)
			{
				_vX = 0;
			}
		}
		else
		{
			if (_vX < 0)
			{
				_vX += FRICTION;

				if (_vX > 0)
				{
					_vX = 0;
				}
			}
		}
	}

	CGameObject::Update(dt, coObject);

	for (int i = 0; i < coObject->size(); i++)
	{
		if (dynamic_cast<CSword*>(coObject->at(i)))
		{
			CSword* sword = dynamic_cast<CSword*>(coObject->at(i));
			if (_isAttackSword &&
				((GetState() == eStateRyu::ATTACKING_SWORD_STATE) || (GetState() == eStateRyu::ATTACKING_SITTING_STATE)) &&
				(sword->GetState() == eStateSword::HIDESWORD))
			{
				sword->SetState(eStateSword::SHOWSWORD);
				//if (CGameSound::GetInstance()->playSound("a)
				//CGameSound::GetInstance()->playSound("attack", false, 1);
			}
			else
			{
				/*if (sword->GetState() == eStateSword::SHOWSWORD)
				{*/
				sword->SetState(eStateSword::HIDESWORD);
				//CGameSound::GetInstance()->stopSound("attack");
				//}
			}

			if (sword->GetState() == eStateSword::SHOWSWORD)
			{
				sword->SetDirection(_nx);

				if (_nx < 0)
				{
					sword->SetPostion(_positionX - sword->GetWidth(), _positionY + _height * 0.5f);
				}
				else
				{
					sword->SetPostion(_positionX + _width, _positionY + _height * 0.5f);
				}
			}

			continue;
		}

		if (dynamic_cast<CDartsRed*>(coObject->at(i)))
		{
			CDartsRed* darts = dynamic_cast<CDartsRed*>(coObject->at(i));

			/*if (_isAttackDarts)
			{
				darts->SetDirection(_nx);
				if (darts->GetState() == eStateDarts::HIDEDARTS)
				{
					darts->SetState(eStateDarts::SHOWDARTS);
					darts->SetDirection(_nx);

					if (_nx < 0)
					{
						darts->SetPostion(_positionX - darts->GetWidth(), _positionY + _height * 0.5f);
					}
					else
					{
						darts->SetPostion(_positionX + _width, _positionY + _height * 0.5f);
					}
				}
				_isAttackDarts = false;
			}

			if (darts->GetState() == eStateDarts::SHOWDARTS)
			{
				darts->SetPositionCharacter(_positionX + _width / 2.0f, _positionY + _height / 2.0f);
			}*/

			continue;
		}

		if (dynamic_cast<CGameObjectBirdBrown*>(coObject->at(i)))
		{
			CGameObjectBirdBrown* birdbrown = dynamic_cast<CGameObjectBirdBrown*>(coObject->at(i));

			if (birdbrown->GetState() == eStateBirdBrown::FLYBIRDBROWN)
			{
				birdbrown->SetPositionCharacter(_positionX + _width / 2.0f, _positionY + _height / 2.0f);
			}

			continue;
		}
	}

	if (_isAttackDarts && (_idWeapon == eTypeWeaponRyu::DARTSSMALLWEAPON))
	{
		_idDart += 1;
		if (_idDart > 1000)
			_idDart = 0;

		CDartsSmall* dartSmall;

		if (_nx >= 0)
		{
			dartSmall = new CDartsSmall(_id * 10000 + _idDart, _positionX + _width, _positionY + (_height * 0.5f), true);
			//dartSmall->SetDirection(1);
		}
		else
		{
			dartSmall = new CDartsSmall(_id * 10000 + _idDart, _positionX, _positionY + (_height * 0.5f), false);
			//dartSmall->SetDirection(-1);
		}

		CGameObjects::GetInstance()->AddObject(dartSmall);
		_isAttackDarts = false;
	}

	if (_isAttackDarts && (_idWeapon == eTypeWeaponRyu::FIREWEAPON))
	{
		_idDart += 4;
		if (_idDart > 1000)
			_idDart = 1;

		//CFirebullet* dartSmall;

		if (_nx >= 0)
		{
			//dartSmall = new CFirebullet(_id * 11000 + _idDart, _positionX + _width, _positionY + (_height * 0.5f), true);
			//dartSmall->SetDirection(1);

			CFirebullet* firebullet1 = new CFirebullet(_id * 10000 + _idDart + 0, _positionX + _width, _positionY + (_height * 0.5f), 0.15, 0.03, true);
			CGameObjects::GetInstance()->AddObject(firebullet1);

			CFirebullet* firebullet2 = new CFirebullet(_id * 10000 + _idDart + 1, _positionX + _width, _positionY + (_height * 0.5f), 0.15, 0.06, true);
			CGameObjects::GetInstance()->AddObject(firebullet2);

			CFirebullet* firebullet3 = new CFirebullet(_id * 10000 + _idDart + 2, _positionX + _width, _positionY + (_height * 0.5f), 0.15, 0.09, true);
			CGameObjects::GetInstance()->AddObject(firebullet3);
		}
		else
		{
			//dartSmall = new CFirebullet(_id * 11000 + _idDart, _positionX, _positionY + (_height * 0.5f), false);
			//dartSmall->SetDirection(-1);

			CFirebullet* firebullet1 = new CFirebullet(_id * 10000 + _idDart + 0, _positionX, _positionY + (_height * 0.5f), 0.15, 0.03, false);
			CGameObjects::GetInstance()->AddObject(firebullet1);

			CFirebullet* firebullet2 = new CFirebullet(_id * 10000 + _idDart + 1, _positionX, _positionY + (_height * 0.5f), 0.15, 0.06, false);
			CGameObjects::GetInstance()->AddObject(firebullet2);

			CFirebullet* firebullet3 = new CFirebullet(_id * 10000 + _idDart + 2, _positionX, _positionY + (_height * 0.5f), 0.15, 0.09, false);
			CGameObjects::GetInstance()->AddObject(firebullet3);
		}

		//CGameObjects::GetInstance()->AddObject(dartSmall);
		_isAttackDarts = false;
	}

	vector<LPCGAMEOBJECT> listMapObject;
	listMapObject.clear();

	/*for (UINT i = 0; i < coObject->size(); i++)
	{
		if (_untouchable)
		{
			if (coObject->at(i)->GetTag() == eObjectType::WALL ||
				coObject->at(i)->GetTag() == eObjectType::GROUND)
			{
				listMapObject.push_back(coObject->at(i));
			}
		}
		else
		{
			if (coObject->at(i)->GetTag() != eObjectType::SWORD &&
				coObject->at(i)->GetTag() != eObjectType::DARTSRED)
			{
				listMapObject.push_back(coObject->at(i));
			}
		}
	}*/

	if (_isBeingAttacked && _vY <= 0)
	{
		_untouchable = true;
	}

	if (_untouchable)
	{
		_untouchable_start += dt;
		if (_untouchable_start > RYU_UNTOUCHABLE_TIME)
		{
			this->_untouchable = false;
			_untouchable_start = 0;
		}
	}

	for (UINT i = 0; i < coObject->size(); i++)
	{
		if (coObject->at(i)->GetTag() == eObjectType::WALL ||
			coObject->at(i)->GetTag() == eObjectType::GROUND ||
			coObject->at(i)->GetTag() == eObjectType::WATER)
		{
			listMapObject.push_back(coObject->at(i));
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
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
		_positionX += (int)(min_tx * _dx + nx * 0.4f);
		//_positionX += _dx;

		if (ny > 0)
		{
			_positionY += (int)(min_ty * _dy + ny * 0.4f);
		}
		else
		{
			_positionY += _dy;
		}

		//if (nx != 0) _vX = 0;
		if (ny > 0) _vY = 0;

		this->_isBeingAttacked = false;

		for (int i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			switch (e->obj->GetTag())
			{
			case eObjectType::GROUND:
			{
				if ((_isAttackSword != false) && (e->ny > 0))
				{
					SetState(eStateRyu::STAND_STATE);
				}
				break;
			}

			case eObjectType::WALL:
			{
				if ((_nx < 0 && e->nx > 0) || (_nx > 0 && e->nx < 0))
				{
					SetState(eStateRyu::CLIMGING_TO_WALL_STATE);
					this->_vX = 0.0f;
					this->_vY = 0.0f;
					this->_action = eActionObject::CLIMB;
				}
				break;
			}

			case eObjectType::WATER:
				break;

			default:
				break;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (!_untouchable)
	{
		vector<LPCGAMEOBJECT> listObjectCollision;
		listObjectCollision.clear();

		for (UINT i = 0; i < coObject->size(); i++)
		{

			if (coObject->at(i)->GetTag() != eObjectType::WALL &&
				coObject->at(i)->GetTag() != eObjectType::GROUND &&
				coObject->at(i)->GetTag() != eObjectType::SWORD &&
				coObject->at(i)->GetTag() != eObjectType::DARTSRED &&
				coObject->at(i)->GetTag() != eObjectType::WATER)
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
				case eObjectType::BANSHEE:
				{
					this->_isBeingAttacked = true;
					//if (e->nx != 0) _nx = int(-(e->nx));
					/*if (e->nx > 0)
						_nx = -1.0f;
					else
						_nx = 1.0f;*/

					this->_health -= 1;
					break;
				}

				case eObjectType::BATBROWN:
				{
					break;
				}

				case eObjectType::BIRDBROWN:
				{
					this->_isBeingAttacked = true;
					//if (e->nx != 0) _nx = int(-(e->nx));
					this->_health -= 2;
					break;
				}

				case eObjectType::BONUSBLUE:
				{
					if (dynamic_cast<CBonusBlue*>(e->obj))
					{
						CBonusBlue* bonusblue = dynamic_cast<CBonusBlue*>(e->obj);
						if (bonusblue->GetState() == eStateItem::SHOWITEM)
						{
							bonusblue->SetState(eStateItem::DISAPPEARITEM);
							_bonus = 500;
						}
					}
					CGameSound::GetInstance()->playSound("getitem", false, 1);
					break;
				}

				case eObjectType::BONUSRED:
				{
					if (dynamic_cast<CBonusRed*>(e->obj))
					{
						CBonusRed* bonusred = dynamic_cast<CBonusRed*>(e->obj);
						if (bonusred->GetState() == eStateItem::SHOWITEM)
						{
							bonusred->SetState(eStateItem::DISAPPEARITEM);
							_bonus = 1000;
						}
					}
					CGameSound::GetInstance()->playSound("getitem", false, 1);
					break;
				}

				case eObjectType::BOSS:
				{
					this->_isBeingAttacked = true;
					//if (e->nx != 0) _nx = int(-(e->nx));
					this->_health -= 1;
					break;
				}

				case eObjectType::BULLETBOSS:
					this->_isBeingAttacked = true;
					//if (e->nx != 0) _nx = int(-(e->nx));
					this->_health -= 1;
					break;

				case eObjectType::BULLETMACHINEGUNGUY:
				{
					this->_isBeingAttacked = true;
					if (e->nx != 0) _nx = int(-(e->nx));
					this->_health -= 1;
					break;
				}

				case eObjectType::CAT:
				{
					this->_isBeingAttacked = true;
					//if (e->nx != 0) _nx = int((e->nx));
					this->_health -= 1;
					break;
				}

				case eObjectType::FIREWHEEL:
				{
					if (dynamic_cast<CFireWheel*>(e->obj))
					{
						CFireWheel* firewheel = dynamic_cast<CFireWheel*>(e->obj);
						if (firewheel->GetState() == eStateItem::SHOWITEM)
						{
							firewheel->SetState(eStateItem::DISAPPEARITEM);
						}
					}
					CGameSound::GetInstance()->playSound("getitem", false, 1);
					break;
				}

				case eObjectType::ITEMCONTAINER4:
					break;

				case eObjectType::KNIFEBANSHEE:
				{
					this->_isBeingAttacked = true;
					//if (e->nx != 0) _nx = int(-(e->nx));
					this->_health -= 1;
					break;
				}

				case eObjectType::MACHINEGUNGUY:
				{
					this->_isBeingAttacked = true;
					//if (e->nx != 0) _nx = int(-(e->nx));
					this->_health -= 1;
					break;
				}

				case eObjectType::RESTOREPHYSICALSTRENGTH:
				{
					if (dynamic_cast<CRestorePhysicalStrength*>(e->obj))
					{
						CRestorePhysicalStrength* restorephysicalstrength = dynamic_cast<CRestorePhysicalStrength*>(e->obj);
						if (restorephysicalstrength->GetState() == eStateItem::SHOWITEM)
						{
							restorephysicalstrength->SetState(eStateItem::DISAPPEARITEM);
							this->_health = RYU_HEALTH;
						}
					}
					CGameSound::GetInstance()->playSound("getitem", false, 1);
					break;
				}

				case eObjectType::SPIRITUALSTRENGTHBLUE:
				{
					if (dynamic_cast<CSpiritualStrengthBlue*>(e->obj))
					{
						CSpiritualStrengthBlue* spiritualStrengthBlue = dynamic_cast<CSpiritualStrengthBlue*>(e->obj);
						if (spiritualStrengthBlue->GetState() == eStateItem::SHOWITEM)
						{
							spiritualStrengthBlue->SetState(eStateItem::DISAPPEARITEM);
							_spiritualStrength += 5;
						}
					}
					CGameSound::GetInstance()->playSound("getitem", false, 1);
					break;
				}

				case eObjectType::SPIRITUALSTRENGTHRED:
				{
					if (dynamic_cast<CSpiritualStrengthRed*>(e->obj))
					{
						CSpiritualStrengthRed* spiritualStrengthRed = dynamic_cast<CSpiritualStrengthRed*>(e->obj);
						if (spiritualStrengthRed->GetState() == eStateItem::SHOWITEM)
						{
							spiritualStrengthRed->SetState(eStateItem::DISAPPEARITEM);
							_spiritualStrength += 10;
						}
					}
					CGameSound::GetInstance()->playSound("getitem", false, 1);
					break;
				}

				case eObjectType::SWORDMAN:
				{
					if (!_isBeingAttacked)
					{
						this->_isBeingAttacked = true;
						//if (e->nx != 0) _nx = int(-(e->nx));
						_health -= 1;
					}
					break;
				}

				case eObjectType::THROWINGSTAR:
				{
					if (dynamic_cast<CThrowingStart*>(e->obj))
					{
						CThrowingStart* throwingStart = dynamic_cast<CThrowingStart*>(e->obj);
						if (throwingStart->GetState() == eStateItem::SHOWITEM)
						{
							throwingStart->SetState(eStateItem::DISAPPEARITEM);
							//_idWeapon = 28;
							_idWeapon = eTypeWeaponRyu::DARTSSMALLWEAPON;
						}
					}
					CGameSound::GetInstance()->playSound("getitem", false, 1);
					break;
				}

				case eObjectType::TIMEFREEZE:
				{
					if (dynamic_cast<CTimeFreeze*>(e->obj))
					{
						CTimeFreeze* timeFreeze = dynamic_cast<CTimeFreeze*>(e->obj);
						if (timeFreeze->GetState() == eStateItem::SHOWITEM)
						{
							timeFreeze->SetState(eStateItem::DISAPPEARITEM);
							_isFreeze = true;
							_TimeFreeze = 5000;
						}
					}
					CGameSound::GetInstance()->playSound("getitem", false, 1);
					break;
				}

				case eObjectType::FIRE:
				{
					if (dynamic_cast<CFire*>(e->obj))
					{
						CFire* timeFreeze = dynamic_cast<CFire*>(e->obj);
						if (timeFreeze->GetState() == eStateItem::SHOWITEM)
						{
							timeFreeze->SetState(eStateItem::DISAPPEARITEM);
							//_idWeapon = 31;
							_idWeapon = eTypeWeaponRyu::FIREWEAPON;
						}
					}
					CGameSound::GetInstance()->playSound("getitem", false, 1);
					break;
				}

				default:
					break;
				}
			}

			if (_isBeingAttacked)
			{
				if (_currentState != eStateRyu::CLIMBING_WALL_STATE && _currentState != eStateRyu::CLIMGING_TO_WALL_STATE)
				{
					_vY = 0.4f;
					_nx = nx;
					_vX = nx * 0.25f;
					SetState(eStateRyu::BEING_ATTACKED_STATE);
				}
				CGameSound::GetInstance()->playSound("beingattack", false, 1);

				//DebugOut(L"Postion Collsion: %f\n", _positionX);
			}
		}
		for (UINT i = 0; i < coEventsObjectCollision.size(); i++) delete coEventsObjectCollision[i];
	}

	if (_TimeFreeze > 0)
	{
		unordered_map<int, LPCGAMEOBJECT> listObject = CGameObjects::GetInstance()->GetListObject();
		for (auto object = listObject.begin(); object != listObject.end(); ++object)
		{
			if (object->second->GetTag() != eObjectType::RYU)
			{
				object->second->SetFreeze(true);
			}
		}
	}
	else
	{
		if (_isFreeze)
		{
			unordered_map<int, LPCGAMEOBJECT> listObject = CGameObjects::GetInstance()->GetListObject();
			for (auto object = listObject.begin(); object != listObject.end(); ++object)
			{
				object->second->SetFreeze(false);
			}
		}
	}

	
}

RectEx CGameObjectRyu::GetBoundingBox()
{
	RectEx rect(
		_positionY + _height,
		_positionX,
		_positionY,
		_positionX + _width
	);
	return rect;
}

void CGameObjectRyu::Render()
{
	

	if (_positionX < 30)
	{
		_positionX = 30;
	}

	if (_positionX > CCamera::GetInstance()->GetMaxPostionX() - 30)
	{
		_positionX = CCamera::GetInstance()->GetMaxPostionX() - 30;
	}

	if (_positionX > CCamera::GetInstance()->GetBound().top)
	{
		CCamera::GetInstance()->GetBound().top - 50;
	}

	if (!(_currentState == eStateRyu::ATTACKING_STAND_STATE ||
		_currentState == eStateRyu::ATTACKING_STAND_DARTSSMALL_STATE ||
		_currentState == eStateRyu::ATTACKING_SWORD_STATE ||
		_currentState == eStateRyu::CLIMBING_WALL_STATE ||
		_currentState == eStateRyu::CLIMGING_TO_WALL_STATE))
	{
		if (this->_currentState == eStateRyu::SITTING_STATE)
		{

		}
		else
		{
			if (this->_currentState == eStateRyu::ATTACKING_SWORD_STATE || this->_currentState == eStateRyu::ATTACKING_STAND_STATE)
			{
				DebugOut(L"Charater attack!");
			}
			else
			{
				// Update state
				if (this->_vY != 0)
				{
					//if (_isBeingAttacked)
					//{
					//	this->SetState(eStateRyu::BEING_ATTACKED_STATE);
					//}
					//else
					//{
					//	//this->SetState(eStateRyu::JUMPING_STATE);
					//}
				}
				else
				{
					if (_action != eActionObject::CLIMB)
					{
						if (this->_vX > 0)
						{
							this->SetState(eStateRyu::RUNNING_STATE);
							//_nx = 1;
						}
						else
						{
							if (this->_vX < 0)
							{
								this->SetState(eStateRyu::RUNNING_STATE);
								//_nx = -1;
							}
							else
							{
								this->SetState(eStateRyu::STAND_STATE);
							}
						}
					}
				}
			}
		}
	}

	/*if (_isBeingAttacked)
		DebugOut(L"Test %f\n", _vX);*/

	bool flip;
	if (_nx >= 0)
	{
		flip = false;
	}
	else
	{
		flip = true;
	}

	// Update animation and render
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
					_isAttackSword = false;
					_isCutEnemi = false;
					_isAttackDartsSmall = false;
					_isAttackDarts = false;
				}
				else
				{
					_currentFrame++;
				}
			}
		}

		if (_untouchable)
		{
			_animationCurrent->Render(this->_positionX, this->_positionY, this->_currentFrame, 128, flip);
		}
		else
		{
			_animationCurrent->Render(this->_positionX, this->_positionY, this->_currentFrame, 255, flip);
		}
	}
}

void CGameObjectRyu::SetState(int state)
{
	if (_currentState == eStateRyu::BEING_ATTACKED_STATE && state != eStateRyu::BEING_ATTACKED_STATE)
	{
		_nx *= -1;
	}
	CGameObject::SetState(state);

	if (!_isAttackSword)
	{
		switch (this->_currentState)
		{
		case eStateRyu::STAND_STATE:
			this->_animationCurrent = _animation[0];
			this->_width = RYU_STAND_WIDTH;
			this->_height = RYU_STAND_HEIGHT;
			this->_isAttackSword = false;
			this->_action = eActionObject::STAND;
			break;

		case eStateRyu::ATTACKING_SWORD_STATE:
			this->_animationCurrent = _animation[1];
			this->_width = RYU_ATTACKING_SWORD_WIDTH;
			this->_height = RYU_ATTACKING_SWORD_HEIGHT;
			this->_isAttackSword = true;
			break;

		case eStateRyu::ATTACKING_STAND_STATE:
			this->_animationCurrent = _animation[2];
			this->_width = RYU_ATTACKING_STAND_WIDTH;
			this->_height = RYU_ATTACKING_STAND_HEIGHT;
			this->_isAttackSword = false;
			this->_isAttackDarts = true;
			break;

		case eStateRyu::ATTACKING_STAND_DARTSSMALL_STATE:
			this->_animationCurrent = _animation[2];
			this->_width = RYU_ATTACKING_STAND_WIDTH;
			this->_height = RYU_ATTACKING_STAND_HEIGHT;
			this->_isAttackSword = false;
			this->_isAttackDarts = false;
			_isAttackDartsSmall = true;
			break;

		case eStateRyu::CLIMGING_TO_WALL_STATE:
			this->_animationCurrent = _animation[3];
			this->_width = RYU_CLIMB_COLLISION_WIDTH;
			this->_height = RYU_CLIMB_COLLISION_HEIGHT;
			this->_isAttackSword = false;
			this->_isAttackDarts = eActionObject::CLIMB;
			break;

		case eStateRyu::CLIMBING_WALL_STATE:
			this->_animationCurrent = _animation[4];
			this->_width = RYU_CLIMB_COLLISION_WIDTH;
			this->_height = RYU_CLIMB_COLLISION_HEIGHT;
			this->_isAttackSword = false;
			this->_isAttackDarts = eActionObject::CLIMB;
			break;

		case eStateRyu::RUNNING_STATE:
			this->_animationCurrent = _animation[5];
			this->_width = RYU_RUN_WIDTH;
			this->_height = RYU_RUN_HEIGHT;
			this->_isAttackSword = false;
			this->_action = eActionObject::RUNOJBECT;
			break;

		case eStateRyu::SITTING_STATE:
			this->_animationCurrent = _animation[6];
			this->_width = 32;
			this->_height = 32;
			this->_isAttackSword = false;
			this->_action = eActionObject::SIT;
			break;

		case eStateRyu::ATTACKING_SITTING_STATE:
			this->_animationCurrent = _animation[7];
			this->_width = 32;
			this->_height = 32;
			this->_isAttackSword = true;
			break;

		case eStateRyu::JUMPING_STATE:
			this->_animationCurrent = _animation[8];
			this->_width = RYU_JUMP_COLLISION_WIDTH;
			this->_height = RYU_JUMP_COLLISION_HEIGHT;
			this->_isAttackSword = false;
			this->_action = eActionObject::JUMP;
			break;

		case eStateRyu::ATTACKING_JUMPING_STATE:
			this->_animationCurrent = _animation[9];
			this->_width = 32;
			this->_height = 32;
			this->_isAttackSword = true;
			break;

		case eStateRyu::BEING_ATTACKED_STATE:
			this->_animationCurrent = _animation[10];
			this->_width = RYU_BEING_ATTACKED_COLLISION_WIDTH;
			this->_height = RYU_BEING_ATTACKED_COLLISION_HEIGHT;
			this->_isAttackSword = false;
			break;

		default:
			break;
		}
	}
}

void CGameObjectRyu::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;

	/*if (level == MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}*/
}

void CGameObjectRyu::Reset()
{
	this->_positionX = _positionStartX;
	this->_positionY = _positionStartY;
	SetState(eStateRyu::STAND_STATE);

	this->_idWeapon = eTypeWeaponRyu::NONEWEAPON;
	this->_health = RYU_HEALTH;
	this->_numberRevival -= 1;
	//this->_bonus = 0;
	//this->_spiritualStrength = 0;

	unordered_map<int, LPCGAMEOBJECT> listObject = CGameObjects::GetInstance()->GetListObject();

	for (auto object = listObject.begin(); object != listObject.end(); ++object)
	{
		if (object->second != NULL)
		{
			if (object->second->GetTag() == eObjectType::BULLETBOSS)
			{
				object->second->SetState(eStateBulletBoss::HIDEBULLETBOSS);
			}

			if (object->second->GetTag() == eObjectType::BOSS)
			{
				object->second->Reset();
			}
		}
	}
}

int CGameObjectRyu::GetRevival()
{
	return _numberRevival;
}
//int CGameObjectRyu::GetHealth()
//{
//	return _health;
//}
int CGameObjectRyu::GetWeapon()
{
	switch (this->_idWeapon)
	{
	case eTypeWeaponRyu::NONEWEAPON:
		return 0;

	case eTypeWeaponRyu::DARTSREDWEAPON:
		return 29;

	case eTypeWeaponRyu::DARTSSMALLWEAPON:
		return 28;

	case eTypeWeaponRyu::FIREWEAPON:
		return 31;

	default:
		return 0;
	}
	//return _idWeapon;
}

int CGameObjectRyu::GetBonus()
{
	return _bonus;
}

int CGameObjectRyu::GetSpiritualStrength()
{
	return _spiritualStrength;
}

bool CGameObjectRyu::IsResetTime()
{
	return _isResetTime;
}