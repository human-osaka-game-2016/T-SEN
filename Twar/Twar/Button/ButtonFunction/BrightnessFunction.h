//=================================================================================================================================//
//!< @file		BrightnessFunction.h	
//!< @brief		BrightnessFunctionクラスヘッダ
//!< @author	hagas
//=================================================================================================================================//

#ifndef BRIGHTNESS_FUNCTION_H
#define BRIGHTNESS_FUNCTION_H

#include <d3dx9.h>
#include "ButtonFunction.h"

/**
* ボタンにマウスカーソルがあたっていると明暗処理を行う機能のDecoratorクラス
* @attention  あくまでDecoratorなのでBasicButtonと一緒に使用すること
*/
class BrightnessFunction : public ButtonFunction
{

public:
	/**
	* Constructor
	* @param[in] pButton	Buttonクラスのインスタンスへのポインタ
	* @param brightnessVal  明暗処理のデフォルト値(デフォルト引数 = 0xffa3a3a3)
	*/
	BrightnessFunction(Button* pButton, DWORD brightnessVal = 0xffa3a3a3);

	/**Destructor*/
	virtual ~BrightnessFunction();

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
	const DWORD		m_BrightnessVal;					//!< 明暗処理のデフォルト値 
	DWORD			m_CorrectionBrightnessVal;			//!< 実際に明暗処理する値
};

#endif	// BRIGHTNESS_FUNCTION_H

//================================================================================================================================//
//END OF FILE
//================================================================================================================================//
