/**
* @file  FieldManager.h
* @brief FieldManagerクラス実装
* @author Matsuda
*/
#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H

#include"Ocean.h"
#include"Sky.h"

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
	Ocean*   m_Ocean;
	Sky*     m_Sky;
};
#endif//FIELDMANAGER_H

