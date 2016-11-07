/**
* @file  FieldManager.h
* @brief フィールドを管理するFieldManagerのh
* @author Matsuda
*/

#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H

#include"Ocene.h"
#include"Sky.h"

class FieldManager
{
private:
	Ocene*   m_Ocene;
	Sky*     m_Sky;

public:
	/**コンストラクタ*/
	FieldManager();

	/**デストラクタ*/
	~FieldManager();

	/**コントロール関数*/
	void Control();

	/**描画関数*/
	void Draw();
};
#endif
