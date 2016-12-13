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

	enum LOGO_STATE
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
	LOGO_STATE		m_LogoState;		//!<ロゴステイト

	BYTE m_Alpha;						//!<α値を変動する変数
	
	bool m_IsEnd;				//!<ロゴシーンの終了を見る変数

	float m_PosX;						//!<Xの座標情報
	float m_PosY;						//!<Yの座標情報
};
#endif // TEAM_LOGO_H
