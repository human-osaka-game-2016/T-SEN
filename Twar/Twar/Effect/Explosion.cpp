/**
* @file		Explosion.cpp
* @brief	Explosionクラス実装
* @author	haga
*/

//-------------------------------------------------------------------------------------------------------------------------------------//
//includes
//-------------------------------------------------------------------------------------------------------------------------------------//

#include "GameLib/GameLib.h"
#include "Explosion.h"

//-------------------------------------------------------------------------------------------------------------------------------------//
//Namespace
//-------------------------------------------------------------------------------------------------------------------------------------//

/**@todo correctionPosは消す予定**/
namespace
{

const D3DXVECTOR3		correctionPos = {0.0f, 0.0f, 0.0f};			// 座標の補正値(エフェクトの位置を調整用に一応作成)
const int				animeTime = 1;								// アニメ遷移時間
const int				animePattern = 3;							// アニメパターン総数
const float				animeTu = 0.25f;							// アニメで変動するtu値
const float				animeTv = 0.25f;							// アニメで変動するtv値

}

//-------------------------------------------------------------------------------------------------------------------------------------//
//Public functions
//-------------------------------------------------------------------------------------------------------------------------------------//

Explosion::Explosion(D3DXVECTOR3 pos, int texID, int vtxID)
	: Effect(pos, texID, vtxID)
{
}

Explosion::~Explosion()
{
}

bool Explosion::Control()
{
	if(m_AnimeTimeCount == animeTime)
	{
		if(m_AnimePatternCount == animePattern)
		{
			m_IsEnd = true;
		}
		else
		{
			m_AnimePatternCount++;
			GameLib::Instance().SetVtxUV(m_VtxID, 0.0f + (animeTu * m_AnimePatternCount), 0.25f + (animeTu * m_AnimePatternCount), 0.0f, animeTv);
			m_AnimeTimeCount = 0;
		}

	}
	else
	{
		m_AnimeTimeCount++;
	}

	return m_IsEnd;
}

void Explosion::Draw()
{
	GameLib::Instance().GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GameLib::Instance().GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
	GameLib::Instance().GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	GameLib::Instance().GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);

	//GameLib::Instance().GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//GameLib::Instance().GetDevice()->SetRenderState(D3DRS_ALPHAREF, 0);
	//GameLib::Instance().GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	GameLib::Instance().GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	GameLib::Instance().GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	GameLib::Instance().GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	GameLib::Instance().GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	GameLib::Instance().GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	GameLib::Instance().GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	Transform3D();
	GameLib::Instance().Draw3DXYCenterPos(m_TexID, m_VtxID);

	GameLib::Instance().GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GameLib::Instance().GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
	GameLib::Instance().GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	GameLib::Instance().GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	GameLib::Instance().GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	GameLib::Instance().GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	GameLib::Instance().GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	GameLib::Instance().GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	GameLib::Instance().GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	GameLib::Instance().GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	GameLib::Instance().GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}
