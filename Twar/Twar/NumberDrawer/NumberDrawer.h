//==================================================================================================================================//
//!< @file		NumberDrawer.h
//!< @brief		NumberDrawerクラスヘッダ
//!< @author	haga
//==================================================================================================================================//
 
#ifndef NUMBER_DRAWER_H
#define NUMBER_DRAWER_H

#include <d3dx9.h>

/**
* 数字を描画だけを行うクラス
*/
class NumberDrawer
{

public:
	/**
	* Constructor
	* @param texID TextureID
	* @param vtxID VertexID
	*/
	NumberDrawer(int texID, int vtxID);

	/**Destructor*/
	~NumberDrawer();

	/**
	* 描画関数
	* @param rPos 描画したい座標
	* @param num  描画したい数字の種類
	*/
	void Draw(const D3DXVECTOR2 rPos, int num);

private:
	int		m_TexID;		//!< TextureID
	int		m_VtxID;		//!< VertexID

};

#endif	// NUMBER_DRAWER_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
