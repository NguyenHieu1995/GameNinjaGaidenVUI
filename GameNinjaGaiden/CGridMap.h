#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <unordered_map>
#include <comdef.h>
#include "CCamera.h"
#include <vector>
#include "CStruct.h"
#include "CGameObjects.h"
#include <iostream>
#include <algorithm>

class CCellGrid
{
public:
	CCellGrid();
	CCellGrid(int x, int y, int w, int h);
	~CCellGrid();

private:
	vector<LPCGAMEOBJECT> _listObject;		// Danh sach object trong cell
	int _posX, _posY;						// Vi tri cua cell trong grid
	int _weight, _height;					// Kich thuoc cua cell

public:
	void AddObject(LPCGAMEOBJECT object);	// Them doi tuong vao danh sach mang
	vector<LPCGAMEOBJECT> GetListObject();	// Tra ve danh sach tat ca cac doi tuong luu tru trong Game
	bool IsContain(RectEx rect);			// Kiem tra doi tuong co thuoc cell grid hay khong
	bool IsNotContainCamera();
	void RenderCellMap();

	void Clear();
};

typedef CCellGrid* LPCCELLGRID;

//=======================================================

class CGridMap
{
public:
	CGridMap();
	CGridMap(int row, int column, int w, int h);
	CGridMap(LPCWSTR filePath, int row, int column, int w, int h);						// Khoi tao grid map by XML File
	~CGridMap();

private:
	int _row, _column; // Row and column of grid
	int _widthCell, _heightCell; // Kich thuoc cua mot Cell
	unordered_map<int, LPCCELLGRID> _listCell;	// Danh sach cac cell trong map
	unordered_map<int, LPCCELLGRID> _listCellStart;
	

public:
	//void LoadGridMapFromFileXML(LPCWSTR filePath);		// Load grid from xml
	vector<LPCGAMEOBJECT> GetListObject();		// Return vector object by rect of camera
	//void Add(int row, int column, LPCCELLGRID cell); // Them cell cua grid theo vi tri row and column of grid
	void Insert(LPCGAMEOBJECT object);					// Kiem tra doi tuong thuoc cell nao va them doi tuong vao cell thich hop
	void InsertStart(LPCGAMEOBJECT object);
	int GetRow();
	int GetColumn();
	int GetWidthCell();
	int GetHeightCell();

	void RenderGridMap();

	void LoadGridMap(LPCWSTR filePath);			// Load info Grid Map from file XML	
	void LoadGridMapStart(LPCWSTR filePath);

	void ReloadGridMap();
};

//=======================================================

