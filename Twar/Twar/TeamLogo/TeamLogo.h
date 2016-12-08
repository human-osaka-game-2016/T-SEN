/**
* @file		TeamLogo.h
* @brief	TeamLogoクラスヘッダ
* @author	ichikawa
*/
#ifndef TEAM_LOGO_H
#define TEAM_LOHO_H

class GameLib;
/**
* チームロゴのクラス
*/
class TeamLogo
{
public:
	enum TEXTURE_ID
	{
		TEAMLOGO_TEX,			//!< タイトル背景
	};

	/**コンストラクタ*/
	TeamLogo();

	/**デストラクタ*/
	~TeamLogo();

	void Contlrol();
	
	void Draw();

	
};
#endif // TEAM_LOGO_H