#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "CConstant.h"
#include "CWindow.h"
#include <cmath>

//
// Class manage Direct Device
//
class CDirectX
{
public:
	~CDirectX();

	static CDirectX *GetInstance();

private:
	CDirectX();
	static CDirectX *_instance; 

	LPDIRECT3D9 _d3d;			// Pointer Direct 9
	LPDIRECT3DDEVICE9 _d3ddv;	// Pointer Device

	LPDIRECT3DSURFACE9 _backBuffer; // BackBuffer of Game
	LPD3DXSPRITE _spriteHandler;	// Sprite handler

public:
	LPDIRECT3D9 GetD3D();	// DirectX 
	LPDIRECT3DDEVICE9 GetDirect3DDevice(); // Directx Device
	LPD3DXSPRITE GetSpriteHandler();		// Sprite Handler
	LPDIRECT3DSURFACE9 GetBackBuffer();		// Backbuffer

	// Init DirectX, Device and Sprite
	bool Init();

	// Draw Texture
	void DrawTexture(float x, float y, LPDIRECT3DTEXTURE9 texture);

	// Draw Sprite
	// scale: ti le phong to, thu nho (1.0f khong thay doi)
	// flipX: Lat theo chieu x (true: lat, false: khong lat)
	// flipY: Lat theo chieu y (true: lat, false: khong lat)
	void DrawSprite(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT rect, int alpha, float scale = 1.0f, bool flipX = false, bool flipY = false);
	//void DrawSprite(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT rect, bool flipX = false, bool flipY = false);
	void DrawSprite(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT rect, int alpha, float scale, bool flipX, float xFlip, bool flipY, float yFlip, float angle = 0.0f);

	// Ve khung va cham cua object
	void DrawBoundingBox(RECT rect);

	void DrawRectangle(RECT rect);
};
