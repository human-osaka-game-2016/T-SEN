/**
* @file MnsterLifeGauge.h
* @brief MnsterLifeGaugeのクラスヘッダ
* @author ichikawa
*/

#ifndef MONSTER_LIFE_GAUGE_H
#define MONSTER_LIFE_GAUGE_H

#include "GameLib/Lib/Vertex.h"
#include "UI.h"

class MonsterLifeGauge :public UI
{

public:
	MonsterLifeGauge(int lifeTexID, int LifeVtrID, int FlameVtrID);
	virtual ~MonsterLifeGauge();
	virtual void Control();
	virtual void Draw();

private:
	enum LIFE_GAUGE_ID
	{
		//LIFE,			//!< ライフID
		//FLAME,			//!< 外装
		UI,				//!< UI
		ID_MAX,
	};

	D3DXVECTOR2		m_LifePos;
	D3DXVECTOR2		m_LifeFlamePos;
	float			m_LifePosCount;
	float			m_LifeHeight;
	float			m_LifeWide;
	float			m_LifeTv;
	float			m_LifeTu;
	float			m_LifeTvCount;
	float			m_LifeID;
	float			m_LifeFlameID;
	float			m_LifeBaseID;
	int				m_LifeMAX;
	int				m_CurrentLife;
	int				m_TexID[LIFE_GAUGE_ID::ID_MAX];
	//void RotationMatrix(CUSTOMVERTEX* vertex);
};


#endif	// MONSTER_LIFE_GAUGE_H
