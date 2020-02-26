#include "CGridMap.h"

CCellGrid::CCellGrid()
{
	this->_listObject.clear();
	this->_posX = 0;
	this->_posY = 0;
	this->_weight = 0;
	this->_height = 0;
}

CCellGrid::CCellGrid(int x, int y, int w, int h)
{
	this->_listObject.clear();
	this->_posX = x;
	this->_posY = y;
	this->_weight = w;
	this->_height = h;
}

CCellGrid::~CCellGrid()
{
	for (auto item = this->_listObject.begin(); item != this->_listObject.end(); ++item)
	{
		(*item) = NULL;
	}
	this->_listObject.clear();
}

void CCellGrid::Clear()
{
	for (auto item = this->_listObject.begin(); item != this->_listObject.end(); ++item)
	{
		(*item) = NULL;
	}
	this->_listObject.clear();
}

vector<LPCGAMEOBJECT> CCellGrid::GetListObject()
{
	return this->_listObject;
}

void CCellGrid::AddObject(LPCGAMEOBJECT object)
{
	this->_listObject.push_back(object);
}

bool CCellGrid::IsContain(RectEx rect)
{
	//RectEx rect = object->GetBoundingBox();
	return !((rect.right < this->_posX) ||
		(rect.left > (this->_posX + this->_weight)) ||
		(rect.top < this->_posY) ||
		(rect.bottom > (this->_posY + this->_height)));
}

bool CCellGrid::IsNotContainCamera()
{
	RectEx rect(CCamera::GetInstance()->GetBound());

	return ((rect.right < this->_posX) ||
		(rect.left > (this->_posX + this->_weight)) ||
		(rect.top < this->_posY) ||
		(rect.bottom > (this->_posY + this->_height)));
}

void CCellGrid::RenderCellMap()
{
	RECT rect;
	rect.left = this->_posX;
	rect.bottom = this->_posY;
	rect.right = rect.left + this->_weight;
	rect.top = rect.bottom + this->_height;
	CDirectX::GetInstance()->DrawBoundingBox(rect);
}

// ===============================================================

CGridMap::CGridMap()
{
	this->_row = 0;
	this->_column = 0;
	this->_widthCell = 0;
	this->_heightCell = 0;
	this->_listCell.clear();
}

CGridMap::CGridMap(LPCWSTR filePath, int row, int column, int w, int h)
{
	this->_row = row;
	this->_column = column;
	this->_widthCell = w;
	this->_heightCell = h;
	this->_listCell.clear();

	this->LoadGridMap(filePath);
	this->LoadGridMapStart(filePath);
}

CGridMap::CGridMap(int row, int column, int w, int h)
{
	this->_row = row;
	this->_column = column;
	this->_widthCell = w;
	this->_heightCell = h;
	this->_listCell.clear();

	LPCCELLGRID cell = NULL;
	int index = 0;

	for (int i = 0; i < this->_row; ++i)
	{
		for (int j = 0; j < this->_column; ++j)
		{
			cell = new CCellGrid(j * this->_widthCell, i * this->_heightCell, this->_widthCell, this->_heightCell);
			index = i * _column + j;
			this->_listCell[index] = cell;
			cell = NULL;
		}
	}

	return;
}

CGridMap::~CGridMap()
{
	for (auto item = _listCell.begin(); item != _listCell.end(); ++item)
	{
		if (item->second != NULL)
		{
			delete item->second;
			item->second = NULL;
		}
	}
	_listCell.clear();

	for (auto item = _listCellStart.begin(); item != _listCellStart.end(); ++item)
	{
		if (item->second != NULL)
		{
			delete item->second;
			item->second = NULL;
		}
	}
	_listCellStart.clear();
}

