/**
* @file		TeamLogo.h
* @brief	TeamLogoクラスヘッダ
* @author	ichikawa
*/
#ifndef TEAM_LOGO_H
#define TEAM_LOHO_H

#include <d3dx9.h>

#define ALPHAMAX 0xFF
/**
* チームロゴのクラス
*/
class TeamLogo
{
public:
	enum TEXTURE_ID
	{
		TEAM_LOGO_TEX,			//!< タイトル背景
	};

	enum LOGOSTATE
	{
		LOGO_FADE_IN,			//!<フェードイン
		LOGO_FADE_OUT,			//!<フェードアウト
	};

	/**コンストラクタ*/
	TeamLogo();

	/**デストラクタ*/
	~TeamLogo();

	bool Contlrol();
	
	void Draw();


private:
	LOGOSTATE		m_LogoState;		//!<ロゴステイト

	BYTE m_Alpha;						//!<α値を変動する変数
	
	bool m_TeamLogoIsEnd;				//!<ロゴシーンの終了を見る変数

	float posX;
	float posY;
};
#endif // TEAM_LOGO_H
