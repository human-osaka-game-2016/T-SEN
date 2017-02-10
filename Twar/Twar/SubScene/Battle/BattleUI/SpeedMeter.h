/**
* @file SpeedMeter.h
* @brief SpeedMeterのクラスヘッダ
* @author ichikawa
*/

#ifndef SPEED_METER_H
#define SPEED_METER_H

#include "GameLib/Lib/Vertex.h"
#include "UI.h"

class SpeedMeter : public UI
{
public:
	/*======================================旧基準=====================================
	SpeedMeter(int bgTexID, int dialTexID, int needleTexID, int meterVtxID);
	=======================================ここまで==================================*/
	SpeedMeter(int aiconTexID, int meterVtxID, int MeaterID);
	virtual ~SpeedMeter();
	virtual void Control();
	virtual void Draw();

private:

	enum METER_ID
	{
		UI,
		ID_MAX,

	};

	int				m_TexID[ID_MAX];
	int				m_AICON_ID;
	int				m_SpeedMeterID;
	D3DXVECTOR2		m_SpeedMeterPos;
	D3DXVECTOR2		m_AiconPos;
	CUSTOMVERTEX	aicon[4];
	CUSTOMVERTEX	speedmeter[4];
	float			m_SpeedLimit;
	float			m_CurrentSpeed;
	float			m_SpeedCount;
	float			m_PosY;
};

#endif	// SPEED_METER_H