// Tra ve danh sach cac doi tuong nam trong cac cell co va cham voi camera
vector<LPCGAMEOBJECT> CGridMap::GetListObject()
{
	ReloadGridMap();

	vector<LPCGAMEOBJECT> result;
	vector<LPCGAMEOBJECT> listObjectOfCell;

	result.clear();
	listObjectOfCell.clear();

	//RECT rect = CCamera::GetInstance()->GetBound();
	RectEx rect(CCamera::GetInstance()->GetBound());

	for (auto item = _listCell.begin(); item != _listCell.end(); ++item)
	{
		if (item->second->IsContain(rect))
		{
			listObjectOfCell = item->second->GetListObject();

			for (auto object = listObjectOfCell.begin(); object != listObjectOfCell.end(); ++object)
			{
				if (!(std::find(result.begin(), result.end(), *object) != result.end()))
				{
					result.push_back(*object);
				}
			}
		}
	}

	listObjectOfCell.clear();
	for (auto item = _listCellStart.begin(); item != _listCellStart.end(); ++item)
	{
		if (item->second->IsNotContainCamera())
		{
			listObjectOfCell = item->second->GetListObject();
			for (auto object = listObjectOfCell.begin(); object != listObjectOfCell.end(); ++object)
			{
				if (*object != NULL)
				{
					//if ((*object)->IsAlive() == false)
					if (!(std::find(result.begin(), result.end(), *object) != result.end()))
					{
						int x = (*object)->GetPositionStart().x;
						if (x > rect.right || x < rect.left)
						{
							(*object)->Reset();
						}
					}
				}
			}
		}
	}

	return result;
}

int CGridMap::GetRow()
{
	return this->_row;
}

int CGridMap::GetColumn()
{
	return this->_column;
}

int CGridMap::GetWidthCell()
{
	return this->_widthCell;
}

int CGridMap::GetHeightCell()
{
	return this->_heightCell;
}

// Them doi tuong game vao cell thich hop theo vi tri cua doi tuong
void CGridMap::Insert(LPCGAMEOBJECT object)
{
	for (auto item = _listCell.begin(); item != _listCell.end(); ++item)
	{
		if (item->second->IsContain(object->GetBoundingBox()))
		{
			item->second->AddObject(object);
		}
	}

	return;
}

void CGridMap::InsertStart(LPCGAMEOBJECT object)
{
	for (auto item = _listCellStart.begin(); item != _listCellStart.end(); ++item)
	{
		if (item->second->IsContain(object->GetBoundingBox()))
		{
			item->second->AddObject(object);
		}
	}

	return;
}

// Render khung cua cac cell trong grid
void CGridMap::RenderGridMap()
{
	for (auto item = _listCell.begin(); item != _listCell.end(); ++item)
	{
		item->second->RenderCellMap();
	}
}

