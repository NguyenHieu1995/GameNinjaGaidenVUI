#include "CCollision.h"

CCollision* CCollision::_instance = NULL;

CCollision* CCollision::GetInstance()
{
	if (NULL == _instance)
	{
		_instance = new CCollision();
	}
	return _instance;
}

CCollision::CCollision()
{

}

CCollision::~CCollision()
{
}

// Kiem ta boardphase
// rectMove Doi tuong di chuyen
// speed toc do di chuyen cua doi tuong trong 1 frame
// rectStatic doi tuong dung yen
bool CCollision::CheckBroadPhase(RectEx rectMove, D3DXVECTOR2 speed, RectEx rectStatic)
{
	this->_bl = speed.x > 0 ? rectMove.left : rectMove.left + speed.x;			// left
	this->_br = speed.x > 0 ? rectMove.right + speed.x : rectMove.right;		// right
	this->_bt = speed.y > 0 ? rectMove.top + speed.y : rectMove.top;			// top
	this->_bb = speed.y > 0 ? rectMove.bottom : rectMove.bottom + speed.y;		// bottom

	if (this->_bl > rectStatic.right ||
		this->_br < rectStatic.left ||
		this->_bt < rectStatic.bottom ||
		this->_bb > rectStatic.top)
	{
		return false;
	}
	else
	{
		return true;
	}
}

LPCCOLLISIONINFO CCollision::SweptAABB(RectEx rectMove, D3DXVECTOR2 speed, RectEx rectStatic)
{
	float t = -1.0f;
	float nx = 0, ny = 0;

	LPCCOLLISIONINFO result = new CCollisionInfo(nx, ny, t);

	if ((int(rectMove.right - rectMove.left) == 0) ||
		(int(rectMove.top - rectMove.bottom) == 0) ||
		(int(rectStatic.right - rectStatic.left) == 0) ||
		(int(rectStatic.top - rectStatic.bottom) == 0))
	{
		return result;
	}

	if (!CheckBroadPhase(rectMove, speed, rectStatic))
		return result;

	// Xu ly 2 vat nam chong len nhau
	// Chua viet
	// =>
	// Vat di chuyen dung yen khong xay ra va cham
	if (0 == speed.x && 0 == speed.y)
		return result;

	// Vat di chuyen theo chieu duong
	if (speed.x > 0)
	{
		this->_dx_entry = rectStatic.left - rectMove.right;
		this->_dx_exit = rectStatic.right - rectMove.left;
	}
	else
	{
		// Vat di chuyen theo chieu am
		if (speed.x < 0)
		{
			this->_dx_entry = rectStatic.right - rectMove.left;
			this->_dx_exit = rectStatic.left - rectMove.right;
		}
	}

	// Vat di chuyen theo chieu duong
	if (speed.y > 0)
	{
		this->_dy_entry = rectStatic.bottom - rectMove.top;
		this->_dy_exit = rectStatic.top - rectMove.bottom;
	}
	else
	{
		// Vat di chuyen theo chieu am
		if (speed.y < 0)
		{
			this->_dy_entry = rectStatic.top - rectMove.bottom;
			this->_dy_exit = rectStatic.bottom - rectMove.top;
		}
	}

	if (0 == speed.x) // Vat khong di chuyen theo chieu X set cac thong so la: vo cung
	{
		this->_tx_entry = -std::numeric_limits<float>::infinity();
		this->_tx_exit = std::numeric_limits<float>::infinity();
	}
	else // Vat di chuyen tinh toan thoi gian bat dau va ket thuc va cham
	{
		this->_tx_entry = this->_dx_entry / speed.x;
		this->_tx_exit = this->_dx_exit / speed.x;
	}

	// Vat khong di chuyen theo chieu Y set cac thong so la: vo cung
	if (0 == speed.y)
	{
		this->_ty_entry = -std::numeric_limits<float>::infinity();
		this->_ty_exit = std::numeric_limits<float>::infinity();
	}
	else // Vat di chuyen tinh toan thoi gian bat dau va ket thuc va cham
	{
		this->_ty_entry = this->_dy_entry / speed.y;
		this->_ty_exit = this->_dy_exit / speed.y;
	}

	// v < dentry    =>    tentry > 1.0
	// dentry < 0  AND v > 0	=> tentry < 0
	// Collision :    0 < tentry < 1
	if ((this->_tx_entry < 0 && this->_ty_entry < 0) || this->_tx_entry > 1.0f || this->_ty_entry > 1.0f)
	{
		return result;
	}

	// Tinh toan thoi gian bat dau va ket thuc va cham
	//	Collide = collide on both axis
	//	Collide time = Entry time = max(txentry, tyentry)
	//	Exit time = min(txexit, tyexit)
	//	Entry Time < Exit Time
	this->_t_entry = max(this->_tx_entry, this->_ty_entry);
	this->_t_exit = min(this->_tx_exit, this->_ty_exit);

	// Neu thoi gian bat dau va cham lon hon thoi gian ket thuc va cham thi khong co va cham
	if (this->_t_entry > this->_t_exit)
	{
		return result;
	}

	// tinh toan thoi gian bat dau va cham cua 2 doi tuong
	result->_t = this->_t_entry;

	// Vat va cham theo truc x
	if (this->_tx_entry > this->_ty_entry)
	{
		result->_ny = 0;

		if (speed.x > 0)
		{
			result->_nx = -1.0f;	// va cham ben trai object static
		}
		else
		{
			result->_nx = 1.0f;		// va cham ben phai object static 
		}
	}
	else // Vat va cham theo truc y
	{
		result->_nx = 0;

		if (speed.y > 0)
		{
			result->_ny = -1.0f;
		}
		else
		{
			result->_ny = 1.0f;
		}
	}

	return result;
}

void CCollision::SweptAABB(
	float ml, float mt, float mr, float mb,
	float dx, float dy,
	float sl, float st, float sr, float sb,
	float& t, float& nx, float& ny)
{
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	if ((int(mr - ml) == 0) ||
		(int(mt - mb) == 0) ||
		(int(sr - sl) == 0) ||
		(int(st - sb) == 0))
	{
		return;
	}

	//
	// Broad-phase test 
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt + dy : mt;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb : mb + dy;

	if (br < sl || bl > sr || bb > st || bt < sb) return;


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}
	else if (dy < 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}

	if (dx == 0)
	{
		tx_entry = -std::numeric_limits<float>::infinity();
		tx_exit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -std::numeric_limits<float>::infinity();
		ty_exit = std::numeric_limits<float>::infinity();
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}


	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}

}
