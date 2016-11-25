/**
* @file		TitleLogo.cpp
* @brief	TitleLogoクラス実装
* @author	haga
*/
#include "GameLib/GameLib.h"
#include "TitleCommonDeclaration.h"
#include "TitleLogo.h"

// ロゴの大きさ
const float TitleLogo::m_LogoWidth = 800.f;
const float TitleLogo::m_LogoHeight = 100.f;

TitleLogo::TitleLogo()
	: m_PosX(0.0f)
	, m_PosY(0.0f)
{
	GameLib::Instance().CreateVtx(title_scene::LOGO, m_LogoWidth, m_LogoHeight);
}

TitleLogo::~TitleLogo()
{
}


void TitleLogo::Control()
{
	/**@todo	光るエフェクトなどが決まっていないので、決まり次第実装*/
}

void TitleLogo::Draw()
{
	GameLib::Instance().DrawXYCenterPos(title_scene::TITLE_LOGO,title_scene::LOGO,);
}