void CGridMap::LoadGridMap(LPCWSTR filePath)
{
	_bstr_t path(filePath);
	TiXmlDocument doc(path);

	// Neu file chua ton tai thi khoi tao tu danh sach object va ghi ra file xml
	if (!doc.LoadFile())
	{
		DebugOut(L"[ERROR] Load file XML GridMap that bai! Loi: %s\n", doc.ErrorDesc());

		TiXmlDocument doc;

		TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "utf-8", "");
		doc.LinkEndChild(dec);

		TiXmlElement* root = new TiXmlElement("Cells");
		root->SetAttribute("wc", this->_widthCell);
		root->SetAttribute("hc", this->_heightCell);
		root->SetAttribute("row", this->_row);
		root->SetAttribute("column", this->_column);
		doc.LinkEndChild(root);

		LPCCELLGRID cell = NULL;
		int index = 0;

		// Khoi tao danh sach cac cell trong grid
		for (int i = 0; i < this->_row; ++i)
		{
			for (int j = 0; j < this->_column; ++j)
			{
				cell = new CCellGrid(j * this->_widthCell, i * this->_heightCell, this->_widthCell, this->_heightCell);
				index = i * _column + j;
				this->_listCell[index] = cell;
				cell = NULL;
			}
		}

		// Them cac doi tuong vao cac cell tuong ung
		unordered_map<int, LPCGAMEOBJECT> listobject = CGameObjects::GetInstance()->GetListObject();
		for (auto itemObject = listobject.begin(); itemObject != listobject.end(); ++itemObject)
		{
			Insert(itemObject->second);
		}

		// Duyet va ghi cac thong tin cua grid ra file xml
		TiXmlElement* subcell;
		TiXmlElement* object;
		vector<LPCGAMEOBJECT> listObjectCell;

		for (auto itemCell = _listCell.begin(); itemCell != _listCell.end(); ++itemCell)
		{
			subcell = new TiXmlElement("SubCell");
			subcell->SetAttribute("id", itemCell->first);
			root->LinkEndChild(subcell);

			listObjectCell = itemCell->second->GetListObject();
			for (auto itemObject = listObjectCell.begin(); itemObject != listObjectCell.end(); ++itemObject)
			{
				object = new TiXmlElement("Object");
				object->SetAttribute("id", (*itemObject)->GetID());
				subcell->LinkEndChild(object);
				object = NULL;
			}

			subcell = NULL;
		}
		// Luu file
		doc.SaveFile(_bstr_t(filePath));
		
		return;
	}

	//DebugOut(L"[INFO] Duong dan file XML GridMap: %s\n", filePath);

	// Neu file da ton tai trong source thi load thong tin grid tu file xml
	for (auto item = _listCell.begin(); item != _listCell.end(); ++item)
	{
		if (item->second != NULL)
		{
			delete item->second;
			item->second = NULL;
		}
	}
	_listCell.clear();

	// Doc cac thong so cua grid
	TiXmlElement* root = doc.RootElement();

	TiXmlElement* subcell;
	TiXmlElement* object;

	root->QueryIntAttribute("wc", &(this->_widthCell));
	root->QueryIntAttribute("hc", &(this->_heightCell));
	root->QueryIntAttribute("row", &(this->_row));
	root->QueryIntAttribute("column", &(this->_column));

	LPCCELLGRID cell = NULL;
	int index = 0;

	// Khoi tao danh sach cac cell
	for (int i = 0; i < this->_row; ++i)
	{
		for (int j = 0; j < this->_column; ++j)
		{
			cell = new CCellGrid(j * this->_widthCell, i * this->_heightCell, this->_widthCell, this->_heightCell);
			index = i * _column + j;
			this->_listCell[index] = cell;
			cell = NULL;
		}
	}

	int idCell, idObject;

	// Them cac doi tuonng vao cac cell tuong  ung
	for (subcell = root->FirstChildElement(); subcell != NULL; subcell = subcell->NextSiblingElement())
	{
		subcell->QueryIntAttribute("id", &idCell);

		for (object = subcell->FirstChildElement(); object != NULL; object = object->NextSiblingElement())
		{
			object->QueryIntAttribute("id", &idObject);
			this->_listCell[idCell]->AddObject(CGameObjects::GetInstance()->GetObjectByID(idObject));
		}
	}
	//DebugOut(L"[SUCCESS] Load all Object GridMap success");	

	return;
}

