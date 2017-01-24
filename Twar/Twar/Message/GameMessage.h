/**
* @file		GameMessage.h
* @brief	GameMessageクラスヘッダ
* @auhtor	haga
*/

#ifndef GAME_MESSAGE_H
#define GAME_MESSAGE_H

#include <string>
#include <d3dx9.h>

class Font;

/**
* ゲーム画面にメッセージを表示するクラス
* @todo 現状はDirectFontで表示する仕組み
*/
class GameMessage
{

public:
	/**
	* コンストラクタ
	* @param rPos	座標
	* @param tText	テキスト 
	* @param scale	文字の大きさ
	*/
	GameMessage(const D3DXVECTOR2& rPos, const std::string& rText, INT scale = 20);

	/**デストラクタ*/
	~GameMessage();

	/**描画関数*/
	void Draw();

private:
	D3DXVECTOR2			m_Pos;			//!< 位置座標
	std::string			m_Text;			//!< 表示するテキスト
	Font*				m_pFont;		//!< Fontクラスのインスタンスへのポインタ


};

#endif	// GAME_MESSAGE_H

