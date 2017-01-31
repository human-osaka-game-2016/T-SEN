//===============================================================================================================================//
//!< @file		ScaleFunction.h
//!< @brief		ScaleFunctionクラスヘッダ
//!< @author	haga
//===============================================================================================================================//

#ifndef SCALE_FUNCTION_H
#define SCALE_FUNCTION_H

#include "ButtonFunction.h"

/**
* ボタンにマウスカーソルがあたっているとスケール処理を行う機能のDecoratorクラス
* @attention  あくまでDecoratorなのでBasicButtonと一緒に使用すること
*/
class ScaleFunction : public ButtonFunction
{

public:
	/**
	* Constructor
	* @param[in] pButton 
	* @param scaleVal スケール処理の変化量(デフォルト引数 = 10.f)
	*/
	ScaleFunction(Button* pButton, float scaleVal = 10.f);

	/**Desutructor*/
	virtual ~ScaleFunction();

	/**
	* コントロール関数
	* @return マウスカーソルがあたっているかどうか
	*/
	virtual bool Control()override;

	/**描画関数*/
	virtual void Draw()override;

	/**
	* VertexIDを取得する関数
	* @return VertexID
	*/
	virtual int GetVtxID()override{ return m_pButton->GetVtxID(); };

	/**
	* ボタンの横幅を取得する関数
	* @return ボタンの横幅
	*/
	virtual float GetButtonWidth()override{ return m_pButton->GetButtonWidth(); };

	/**
	* ボタンの縦幅を取得する関数
	* @return ボタンの縦幅
	*/
	virtual float GetButtonHeight()override{ return m_pButton->GetButtonHeight(); };


private:
	const float		m_ScaleVal;					//!< スケール処理の変化量
	float			m_CorrectionScaleVal;		//!< 実際にスケール処理に用いる補正値

};

#endif	// SCALE_FUNCTION_H

//==============================================================================================================================//
//END OF FILE
//==============================================================================================================================//
