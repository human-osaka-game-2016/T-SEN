/**
* @file PolicyBackGround.h
* @brief PolicyBackGroundクラスヘッダ
* @author matsuda
*/
#include "GameLib/GameLib.h"
#include "PolicyBackGround.h"

PolicyBackGround::PolicyBackGround(int texID, int vtxID)
	:m_Pos({0.0f,0.0f})
	, m_TexID(texID)
	, m_VtxID(vtxID)
{
	float backgroundWidth = static_cast<float>(GameLib::Instance().GetWindowWidth());
	float backgroundHeight = static_cast<float>(GameLib::Instance().GetWindowHeight());
	GameLib::Instance().CreateVtx(m_VtxID, backgroundWidth, backgroundHeight);
}


PolicyBackGround::~PolicyBackGround()
{
}

void PolicyBackGround::Draw()
{
	GameLib::Instance().DrawXY(m_TexID, m_VtxID, m_Pos.x, m_Pos.y);
}