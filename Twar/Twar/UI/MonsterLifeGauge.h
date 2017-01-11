#ifndef MONSTER_LIFE_GAUGE_H
#define MONSTER_LIFE_GAUGE_H

#include "GameLib/Lib/Vertex.h"
#include "UI.h"

class MonsterLifeGauge :public UI
{

public:
	MonsterLifeGauge(int lifeTexID, int flameTexID);
	virtual ~MonsterLifeGauge();
	virtual void Control();
	virtual void Draw();

private:
	enum LIFE_GAUGE_ID
	{
		LIFE,			//!< ライフID
		FLAME,			//!< 外装
		ID_MAX,
	};

	D3DXVECTOR2		m_LifePos;
	float			m_LifePosCount;
	float			m_LifeHeight;
	int				m_TexID[LIFE_GAUGE_ID::ID_MAX];
	float			m_LifeTv;
	float			m_LifeTvCount;
	int				m_LifeMAX;

	int				m_CurrentLife;

	void RotationMatrix(CUSTOMVERTEX* vertex);
};


#endif	// MONSTER_LIFE_GAUGE_H
