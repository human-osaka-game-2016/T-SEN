/**
* @file		Radar.h
* @brief	Radarクラスヘッダ
* @author	haga
*/

#ifndef RADAR_H
#define RADAR_H

#include "vector"
#include "d3dx9.h"

/**
* バトルにおけるオブジェクトの位置を把握しているクラス
* 索敵も行ってくれる
*/
class Radar
{
public:
	static Radar& Instance()
	{
		static Radar radar;
		return radar;
	}

	D3DXVECTOR3 GetNearShipPos(const D3DXVECTOR3& rPos);

	D3DXVECTOR3 GetMonsterPos(){ return m_MonsterPos; }

	void SetShipPos(const D3DXVECTOR3& rPos);

	void SetMonsterPos(const D3DXVECTOR3& rPos);

	void ClearData();
	
	~Radar();

private:

	Radar();
	struct ComparisionData
	{
		D3DXVECTOR3 pos;
		float length;
	};

	std::vector<D3DXVECTOR3>	m_ShipPos;
	D3DXVECTOR3					m_MonsterPos;

	static bool CompareLength(const ComparisionData& rLeft, const ComparisionData& rRight);

};

#endif	// RADAR_H
