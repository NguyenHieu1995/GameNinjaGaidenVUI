#include "CBulletMachineGunGuy.h"


CBulletMachineGunGuy::CBulletMachineGunGuy(int id) : CGameObject(id)
{
	this->_animation.push_back(CAnimations::GetInstance()->Get(4001));
	this->_animationCurrent = _animation[0];

	SetState(eStateBulletMachineGunGuy::SHOWBULLETMACHINEGUNGUY);
	this->_tag = eObjectType::BULLETMACHINEGUNGUY;

	_isCutEnemi = false;
}

CBulletMachineGunGuy::CBulletMachineGunGuy(int id, int x, int y) : CGameObject(id, x, y)
{
	this->_animation.push_back(CAnimations::GetInstance()->Get(4001));
	this->_animationCurrent = _animation[0];

	SetState(eStateBulletMachineGunGuy::SHOWBULLETMACHINEGUNGUY);
	this->_tag = eObjectType::BULLETMACHINEGUNGUY;

	_isCutEnemi = false;
}

CBulletMachineGunGuy::~CBulletMachineGunGuy()
{
}

void CBulletMachineGunGuy::Update(DWORD dt, vector<LPCGAMEOBJECT>* coObject)
{
	this->_vX = _nx * BULLETMACHINEGUNGUY_SPEED;

	_frameTime += dt;

	if (_currentState == eStateBulletMachineGunGuy::SHOWBULLETMACHINEGUNGUY)
	{
		CGameObject::Update(dt, coObject);

		_positionX += _dx;
		_positionY += _dy;
	}

	if (_positionX < CCamera::GetInstance()->GetBound().left || _positionX > CCamera::GetInstance()->GetBound().right)
	{
		SetState(eStateBulletMachineGunGuy::HIDEBULLETMACHINEGUNGUY);
	}
}
void CBulletMachineGunGuy::Render()
{
	/*if (_positionX <= 10)
	{
		SetState(eStateBulletMachineGunGuy::HIDEBULLETMACHINEGUNGUY);
	}*/

	if (_currentState == eStateBulletMachineGunGuy::HIDEBULLETMACHINEGUNGUY)
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

RectEx CBulletMachineGunGuy::GetBoundingBox()
{
	RectEx rect(
		_positionY + _height,
		_positionX,
		_positionY,
		_positionX + _width
	);
	return rect;
}

void CBulletMachineGunGuy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = _positionX;
	bottom = _positionY;

	right = left + _width;
	top = bottom + _height;
}

void CBulletMachineGunGuy::SetState(int state)
{
	if (_currentState == state)
		return;

	CGameObject::SetState(state);

	switch (this->_currentState)
	{
	case eStateBulletMachineGunGuy::HIDEBULLETMACHINEGUNGUY:
		this->_width = 0;
		this->_height = 0;
		this->_vX = 0;
		this->_vY = 0;
		break;

	case eStateBulletMachineGunGuy::SHOWBULLETMACHINEGUNGUY:
		this->_width = BULLETMACHINEGUNGUY_COLLISION_WIDTH;
		this->_height = BULLETMACHINEGUNGUY_COLLISION_HEIGHT;
		this->_vX = BULLETMACHINEGUNGUY_SPEED;
		this->_vY = 0;
		break;

	default:
		break;
	}
}