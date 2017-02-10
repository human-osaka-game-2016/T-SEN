/**
* @file APBullet.h
* @brief APBulletクラスヘッダ
* @author Matsuda
*/
#ifndef APBULLET_H
#define APBULLET_H

#include "Bullet.h"
#include "fbx/FbxRelated.h"

class ApBullet :public Bullet
{
public:
	/**コンストラクタ関数*/
	ApBullet(FbxModel*	pModel, const D3DXVECTOR3& rPos, float angle, D3DXVECTOR3* vec);

	/**デストラクタ関数*/

	virtual ~ApBullet();
	
	/**
	*コントロール関数
	*@param Pos     渡したい座標
	*@param Rotate　渡したい角度
	*/
	virtual bool Control();
	
	/**描画関数*/
	virtual void Draw();
	
	/**最後尾につける関数*/
	//virtual void PushBack(Data* pdata);
	//
	///**今のポインターを削除して次のポインターを渡す関数*/
	//virtual Data* EraseNext(Data* pdata);
	//
	///**リストを空にする関数*/
	//virtual void Clear();

private:
	FbxRelated m_APBullet;
};
#endif //APBULLET_H
