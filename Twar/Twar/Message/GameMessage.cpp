/**
* @file		GameMessage.cpp
* @brief	GameMessageクラス実装
* @auhtor	haga
*/

//-------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include "GameMessage.h"
#include "GameLib/GameLib.h"
#include "Font/Font.h"

//-------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//-------------------------------------------------------------------------------------------------------------------------------------//

GameMessage::GameMessage(const D3DXVECTOR2& rPos, const std::string& rText, INT scale)
	: m_Pos(rPos)
	, m_Text(rText)
	, m_pFont(new Font(GameLib::Instance().GetDevice(), scale, scale))
{
}

GameMessage::~GameMessage()
{
	delete m_pFont;
}

void GameMessage::Draw()
{
	m_pFont->Draw(m_Text.c_str(), m_Pos);
}
