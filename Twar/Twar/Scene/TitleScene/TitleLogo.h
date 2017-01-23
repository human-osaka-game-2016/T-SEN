/**
* @file		TitleLogo.h
* @brief	TitleLogoクラスヘッダ
* @author	haga
* @todo		2016/11/24ファイル作成のみ。実装は後で行う
*/

#ifndef TITLE_LOGO_H
#define TITLE_LOGO_H

/**
* タイトルロゴを管理するクラス.
*/
class TitleLogo
{
public:
	/**コンストラクタ*/
	TitleLogo();

	/**デストラクタ*/
	~TitleLogo();

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();

private:
	float			   m_PosX;				//!< タイトルロゴのx座標
	float			   m_PosY;				//!< タイトルロゴのy座標

};

#endif	// TITLE_LOGO_H
