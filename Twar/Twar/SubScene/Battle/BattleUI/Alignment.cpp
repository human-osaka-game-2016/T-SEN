/**
* @file Alignment.cpp
* @brief AlignmentƒNƒ‰ƒXŽÀ‘•
* @author haga
*/

#include "GameLib/GameLib.h"
#include "Alignment.h"
#include "../BattleData/BattleDataManager.h"


Alignment::Alignment(int texID, int zoomTexID, int vtxID)
	: m_TexID(texID)
	, m_ZoomTexID(zoomTexID)
	, m_VtxID(vtxID)
{
	GameLib::Instance().ShowMouseCursor(false);
	GameLib::Instance().SetMousePosCenter();
//	GameLib::Instance().GetMousePos(&m_Pos.x, &m_Pos.y);
	GameLib::Instance().CreateVtx(m_VtxID, 1800.f, 1000.f);

	HWND hWnd = InputDevice::GetInstance().GethWnd();

	RECT winRect;
	RECT clientRect;

	GetWindowRect(hWnd, &winRect);
	GetClientRect(hWnd, &clientRect);
	m_Pos.x = static_cast<int>(winRect.left + ((clientRect.right - clientRect.left) / 2));
	m_Pos.y = static_cast<int>(winRect.bottom - ((clientRect.bottom - clientRect.top) / 2));

}

Alignment::~Alignment()
{
}

void Alignment::Control()
{
	//GameLib::Instance().GetMousePos(&m_Pos.x, &m_Pos.y);
}

void Alignment::Draw()
{
	if (BattleDataManager::Instance().CheckZoom())
	{
		GameLib::Instance().DrawXYCenterPos(m_ZoomTexID, m_VtxID, m_Pos.x, m_Pos.y);
	}
	else
	{
		GameLib::Instance().DrawXYCenterPos(m_TexID, m_VtxID, m_Pos.x, m_Pos.y);
	}

}
