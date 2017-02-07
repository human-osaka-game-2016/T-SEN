/**
* @file PolicyBackGround.h
* @brief PolicyBackGroundクラスヘッダ
* @author matsuda
*/
#ifndef POLICYBACKGROUND_H
#define POLICYBACKGROUND_H

#include <d3dx9.h>

class PolicyBackGround
{
public:
	PolicyBackGround(int texID, int vtxID);
	~PolicyBackGround();
	void Draw();
private:
	D3DXVECTOR2 m_Pos;              //!< 位置座標
	int					m_TexID;	//!< TextureID
	int					m_VtxID;	//!< VertexID
};
#endif

