#include "CKnifeBanshee.h"

CKnifeBanshee::CKnifeBanshee(int id) : CGameObject(id)
{
	this->_width = 0;
	this->_height = 0;

	_animation.push_back(CAnimations::GetInstance()->Get(4000));

	this->_animationCurrent = _animation[0];

	SetState(eStateKnifeBanshee::SHOWKNIFEBANSHEE);
	this->_tag = eObjectType::KNIFEBANSHEE;

	_isCutEnemi = false;

	this->_vX = 0;
	this->_vY = 0;

	this->_angle = 0;
}

CKnifeBanshee::CKnifeBanshee(int id, int x, int y) : CGameObject(id , x, y)
{
	this->_width = 0;
	this->_height = 0;

	_animation.push_back(CAnimations::GetInstance()->Get(4000));

	this->_animationCurrent = _animation[0];

	SetState(eStateKnifeBanshee::SHOWKNIFEBANSHEE);
	this->_tag = eObjectType::KNIFEBANSHEE;

	_isCutEnemi = false;

	this->_vX = 0;
	this->_vY = 0;

	this->_angle = 0;
}

CKnifeBanshee::~CKnifeBanshee()
{
}

void CKnifeBanshee::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	//this->_vX = _nx * KNIFEBANSHEE_SPEED;
	this->_vY += GRAVITY * dt * 0.3f;
		
	//this->_vX = 0.0002f * dt;

	//this->_vX = 0;

	_frameTime += dt;

	if (_currentState == eStateKnifeBanshee::SHOWKNIFEBANSHEE)
	{
		CGameObject::Update(dt, coObject);
		
		_positionX += _dx;
		_positionY += _dy;		
	}

	if (_positionY <= 0)
	{
		SetState(eStateKnifeBanshee::HIDEKNIFEBANSHEE);
	}
}

void CKnifeBanshee::Render()
{
	if (_currentState == eStateKnifeBanshee::HIDEKNIFEBANSHEE)
	{
		return;
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
				}
				else
				{
					_currentFrame++;
				}
			}
		}

		bool flip = false;
		if (_nx >= 0)
		{
			flip = false;
		}
		else
		{
			flip = true;
		}

		_animationCurrent->Render(this->_positionX, this->_positionY, this->_currentFrame, 255, flip);
	}
}

RectEx CKnifeBanshee::GetBoundingBox()
{
	RectEx rect(
		_positionY + _height,
		_positionX,
		_positionY,
		_positionX + _width
	);
	return rect;
}

void CKnifeBanshee::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}

void CKnifeBanshee::SetState(int state)
{
	if (_currentState == state)
		return;

	CGameObject::SetState(state);

	switch (this->_currentState)
	{
	case eStateKnifeBanshee::HIDEKNIFEBANSHEE:
		this->_width = 0;
		this->_height = 0;
		this->_vX = 0;
		this->_vY = 0;
		break;

	case eStateKnifeBanshee::SHOWKNIFEBANSHEE:
		this->_width = KNIFEBANSHEE_COLLISION_WIDTH;
		this->_height = KNIFEBANSHEE_COLLISION_HEIGHT;
		this->_vX = KNIFEBANSHEE_SPEED;
		this->_vY = KNIFEBANSHEE_JUMP;
		break;

	default:
		break;
	}
}