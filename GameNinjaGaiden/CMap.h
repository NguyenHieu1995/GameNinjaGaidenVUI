#pragma once
#include <iostream>
#include <fstream>
#include <d3dx9.h>
#include <Windows.h>
#include <unordered_map>
#include "CDirectX.h"
#include "CTextures.h"

using namespace std;

class CMap
{
public:
	CMap(int id, LPCWSTR fileText, LPDIRECT3DTEXTURE9 texture);
	virtual ~CMap();

public:	
	void Render();

private:
	int _iID;
	int _iWidth, _iHeight;		// Size of one tidemap
	int** _matrixMap;			// Matrix save position of tidemap
	int _iColumn, _iRow;		// Row and column of matrix
	LPDIRECT3DTEXTURE9 _pTexture;		// Texture of all tidemap

	bool LoadMap(LPCWSTR fileText, LPDIRECT3DTEXTURE9 texture);
};
typedef CMap* LPCMAP;

class CMaps
{
public:
	~CMaps();
	
public:
	static CMaps* GetInstance();
	bool LoadFileXML(LPCWSTR filePath);
	LPCMAP Get(unsigned int id);

private:
	static CMaps* _instance;

	// database map of game
	unordered_map<int, LPCMAP> _maps;
	void Add(int id, LPCWSTR fileText, LPDIRECT3DTEXTURE9 texture);

	CMaps();
};

