/**
* @file		ResultBackground.h		
* @brief	ResultBackgroundクラスヘッダ
* @auhtor	haga
*/

#ifndef RESULT_BACKGROUND_H
#define RESULT_BACKGROUND_H

#include<d3dx9.h>

/**
* 勝敗結果表示クラス
*/
class ResultBackground
{

public:
	/**
	* コンストラクタ
	* @param texID	テクスチャーID
	* @param vtxID	バーテックスID
	*/
	ResultBackground(int texID, int vtxID);

	/**デストラクタ*/
	~ResultBackground();

	/**
	* コントロール関数
	* @return フェードインが終了したかどうか
	*/
	bool Control();

	/**描画関数*/
	void Draw();

	/**フェードイン処理を終了させる*/
	void EndFedeIn();

private:
	D3DXVECTOR2		m_Pos;				//!< 位置座標
	int				m_TexID;			//!< テクスチャーID
	int				m_VtxID;			//!< バーテックスID
	BYTE			m_Alpha;			//!< バーテックスのアルファ値
	bool			m_IsFedeInEnd;		//!< フェードインが終了したかどうか


};

#endif	// RESULT_BACKGROUND_H
