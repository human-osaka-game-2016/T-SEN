/**
* @file		TeamLogo.cpp
* @brief	TeamLogoクラス実装
* @author	ichikawa
*/

#include "GameLib/GameLib.h"
#include "TeamLogo.h"

TeamLogo::TeamLogo() 
	: m_alpha(0x00)
	, m_LogoState(LOGOFADE_IN)
	, m_TeamLogoIsEnd(false)
{
	float logoWidth = 1024.f;
	float logoHeight = 512.f;
	GameLib::Instance().LoadTex(TEAMLOGO_TEX, "../Resouce/20141228_111729_foxinfonet.jpg");
	GameLib::Instance().CreateVtx(TeamLogo::TEAMLOGO_TEX, logoWidth, logoHeight);
}

TeamLogo::~TeamLogo()
{

}

/** コントロール関数*/
bool TeamLogo::Contlrol()
{
	switch(m_LogoState)
	{
	case LOGOFADE_IN:
		if (m_alpha < ALPHAMAX){
			m_alpha += 0x01;
		}
		else
		{
			m_LogoState = LOGOFADE_OUT;
		}
		break;
	case LOGOFADE_OUT:
		if (m_alpha > 0x00)
		{
			m_alpha -= 0x01;
		}
		else
		{
			m_TeamLogoIsEnd = true;
		}
			break;
	}

	return m_TeamLogoIsEnd;
}

void TeamLogo::Draw()
{
	DWORD color = D3DCOLOR_ARGB(m_alpha, 0xFF, 0xFF, 0xFF);
	GameLib::Instance().SetVtxColor(TeamLogo::TEAMLOGO_TEX, color);
	GameLib::Instance().DrawXY(TeamLogo::TEAMLOGO_TEX, TeamLogo::TEAMLOGO_TEX, 320, 200);
}
