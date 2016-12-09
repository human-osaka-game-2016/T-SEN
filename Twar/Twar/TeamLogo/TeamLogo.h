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
		TEAMLOGO_TEX,			//!< タイトル背景
	};

	/**コンストラクタ*/
	TeamLogo();

	/**デストラクタ*/
	~TeamLogo();

	bool Contlrol();
	
	void Draw();


	enum LOGOSTATE
	{
		LOGOFADE_IN,			//!<フェードイン
		LOGOFADE_OUT,			//!<フェードアウト
	};
	LOGOSTATE		m_LogoState;

	BYTE m_alpha;
	
	bool m_TeamLogoIsEnd;		//!< 
};
#endif // TEAM_LOGO_H
