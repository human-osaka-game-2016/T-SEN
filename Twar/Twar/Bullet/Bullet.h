/**
* @file Bullet.h
* @brief Bulletクラスヘッダ
* @author Matsuda
*/
#ifndef BULLET_H
#define BULLET_H

#include <d3dx9.h>

class FbxModel;

/**
*Bulletクラス
*/
class Bullet
{
	friend class BulletManager;

protected:
	struct Data
	{
		D3DXVECTOR3 BulletPos;
		float Rotate;
		bool hasDrawn;
		bool hasInited;
		Data* pBefore;
		Data* pNext;
		D3DXMATRIX Matrix;
	};
	Data* m_pFirst;
	Data* m_pLast;
	Data m_Data;
	D3DXMATRIX m_Rotation;
public:
	/**コンストラクタ*/
	Bullet();

	/**デストラクタ*/
	virtual ~Bullet();

	/**コントロール関数*/
	virtual void Control(D3DXVECTOR3 Pos, float Rotate);
	
	/**描画関数*/
	virtual void Draw();
	
	/**最後尾につける関数*/
	virtual void PushBack(Data* pData);
	
	/**今あるポインターを削除して次のポインターを返す*/
	virtual Data* EraseNext(Data* pData);
	
	/**リストを空にする関数*/
	virtual void Clear();

protected:
	FbxModel* m_pFbx; //!<  モデルデータ

};
#endif  //BULLET_H
