/**
* @file FieldManager.h
* @brief FieldManagerクラスヘッダ
* @author Matsuda
*/
#ifndef FIELD_MANAGER_H
#define FIELD_MANAGER_H

#include"Ocean.h"
#include"Sky.h"

/**
*FieldManagerクラス
*/
class FieldManager
{
public:
	/**コンストラクタ*/
	FieldManager();

	/**デストラクタ*/
	~FieldManager();

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();

private:
	Ocean*   m_pOcean;
	Sky*     m_pSky;
};
#endif//FIELDMANAGER_H

