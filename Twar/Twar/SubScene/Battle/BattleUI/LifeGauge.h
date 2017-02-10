/**
* @file LifeGauge.h
* @brief LifeGaugeのクラスヘッダ
* @author ichikawa
*/

#ifndef LIFE_GAUGE_H
#define LIFE_GAUGE_H

#include "UI.h"
class LifeGauge : public UI
{
public:
	LifeGauge(int lifeTexID, int lifeVtxID, int flameVtxID, int MosterflameID);
	virtual ~LifeGauge();
	virtual void Control();
	virtual void Draw();

private:
	enum LIFE_GAUGE_ID
	{
		LIFE,				//!< ライフID
		UI,					//!< UIの統合ファイル
		ID_MAX,
	};

	D3DXVECTOR2		m_LifePos;
	D3DXVECTOR2     m_LifePosID;

	float			m_LifePosCount;
	float			m_LifeHeight;
	int				m_TexID[LIFE_GAUGE_ID::ID_MAX];
	int				m_VtxID;
	int				m_FlameVtxID;
	int				m_MonsterFlameID;
	int				m_FlameBaseID;
	float			m_LifeTv;
	float			m_LifeTu;
	float			m_LifeTvCount;
	int				m_LifeMAX;

	int CurrentLife;

};

#endif	//LIFE_GAUGE_H
