//==================================================================================================================================//
//!< @file		LifeGauge.h
//!< @brief		LifeGaugeクラスヘッダ
//!< @author	ichikawa
//==================================================================================================================================//

#ifndef LIFE_GAUGE_H
#define LIFE_GAUGE_H

#include "UI.h"
class LifeGauge : public UI
{

public:
	LifeGauge(int lifeTexID, int flameTexID, int decoTexID, int lifeVtxID, int flameVtxID);
	virtual ~LifeGauge();
	virtual void Control();
	virtual void Draw();

private:
	enum LIFE_GAUGE_ID
	{
		LIFE,			//!< ライフID
		FLAME,			//!< 外装
		DECORATION,		//!< 装飾
		ID_MAX,
	};

	D3DXVECTOR2		m_LifePos;
	float			m_LifePosCount;
	float			m_LifeHeight;
	int				m_TexID[LIFE_GAUGE_ID::ID_MAX];
	int				m_VtxID;
	int				m_FlameVtxID;
	float			m_LifeTv;
	float			m_LifeTvCount;
	int				m_LifeMAX;

	int CurrentLife;
	
};

#endif	// LIFE_GAUGE_H

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
