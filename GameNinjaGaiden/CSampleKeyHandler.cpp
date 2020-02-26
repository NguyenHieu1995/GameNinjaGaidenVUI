#include "CSampleKeyHandler.h"
#include <dinput.h>
#include "CCamera.h"
#include "CGameSound.h"

CSampleKeyHandler::CSampleKeyHandler()
{

}

CSampleKeyHandler::~CSampleKeyHandler()
{

}

void CSampleKeyHandler::KeyState(BYTE* states, CGameObject* object)
{
	if ((states[DIK_SPACE] & 0x80) > 0)
	{
		DebugOut(L"[INFO] Nhap phim space\n");
	}

	if (object->GetAction() == eActionObject::CLIMB)
	{
		if (((states[DIK_LEFT] & 0x80) > 0) && ((states[DIK_D] & 0x80) > 0) ||
			((states[DIK_RIGHT] & 0x80) > 0) && ((states[DIK_D] & 0x80) > 0))
		{
			object->SetState(eStateRyu::JUMPING_STATE);
			object->SetVx(RYU_RUN_SPEED);
			object->SetVy(RYU_JUMP_SPEED);
		}
	}
	else
	{
		if (((states[DIK_LEFT] & 0x80) > 0) || ((states[DIK_RIGHT] & 0x80) > 0))
		{
			if ((states[DIK_LEFT] & 0x80) > 0)
			{
				object->SetDirection(-1);
				object->SetState(eStateRyu::RUNNING_STATE);
				object->SetVx(object->GetDirection() * RYU_RUN_SPEED);
			}
			else
			{
				if ((states[DIK_RIGHT] & 0x80) > 0)
				{
					object->SetDirection(1);
					object->SetState(eStateRyu::RUNNING_STATE);
					object->SetVx(object->GetDirection() * RYU_RUN_SPEED);
				}
			}
		}
		else
		{
			if ((states[DIK_DOWN] && 0x80) > 0)
			{
				object->SetState(eStateRyu::SITTING_STATE);
				object->SetVx(0.0f);
			}
			else
			{
				object->SetState(eStateRyu::STAND_STATE);
				//object->SetVx(0.0f);
			}
		}
	}

	if (object->GetSpeed().y != 0)
	{
		object->SetState(eStateRyu::JUMPING_STATE);
	}
}

void CSampleKeyHandler::OnKeyDown(int keycode, CGameObject* object)
{
	switch (keycode)
	{
	case DIK_D:
		//CCamera::GetInstance()->UnLock();
		if (object->GetAction() != eActionObject::CLIMB &&
			object->GetAction() != eActionObject::JUMP)
		{
			object->SetState(eStateRyu::JUMPING_STATE);
			object->SetVy(RYU_JUMP_SPEED);
		}

		CGameSound::GetInstance()->playSound("jump", false, 1);
		break;

	case DIK_F:
		if (object->GetAction() != eActionObject::CLIMB)
		{
			if (object->GetAction() == eActionObject::SIT)
			{
				object->SetState(eStateRyu::ATTACKING_SITTING_STATE);
			}
			else
			{
				if (CInput::GetInstance()->IsKeyDown(DIK_UP))
				{
					object->SetState(eStateRyu::ATTACKING_STAND_STATE);
				}
				else
				{
					object->SetState(eStateRyu::ATTACKING_SWORD_STATE);
				}
			}
		}
		CGameSound::GetInstance()->playSound("attack", false, 1);
		break;

	case DIK_ESCAPE:
		//CCamera::GetInstance()->Lock(object);
		break;
	case DIK_0:
		object->SetState(0);
		break;
	case DIK_1:
		object->SetState(1);
		break;
	case DIK_2:
		object->SetState(2);
		break;
	case DIK_3:
		object->SetState(3);
		break;
	case DIK_4:
		object->SetState(4);
		break;
	case DIK_5:
		object->SetState(5);
		break;
	case DIK_6:
		object->SetState(6);
		break;
	case DIK_7:
		object->SetState(7);
		break;
	case DIK_8:
		object->SetState(8);
		break;
	case DIK_9:
		object->SetState(9);
		break;

	default:
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int keycode, CGameObject* object)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", keycode);
	switch (keycode)
	{
	case DIK_SPACE:
		//DebugOut(L"[INFO] Space Key Up\n");
		break;
	}
}