//============================================================================================================================//
//!< @file		ButtonFunction.h
//!< @brief		ButtonFunctionクラスヘッダ
//!< @author	haga
//============================================================================================================================//

#ifndef BUTTON_FUNCTION_H
#define BUTTON_FUNCTION_H

#include "../Button.h"

/**
* ボタンに機能を追加するためのDecoratorの基底クラス
*/
class ButtonFunction : public Button
{

public:
	/**
	* Constructor
	* @param[in] pButton	Buttonクラスのインスタンスへのポインタ
	*/
	explicit ButtonFunction(Button* pButton);

	/**Destructor*/
	virtual ~ButtonFunction();

	/**
	* コントロール関数
	* @return マウスカーソルがあたっているかどうか
	*/
	virtual bool Control() = 0;

	/**描画関数*/
	virtual void Draw() = 0;

	/**
	* VertexIDを取得する関数
	* @return VertexID
	*/
	virtual int GetVtxID() = 0;

	/**
	* ボタンの横幅を取得する関数
	* @return ボタンの横幅
	*/
	virtual float GetButtonWidth() = 0;

	/**
	* ボタンの縦幅を取得する関数
	* @return ボタンの縦幅
	*/
	virtual float GetButtonHeight() = 0;

protected:
	Button*		m_pButton;			//!< Buttonクラスのインスタンスへのポインタ

};

#endif	// BUTTON_FUNCTION_H

//============================================================================================================================//
//END OF FILE
//============================================================================================================================//
