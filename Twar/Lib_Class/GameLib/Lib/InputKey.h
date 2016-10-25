/**
* @file   InputKey.h
* @brief  操作キーに関するクラスのh
* @author haga
*/
#ifndef INPUT_KEY_H
#define INPUT_KEY_H


#include <dinput.h>
#include "InputDevice.h"

/**キー種類*/
enum  KEYKIND
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	ESCAPE,
	SHIFT,
	SPACE,
	TAB,
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	KEYMAX,
};



/**
* キーに関するクラス
*/
class InputKey
{
private:
	LPDIRECTINPUTDEVICE8  m_pKeyDevice;			//!< キーボードデバイス格納用
	int					  m_PreKey[KEYMAX];		//!< キーの状態格納する変数

	/**
	* 状態を確認する関数.
	* @param[in] DIK	ダイレクトインプットキー
	* @param[in] st	キー種類
	*/
	void CheckState(BYTE* DIK, KEYKIND st);

public:
	BYTE     m_diks[256];			//!< DIKを格納する変数
	BTN_STATE m_Key[KEYMAX];			//!< キーの種類を格納する変数

	/**コンストラクタ*/
	InputKey();

	/**デストラクタ*/
	~InputKey();

	/**キーの更新*/
	void UpdateKey();

	/**
	* キー状態確認関数
	* @param[in] DIK	ダイレクトインプットキーID
 	* @param[in] st		キーの種類
	*/
	BTN_STATE CheckKey(int DIK, KEYKIND st);
};

#endif		// INPUT_KEY_H