/**
* @file		TeamLogo.cpp
* @brief	TeamLogoクラス実装
* @author
*/
#include "GameLib/GameLib.h"
#include "TeamLogo.h"


TeamLogo::TeamLogo()

{
	GameLib::Instance().LoadTex(1, "狐.jpg");
}

TeamLogo::~TeamLogo()
{

}

/** コントロール関数*/
void TeamLogo::Contlrol()
{
	//GameLib::SetVtxColor(1, )
}

void TeamLogo::Draw()
{
	GameLib::Instance().DrawXY(1, 1, 400, 225);
}