#ifndef SPEED_METER_H
#define SPEED_METER_H

#include "GameLib/Lib/Vertex.h"
#include "UI.h"

class SpeedMeter : public UI
{
public:
	SpeedMeter(int bgTexID, int dialTexID, int needleTexID, int meterVtxID);
	virtual ~SpeedMeter();
	virtual void Control();
	virtual void Draw();

private:

	enum METER_ID
	{
		BG,
		DIAL,
		NEEDLE,
		ID_MAX,
	};

	int				m_TexID[ID_MAX];
	int				m_VtxID;
	D3DXVECTOR2		m_NeedlePos;
	float			m_SpeedLimit;
	float			m_CurrentSpeed;
	float			m_SpeedCount;

	void RotationMatrix(CUSTOMVERTEX* vertex);
};

#endif	// SPEED_METER_H
