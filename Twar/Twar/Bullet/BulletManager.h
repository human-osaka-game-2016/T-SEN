/**
* @file BulletManager.h
* @brief BulletManagerクラスヘッダ
* @author Matsuda
*/
#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

class ApBullet;
class Bullet;
class FbxRelated;
/**
*BulletManagerクラス
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

	/**コンストラクタ*/
	BulletManager();
	
	/**デストラクタ*/
	~BulletManager();
	
	/**コントロール関数*/
	void Control(D3DXVECTOR3 Pos, float Rotate);
	
	/**描画関数*/
	void Draw();
	
	/**Bullet生成関数*/
	void Creat(char* pCount, BULLET_ID* pBulletID);

private:
	ApBullet* m_pAPBullet;
	FbxRelated m_APBullet;
	std::vector<Bullet*> m_Bullet;
	char m_BulletCount;
	int m_BulletNumber;
};
#endif //BULLETMANAGER_H

