/**
* @file   InputKey.h
* @brief  操作キーに関するクラスのh
* @author haga
*/
#ifndef INPUT_KEY_H
#define INPUT_KEY_H

#include <dinput.h>

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
	KEYMAX
};

/**キー状態*/
enum KEYSTATE
{
	OFF,		//!< キーを離した状態が続いている
	ON,			//!< キーを押した状態が続いている
	RELEASE,	//!< キーを離す
	PUSH		//!< キーを押す
};

/**
* キーに関するクラス
*/
class InputKey
{
private:
	LPDIRECTINPUTDEVICE8  m_pKeyDevice;			//!< キーボードデバイス格納用
	int					  m_PreKey[KEYMAX];		//!< キーの状態格納する変数

public:
	BYTE     m_diks[256];			//!< DIKを格納する変数
	KEYSTATE m_Key[KEYMAX];			//!< キーの種類を格納する変数

	/**コンストラクタ*/
	InputKey();

	/**デストラクタ*/
	~InputKey();

	/**
	* 実体を取得する関数<br>
	* Singletonパターン.
	* @return ControlKey キー操作のオブジェクト
	*/
	static InputKey& GetInstance()
	{
		static InputKey ControlKey;

		return ControlKey;
	}

	/**キーの更新*/
	void UpdateKey();

	/**
	* キーの状態を確認する関数.
	* @param[in] DIK	ダイレクトインプットキー
	* @param[in] st	キー種類
	*/
	void KeyCheck(BYTE* DIK, KEYKIND st);

};

#endif		// INPUT_KEY_H