#include "CDirectX.h"
#include "CCamera.h"

CDirectX *CDirectX::_instance = NULL;

CDirectX::CDirectX()
{
	this->_d3d = NULL;
	this->_d3ddv = NULL;
	this->_backBuffer = NULL;
	this->_spriteHandler = NULL;
}

CDirectX::~CDirectX()
{
	if (this->_d3d != NULL)
		this->_d3d->Release();

	if (this->_d3ddv != NULL)
		this->_d3ddv->Release();
	
	if (this->_backBuffer != NULL)
		this->_backBuffer->Release();
	
	if (this->_spriteHandler != NULL)
		this->_spriteHandler->Release();
}

CDirectX *CDirectX::GetInstance()
{
	if (_instance == NULL)
		_instance = new CDirectX();

	return _instance;
}

// Init DirectX, Device and Sprite
bool CDirectX::Init()
{
	this->_d3d = Direct3DCreate9(D3D_SDK_VERSION);

	//
	D3DPRESENT_PARAMETERS d3dpp;
	
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;

	// Rect of window
	RECT r;
	HWND hWnd = CWindow::GetInstance()->GetHwnd();
	GetClientRect(hWnd, &r);

	d3dpp.BackBufferHeight = r.bottom + 1;
	d3dpp.BackBufferWidth = r.right + 1;
	
	// Create Device
	this->_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&this->_d3ddv
	);

	if (this->_d3ddv == NULL)
	{
		OutputDebugString(L"[ERROR] CreateDevice Failed!\n");
		return false;
	}

	this->_d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &this->_backBuffer);

	// Create Sprite
	D3DXCreateSprite(this->_d3ddv, &this->_spriteHandler);

	return true;
}

LPDIRECT3D9 CDirectX::GetD3D()
{
	return this->_d3d;
}

LPDIRECT3DDEVICE9 CDirectX::GetDirect3DDevice()
{
	return this->_d3ddv;
}

LPD3DXSPRITE CDirectX::GetSpriteHandler()
{
	return this->_spriteHandler;
}

LPDIRECT3DSURFACE9 CDirectX::GetBackBuffer()
{
	return this->_backBuffer;
}

// Draw Texture
void CDirectX::DrawTexture(float x, float y, LPDIRECT3DTEXTURE9 texture)
{
	D3DXVECTOR3 position(x, y, 0);
	this->_spriteHandler->Draw(texture, NULL, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
}

// Draw Sprite
void CDirectX::DrawSprite(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT rect, int alpha, float scale, bool flipX, bool flipY)
{
	if (texture == NULL)
	{
		return;
	}
	//D3DXVECTOR3 position(x, y, 0);

	// Find center of sprite
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)(abs(rect.right - rect.left) / 2 * scale),
		(float)(abs(rect.bottom - rect.top) / 2 * scale));

	// Screen position of the sprite
	// Chuyen goc to do xuong phia duoi Left bottom
	D3DXVECTOR2 translate = CCamera::GetInstance()->GetPostionInViewport(x, y + (abs(rect.bottom - rect.top) * scale));//D3DXVECTOR2((float)x, (float)y);
	
	// Scaling X,Y
	D3DXVECTOR2 scaling(scale, scale);

	// Flip chuyen goc toa do hinh => right top tranh bi giat hinh
	if (flipX)  // if flip horizontal
	{
		scaling.x *= -1;            // negative X scale to flip
		// Get center of flipped image.
		spriteCenter.x -= (float)(abs(rect.right - rect.left) / 2 * scale);
		// Flip occurs around left edge, translate right to put
		// Flipped image in same location as original.

		// Them dong nay de Chuyen goc toa ve left top
		translate.x += (float)(abs(rect.right - rect.left) * scale);
	}

	if (flipY)    // if flip vertical
	{
		scaling.y *= -1;            // negative Y scale to flip
		// Get center of flipped image
		spriteCenter.y -= (float)(abs(rect.bottom - rect.top) * scale);
		// Flip occurs around top edge, translate down to put
		// Flipped image in same location as original.
		translate.y += (float)(abs(rect.bottom - rect.top) * scale);
	}

	translate.x = (FLOAT)(int)translate.x;
	translate.y = (FLOAT)(int)translate.y;

	// Create a matrix to rotate, scale and position our sprite
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,                // the matrix
		NULL,                   // keep origin at top left when scaling
		0.0f,                   // no scaling rotation
		&scaling,               // scale amount
		&spriteCenter,          // rotation center
		NULL, //(float)(spriteData.angle),  // rotation angle
		&translate);            // X,Y location

	// Lay ma tran ban dau truoc khi bien doi
	D3DXMATRIX oldMatrix;
	this->_spriteHandler->GetTransform(&oldMatrix);

	// Tell the sprite about the matrix
	this->_spriteHandler->SetTransform(&matrix);
	   
	//D3DXVECTOR3 center = D3DXVECTOR3((abs(rect.right - rect.left) / 2.0f), (abs(rect.bottom - rect.top) / 2.0f), 0.0f);
	//this->_spriteHandler->Draw(texture, &rect, &center, &position, D3DCOLOR_XRGB(255, 255, 255));
	
	// Render sprite 
	this->_spriteHandler->Draw(texture, &rect, NULL, NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	//this->_spriteHandler->Draw(texture, &rect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	// Set transform ve lai ban dau
	this->_spriteHandler->SetTransform(&oldMatrix);
}

