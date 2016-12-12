/**
* @file		TeamLogo.cpp
* @brief	TeamLogoクラス実装
* @author	ichikawa
*/

#include "GameLib/GameLib.h"
#include "TeamLogo.h"

TeamLogo::TeamLogo() 
	: m_Alpha(0x00)
	, m_LogoState(LOGO_FADE_IN)
	, m_TeamLogoIsEnd(false)
{
	float logoWidth = 1024.f;
	float logoHeight = 512.f;
	posX = 320.f;
	posY = 240.f;
	GameLib::Instance().LoadTex(TEAM_LOGO_TEX, "../Resouce/20141228_111729_foxinfonet.jpg");
	GameLib::Instance().CreateVtx(TeamLogo::TEAM_LOGO_TEX, logoWidth, logoHeight);
}

TeamLogo::~TeamLogo()
{

}

/** コントロール関数*/
bool TeamLogo::Contlrol()
{
	switch(m_LogoState)
	{
	case LOGO_FADE_IN:
		if (m_Alpha < ALPHAMAX){
			m_Alpha += 0x01;
		}
		else
		{
			m_LogoState = LOGO_FADE_OUT;
		}
		break;
	case LOGO_FADE_OUT:
		if (m_Alpha > 0x00)
		{
			m_Alpha -= 0x01;
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
	DWORD color = D3DCOLOR_ARGB(m_Alpha, 0xFF, 0xFF, 0xFF);
	GameLib::Instance().SetVtxColor(TeamLogo::TEAM_LOGO_TEX, color);
	GameLib::Instance().DrawXY(TeamLogo::TEAM_LOGO_TEX, TeamLogo::TEAM_LOGO_TEX, TeamLogo::posX, TeamLogo::posY);
}
