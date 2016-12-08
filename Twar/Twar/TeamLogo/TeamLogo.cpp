/**
* @file		TeamLogo.cpp
* @brief	TeamLogoクラス実装
* @author
*/
#include "GameLib/GameLib.h"
#include "TeamLogo.h"


TeamLogo::TeamLogo()

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
void TeamLogo::Contlrol()
{
	
}

void TeamLogo::Draw()
{
	GameLib::Instance().DrawXY(TeamLogo::TEAMLOGO_TEX, TeamLogo::TEAMLOGO_TEX, 320, 200);
}