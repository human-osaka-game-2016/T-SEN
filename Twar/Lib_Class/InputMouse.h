/**
* @file   InputMouse.h
* @brief  マウス操作に関するクラス
* @author haga
*/
#ifndef INPUT_MOUSE_H
#define INPUT_MOUSE_H

#include <dinput.h>
#include <d3dx9.h>

/**
* マウス操作に関するクラス
*/
class InputMouse
{
private:
	HWND				 m_hWnd;			//!< ウィンドウハンドル格納
	LPDIRECTINPUTDEVICE8 m_pMouseDevice;	//!< マウスデバイス
	DIMOUSESTATE2		 m_dims;			//!< マウス構造体(ボタン関連)
	INT					 m_wndWid;			//!< ウインドウサイズ幅
	INT					 m_wndHgt;			//!< ウィンドドウサイズ高さ
	LONG				 m_posX;			//!< マウスのx座標
	LONG				 m_posY;			//!< マウスのy座標
	LONG				 m_wheel;			//!< マウスのホイール
	bool				 m_LDown;			//!< Update時点の左ボタン状態
	bool				 m_RDown;			//!< Update時点の右ボタン状態
	bool				 m_MDown;			//!< Update時点の中ボタン状態
	bool				 m_LAction;			//!< ボタン押した直後だけONになる(クリックを拾うときに)
	bool				 m_RAction;			//!< ボタン押した直後だけONになる(クリックを拾うときに)
	bool				 m_MAction;			//!< ボタン押した直後だけONになる(クリックを拾うときに)

public:
	/**コンストラクタ*/
	InputMouse();
	/**デストラクタ*/
	~InputMouse();

	/**マウスホイールの状態*/
	enum WHEEL_STATE
	{
		WHEEL_NONE = 0,		//!< 回転していない
		WHEEL_UP = 1,		//!< 奥に回転させている状態
		WHEEL_DOWN = -1,	//!< 手前に回転させている状態
	};

	/**マウスの更新*/
	void UpdateMouse();

	/**マウス座標を取得する*/
	LONG GetPosX() const { return m_posX; }
	LONG GetPosY() const { return m_posY; }
	LONG GetWheel() const { return m_wheel; }

	/**状態確認*/
	bool GetIsLAction() const { return m_LAction; }
	bool GetIsRAction() const { return m_RAction; }
	bool GetIsMAction() const { return m_MAction; }

	/**
	* マウスの座標をセット.
	* @param[in] x 座標x
	* @param[in] y 座標y
	*/
	void SetCursorPos(int x, int y)
	{
		m_posX = x;
		m_posY = y;
	}
};

#endif // INPUT_MOUSE_H