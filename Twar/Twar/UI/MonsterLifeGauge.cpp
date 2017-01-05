
//--------------------------------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "MonsterLifeGauge.h"

//--------------------------------------------------------------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------------------------------------------------------------//

namespace
{

const D3DXVECTOR2	Pos = { 1200.f, 50.f}; 
const float			LifePosX = 1200.f;
const float			VtxHeight = 600.f;
const float			VtxWidth = 50.f;

}

//--------------------------------------------------------------------------------------------------------------------------------------//
//public functions
//--------------------------------------------------------------------------------------------------------------------------------------//

MonsterLifeGauge::MonsterLifeGauge(int lifeTexID, int flameTexID)
	: m_LifeTv(0.0f)
	, m_LifeHeight(VtxHeight)
{
	m_Angle = 90.f;
	m_LifeMAX = 10;
	CurrentLife = m_LifeMAX;
	m_LifeTvCount = 1.0f / m_LifeMAX;
	m_LifePos = Pos;
	m_LifePosCount = VtxHeight / m_LifeMAX;
	m_Pos = Pos;
	m_TexID[LIFE] = lifeTexID;
	m_TexID[FLAME] = flameTexID;
}

MonsterLifeGauge::~MonsterLifeGauge()
{
}

void MonsterLifeGauge::Control()
{
	if(GameLib::Instance().CheckKey(DIK_K, K) == ON)
	{
		if(m_LifeMAX != 0)
		{
			CurrentLife -= 1;
			m_LifeTv += (m_LifeMAX - CurrentLife) * m_LifeTvCount;
			m_LifePos.x -= ((m_LifeMAX - CurrentLife) * m_LifePosCount) / 2.0f;
			m_LifeHeight -= (m_LifeMAX - CurrentLife) * m_LifePosCount;
			m_LifeMAX = CurrentLife;
		}
	}
}

void MonsterLifeGauge::Draw()
{
	CUSTOMVERTEX life[] =
	{
		{ -VtxWidth / 2.0f, -m_LifeHeight / 2.0f, 0.0f, 1.0f, 0xFFFF0000, 0.0f, m_LifeTv },
		{ VtxWidth / 2.0f, -m_LifeHeight / 2.0f, 0.0f, 1.0f, 0xFFFF0000, 1.0f, m_LifeTv },
		{ VtxWidth / 2.0f, m_LifeHeight / 2.0f, 0.0f, 1.0f, 0xFFFF0000, 1.0f, 1.0f },
		{ -VtxWidth / 2.0f, m_LifeHeight / 2.0f, 0.0f, 1.0f, 0xFFFF0000, 0.0f, 1.0f },
	};

	RotationMatrix(life);

	for(char i = 0; i < 4; ++i)
	{
		life[i].x += m_LifePos.x;
		life[i].y += m_LifePos.y;
	}

	GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID[LIFE]));
	GameLib::Instance().GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, life, sizeof(CUSTOMVERTEX));

	CUSTOMVERTEX lifeFlame[] =
	{
		{ -VtxWidth / 2.0f, -VtxHeight / 2.0f, 0.0f, 1.0f, 0xFFFFFFFF, 0.0f, 0.0f },
		{ VtxWidth / 2.0f, -VtxHeight / 2.0f, 0.0f, 1.0f, 0xFFFFFFFF, 1.0f, 0.0f },
		{ VtxWidth / 2.0f, VtxHeight / 2.0f, 0.0f, 1.0f, 0xFFFFFFFF, 1.0f, 1.0f },
		{ -VtxWidth / 2.0f, VtxHeight / 2.0f, 0.0f, 1.0f, 0xFFFFFFFF, 0.0f, 1.0f },
	};

	RotationMatrix(lifeFlame);

	for(char i = 0; i < 4; ++i)
	{
		lifeFlame[i].x += m_Pos.x;
		lifeFlame[i].y += m_Pos.y;
	}

	GameLib::Instance().GetDevice()->SetTexture(0, GameLib::Instance().GetTexture(m_TexID[FLAME]));
	GameLib::Instance().GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, lifeFlame, sizeof(CUSTOMVERTEX));
}

//---------------------------------------------------------------------------------------------------------------------------------------//
//Private functions
//---------------------------------------------------------------------------------------------------------------------------------------//

//行列を使用した回転関数（+だと右回転、-だと左回転)
void  MonsterLifeGauge::RotationMatrix(CUSTOMVERTEX* vertex)
{
	D3DXMATRIX PosMatrix;		// 頂点行列
	D3DXMATRIX RotateMatrix;	// 回転行列

	float cx = 0.0f;		//中心座標のx座標を格納する変数
	float cy = 0.0f;		//変形したy座標を一時的に保持するための変数

	//画像の中心座標を求める
	cx = (vertex[2].x - vertex[0].x) / 2.0f + vertex[0].x;
	cy = (vertex[2].y - vertex[0].y) / 2.0f + vertex[0].y;

	// 行列の初期化（単位行列生成）
	D3DXMatrixIdentity(&PosMatrix);
	D3DXMatrixIdentity(&RotateMatrix);

	D3DXMatrixRotationZ(&RotateMatrix, D3DXToRadian(m_Angle));

	// 回転処理
	for(int i = 0; i<4; i++)
	{
		// 現在の頂点座標を格納
		D3DXMatrixTranslation(&PosMatrix, vertex[i].x, vertex[i].y, vertex[i].z);
		// 回転
		PosMatrix *= RotateMatrix;
		// 結果を戻す
		vertex[i].x = PosMatrix._41;
		vertex[i].y = PosMatrix._42;
		vertex[i].z = PosMatrix._43;
	}
}