void CDirectX::DrawSprite(float x, float y, LPDIRECT3DTEXTURE9 texture, RECT rect, int alpha, float scale, bool flipX, float xFlip, bool flipY, float yFlip, float angle)
{
	if (texture == NULL)
	{
		return;
	}
	//D3DXVECTOR3 position(x, y, 0);

	// Find center of sprite
	D3DXVECTOR2 spriteCenter = D3DXVECTOR2((float)(abs(rect.right - rect.left) / 2 * scale),
		(float)(abs(rect.bottom - rect.top) / 2 * scale));

	// Screen position of the sprite
	// Chuyen goc to do xuong phia duoi Left bottom
	D3DXVECTOR2 translate = CCamera::GetInstance()->GetPostionInViewport(x, y + (abs(rect.bottom - rect.top) * scale));//D3DXVECTOR2((float)x, (float)y);

	// Scaling X,Y
	D3DXVECTOR2 scaling(scale, scale);

	// Flip chuyen goc toa do hinh => right top tranh bi giat hinh
	if (flipX)  // if flip horizontal
	{
		scaling.x *= -1;            // negative X scale to flip
		// Get center of flipped image.
		spriteCenter.x -= (float)(abs(rect.right - rect.left) / 2 * scale);
		// Flip occurs around left edge, translate right to put
		// Flipped image in same location as original.

		// Them dong nay de Chuyen goc toa ve left top
		translate.x += ((float)(abs(rect.right - rect.left) * scale) * xFlip);
	}

	if (flipY)    // if flip vertical
	{
		scaling.y *= -1;            // negative Y scale to flip
		// Get center of flipped image
		spriteCenter.y -= (float)(abs(rect.bottom - rect.top) * scale);
		// Flip occurs around top edge, translate down to put
		// Flipped image in same location as original.
		translate.y += ((float)(abs(rect.bottom - rect.top) * scale) * yFlip);
	}

	translate.x = (FLOAT)(int)translate.x;
	translate.y = (FLOAT)(int)translate.y;

	// Create a matrix to rotate, scale and position our sprite
	D3DXMATRIX matrix;
	D3DXMatrixTransformation2D(
		&matrix,                // the matrix
		NULL,                   // keep origin at top left when scaling
		0.0f,                   // no scaling rotation
		&scaling,               // scale amount
		&spriteCenter,          // rotation center
		float(angle * (PI / 180)), //(float)(spriteData.angle),  // rotation angle
		&translate);            // X,Y location

	// Lay ma tran ban dau truoc khi bien doi
	D3DXMATRIX oldMatrix;
	this->_spriteHandler->GetTransform(&oldMatrix);

	// Tell the sprite about the matrix
	this->_spriteHandler->SetTransform(&matrix);

	//D3DXVECTOR3 center = D3DXVECTOR3((abs(rect.right - rect.left) / 2.0f), (abs(rect.bottom - rect.top) / 2.0f), 0.0f);
	//this->_spriteHandler->Draw(texture, &rect, &center, &position, D3DCOLOR_XRGB(255, 255, 255));

	// Render sprite 
	this->_spriteHandler->Draw(texture, &rect, NULL, NULL, D3DCOLOR_ARGB(alpha, 255, 255, 255));
	//this->_spriteHandler->Draw(texture, &rect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	// Set transform ve lai ban dau
	this->_spriteHandler->SetTransform(&oldMatrix);
}

// Ve khung va cham cua doi tuong
void CDirectX::DrawBoundingBox(RECT rect)
{
	// Tinh toan khung cua doi tuong tren viewport
	D3DXVECTOR2 position = CCamera::GetInstance()->GetPostionInViewport((float)rect.left, (float)rect.top);
	RECT rectBoundRender;
	rectBoundRender.left = (LONG)position.x;
	rectBoundRender.right = (LONG)(position.x + abs(rect.right - rect.left));
	rectBoundRender.top = (LONG)position.y;
	rectBoundRender.bottom = (LONG)(position.y + abs(rect.bottom - rect.top));

	// Ve 4 duong thang
	LPD3DXLINE line;
	D3DXCreateLine(CDirectX::GetInstance()->GetDirect3DDevice(), &line);
	D3DXVECTOR2 lines[] = {
		D3DXVECTOR2((FLOAT)rectBoundRender.left, (FLOAT)rectBoundRender.top),
		D3DXVECTOR2((FLOAT)rectBoundRender.right, (FLOAT)rectBoundRender.top),
		D3DXVECTOR2((FLOAT)rectBoundRender.right, (FLOAT)rectBoundRender.bottom),
		D3DXVECTOR2((FLOAT)rectBoundRender.left, (FLOAT)rectBoundRender.bottom),
		D3DXVECTOR2((FLOAT)rectBoundRender.left, (FLOAT)rectBoundRender.top)
	};

	line->Begin();
	line->Draw(lines, 5, D3DCOLOR_XRGB(255, 0, 0));
	line->End();

	line->Release();
}

void CDirectX::DrawRectangle(RECT rect)
{
	
}