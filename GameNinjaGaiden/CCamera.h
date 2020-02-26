#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "CConstant.h"
#include "CDebug.h"
#include "CGameObject.h"

//
// Lop quan ly Camera(Viewport )
// - Quan ly thong so cua camera 
// - Tinh toan toa do cua doi tuong tren camara
//
class CCamera
{
private:
	CCamera();
	static CCamera* _instance;

public:
	~CCamera();
	static CCamera* GetInstance();

public:
	void SetPositionViewport(float x, float); // Set vi tri top left cua viewport
	D3DXVECTOR2 GetPostionInViewport(float x, float y); // Get vi tri cua object tren viewport (world -> view)
	RECT GetBound();									// Get RECT cua Viewport
	void Update();										// Update vi tri cua camera 
	void Lock(CGameObject* object);						// Khoa camera theo object
	void UnLock();										// Giu nguyen camera khong di chuyen theo nhan vat nua
	void Render(int score, int time, int idWeapon, int number_P, int spiritualStrengthPoint, int stageFirst, int stageSecond, int healthNinja, int healthEnemy);

	int GetMinPositioX();
	int GetMaxPostionX();

	void SetMinPositioX(int x);
	void SetMaxPostionX(int x);

private:
	float _positionX;	// toa do x cua viewport
	float _positionY;	// toa do y cua viewport
	float _width;		// chieu dai cua viewport
	float _height;		// chieu cao cua viewport
	CGameObject* _objectLock;	// Doi tuong khoa cua view port(neu khac Null thi man hinh di chuyen theo doi tuong nay)
	int _minPositioX;
	int _maxPostionX;
};
