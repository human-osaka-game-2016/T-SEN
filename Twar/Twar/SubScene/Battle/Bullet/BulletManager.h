/**
* @file BulletManager.h
* @brief BulletManager�N���X�w�b�_
* @author Matsuda
*/
#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include <vector>

class ApBullet;
class Bullet;
class FbxRelated;
/**
*BulletManager�N���X
*/
class BulletManager
{
	friend class Bullet;

public:
	enum BULLET_ID
	{
		APBULLET,
		HEBULLET,
		TORPEDO,
	};

	/**�R���X�g���N�^*/
	BulletManager();
	
	/**�f�X�g���N�^*/
	~BulletManager();
	
	/**�R���g���[���֐�*/
	void Control(D3DXVECTOR3 Pos, float Rotate);
	
	/**�`��֐�*/
	void Draw();
	
	/**Bullet�����֐�*/
	void Create(char* pCount, BULLET_ID* pBulletID);

private:
	ApBullet*		m_pAPBullet;
	FbxRelated*		m_pAPBulletModel;
	std::vector<Bullet*> m_Bullet;
	char m_BulletCount;
	int m_BulletNumber;
};
#endif //BULLETMANAGER_H

