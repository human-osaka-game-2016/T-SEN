#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include <vector>

class Collision;

class CollisionManager
{
public:

	static CollisionManager& Instance()
	{
		static CollisionManager collisionManager;

		return collisionManager;
	}

	~CollisionManager();

	// データセット
	void SetCollision(Collision* collision);

	// 衝突チェック
	void CheckCollision();

	// データクリア
	void ClearData();


private:
	std::vector<Collision*>		m_Collision;
	CollisionManager();
	CollisionManager(const CollisionManager& o) = delete;

};

#endif	// COLLISION_MANAGER_H