void CGridMap::LoadGridMapStart(LPCWSTR filePath)
{
	_bstr_t path(filePath);
	TiXmlDocument doc(path);

	// Neu file chua ton tai thi khoi tao tu danh sach object va ghi ra file xml
	if (!doc.LoadFile())
	{
		DebugOut(L"[ERROR] Load file XML GridMap that bai! Loi: %s\n", doc.ErrorDesc());

		TiXmlDocument doc;

		TiXmlDeclaration* dec = new TiXmlDeclaration("1.0", "utf-8", "");
		doc.LinkEndChild(dec);

		TiXmlElement* root = new TiXmlElement("Cells");
		root->SetAttribute("wc", this->_widthCell);
		root->SetAttribute("hc", this->_heightCell);
		root->SetAttribute("row", this->_row);
		root->SetAttribute("column", this->_column);
		doc.LinkEndChild(root);

		LPCCELLGRID cell = NULL;
		int index = 0;

		// Khoi tao danh sach cac cell trong grid
		for (int i = 0; i < this->_row; ++i)
		{
			for (int j = 0; j < this->_column; ++j)
			{
				cell = new CCellGrid(j * this->_widthCell, i * this->_heightCell, this->_widthCell, this->_heightCell);
				index = i * _column + j;
				this->_listCellStart[index] = cell;
				cell = NULL;
			}
		}

		// Them cac doi tuong vao cac cell tuong ung
		unordered_map<int, LPCGAMEOBJECT> listobject = CGameObjects::GetInstance()->GetListObject();
		for (auto itemObject = listobject.begin(); itemObject != listobject.end(); ++itemObject)
		{
			LPCGAMEOBJECT object = itemObject->second;
			if ((object->GetTag() == eObjectType::BANSHEE) ||
				(object->GetTag() == eObjectType::BATBROWN) ||
				(object->GetTag() == eObjectType::BIRDBROWN) ||
				(object->GetTag() == eObjectType::CAT) ||
				(object->GetTag() == eObjectType::MACHINEGUNGUY) ||
				(object->GetTag() == eObjectType::SWORDMAN))
			{

				InsertStart(itemObject->second);
			}
		}

		return;
	}

	//DebugOut(L"[INFO] Duong dan file XML GridMap: %s\n", filePath);

	// Neu file da ton tai trong source thi load thong tin grid tu file xml
	for (auto item = _listCellStart.begin(); item != _listCellStart.end(); ++item)
	{
		if (item->second != NULL)
		{
			delete item->second;
			item->second = NULL;
		}
	}
	_listCellStart.clear();

	// Doc cac thong so cua grid
	TiXmlElement* root = doc.RootElement();

	TiXmlElement* subcell;
	TiXmlElement* object;

	root->QueryIntAttribute("wc", &(this->_widthCell));
	root->QueryIntAttribute("hc", &(this->_heightCell));
	root->QueryIntAttribute("row", &(this->_row));
	root->QueryIntAttribute("column", &(this->_column));

	LPCCELLGRID cell = NULL;
	int index = 0;

	// Khoi tao danh sach cac cell
	for (int i = 0; i < this->_row; ++i)
	{
		for (int j = 0; j < this->_column; ++j)
		{
			cell = new CCellGrid(j * this->_widthCell, i * this->_heightCell, this->_widthCell, this->_heightCell);
			index = i * _column + j;
			this->_listCellStart[index] = cell;
			cell = NULL;
		}
	}

	int idCell, idObject;

	// Them cac doi tuonng vao cac cell tuong  ung
	for (subcell = root->FirstChildElement(); subcell != NULL; subcell = subcell->NextSiblingElement())
	{
		subcell->QueryIntAttribute("id", &idCell);

		for (object = subcell->FirstChildElement(); object != NULL; object = object->NextSiblingElement())
		{
			object->QueryIntAttribute("id", &idObject);

			LPCGAMEOBJECT object = CGameObjects::GetInstance()->GetObjectByID(idObject);
			if ((object->GetTag() == eObjectType::BANSHEE) ||
				(object->GetTag() == eObjectType::BATBROWN) ||
				(object->GetTag() == eObjectType::BIRDBROWN) ||
				(object->GetTag() == eObjectType::CAT) ||
				(object->GetTag() == eObjectType::MACHINEGUNGUY) ||
				(object->GetTag() == eObjectType::SWORDMAN))
			{

				this->_listCellStart[idCell]->AddObject(CGameObjects::GetInstance()->GetObjectByID(idObject));
			}/*
			this->_listCellStart[idCell]->AddObject(CGameObjects::GetInstance()->GetObjectByID(idObject));*/
		}
	}
	//DebugOut(L"[SUCCESS] Load all Object GridMap success");	

	return;
}

void CGridMap::ReloadGridMap()
{
	for (auto item = _listCell.begin(); item != _listCell.end(); ++item)
	{
		if (item->second != NULL)
		{
			item->second->Clear();
		}
	}

	unordered_map<int, LPCGAMEOBJECT> listobject = CGameObjects::GetInstance()->GetListObject();

	for (auto itemObject = listobject.begin(); itemObject != listobject.end(); ++itemObject)
	{
		Insert(itemObject->second);

		//if (itemObject)
	}
}