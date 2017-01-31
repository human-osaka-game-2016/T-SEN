//==================================================================================================================================//
//!< @file		HomeBackground.h
//!< @brief		HomeBackgroundクラスヘッダ
//!< @author	haga
//==================================================================================================================================//

#ifndef HOME_BACKGROUND_H
#define HOME_BACKGROUND_H

#include <d3dx9.h>

/**
* Homeシーン(鎮守府)の背景を描画するクラス
*/
class HomeBackground
{

public:
	/**
	* Constructor
	* @param texID	TextureID
	* @param vtxID	VertexID
	*/
	HomeBackground(int texID, int vtxID);

	/**Destructor*/
	~HomeBackground();

	/**描画関数*/
	void Draw();

private:
	D3DXVECTOR2			m_Pos;		//!< 位置座標
	int					m_TexID;	//!< TextureID
	int					m_VtxID;	//!< VertexID

};

#endif	// HOME_BACKGROUND_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
