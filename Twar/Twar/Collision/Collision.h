#ifndef COLLISION_H
#define COLLISION_H

#include <d3dx9.h>

class Collision
{
public:
	enum CollisionID
	{
		MONSTER,
		SHIP,

	};

	Collision(float radius);

	~Collision();

	void SetData(const D3DXVECTOR3& pos);

	void CheckState();

	bool InformCollision();

	D3DXVECTOR3 GetPos(){ return m_Pos; }

	float		GetRadius(){ return m_Radius; }

private:
	D3DXVECTOR3		m_Pos;			//!< 座標
	float			m_Radius;		//!< 半径
	bool			m_IsExist;			//!< 衝突したかどうか

};

#endif // COLLISION_H
