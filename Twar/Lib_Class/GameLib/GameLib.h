/**
* @file GameLib.h
* @brief  Facadeパターンのライブラリ
* @author haga
*/
#ifndef GAMELIB_H
#define GAMELIB_H

#include <windows.h>
#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include "Lib/InputKey.h"

class WindowCreator;
class GraphicsDevice;
class InputDevice;
class InputMouse;
class TextureManager;
class XFileManager;
class SoundFileManager;
class VertexManager;
class DebugFont;
class DebugTimer;


#define DIRECT3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//!< 頂点フォーマット
#define USER_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)					//!< 頂点フォーマット(XYZと法線とテクスチャー)

/**DirectInputにおけるボタンの状態*/
enum BUTTON_STATE
{
	ON,				//!< キーを押した状態が続いている
	OFF,			//!< キーを離した状態が続いている
	PUSH,			//!< キーを押す
	RELEASE			//!< キーを離す
};

/**ホイールの状態*/
enum WHEEL_STATE
{
	ROLL_NONE,		//!< 回転していない
	ROLL_UP,		//!< 奥に回転させている状態
	ROLL_DOWN,		//!< 手前に回転させている状態
};

/**音楽の再生方法*/
enum SOUND_OPERATION
{
	SOUND_PLAY,			//!< 再生
	SOUND_STOP,			//!< 停止
	SOUND_LOOP,			//!< ループ再生
	SOUND_RESET, 		//!< 初期位置に戻す
	SOUND_RESET_PLAY,   //!< 停めて初期位置戻す
	SOUND_STOP_RESET	//!< 初期位置から再生し直す
};

/**
* ライブラリのクラス	
*/
class GameLib
{
private:
	/**
	* コンストラクタ.
	* Singltonパターンなのでprivate
	*/
	GameLib();

public:
	
	/**デストラクタ*/
	~GameLib();

	/** 
 	* GameLibの実体を取得する関数<br>
	* Singletonパターン.
	* @return GameLibクラス
	*/
	static GameLib& GetInstance()
	{
		static GameLib gameLib;
		return gameLib;
	}

	/**
	* 初期化関数.
	* @param[in] title  ウィンドウタイトル
	* @param[in] width  ウィンドウの横幅
	* @param[in] height ウインドウの縦幅
	* @param[in] Wndproc	ウィンドウプロシージャ関数
	* @param[in] windowType ウィンドウタイプ trueなら通常,falseならフルスクリーン
	*/
	void InitGameLib(TCHAR*  title, int width, int height, LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM), bool windowType);

	/**メモリ開放関数*/
	void ReleaseGameLib();

	/**ウィンドウをフルスクリーンかウィンドウサイズに変える関数*/
	void ChangeWindowMode();			

	/**ウィンドウの横幅を取得する関数*/
	int GetWindowWidth();

	/**ウィンドウの縦幅を取得する関数*/
	int GetWindowHeight();

	//------------------------------------------------------------------------------------
	//									描画関連関数
	//------------------------------------------------------------------------------------
	/**
	* デバイスを取得する関数.
	* 残すべきか悩んだが、デバイスを取得して方法を残した方がいいという意見が多数だったので残しておく@haga
	* @return デバイスのポインタ
	*/
	const IDirect3DDevice9* GetDevice();					

	/**
	* 描画開始処理関数.
	* @param[in] FVF 頂点フォーマット
	*/
	void StartRender(DWORD FVF = DIRECT3DFVF_CUSTOMVERTEX);

	/**描画終了処理関数*/
	void EndRender();											

	/**
	* 頂点フォーマットを設定する関数
	* @param[in] FVF 頂点フォーマット
	*/
	void SetFVF(DWORD FVF);										

	//---------------------------------------------------------------------------------------
	//								テクスチャー関連関数
	//---------------------------------------------------------------------------------------
	/**
	* テクスチャーを読み込む関数.
	* @param[in] key		登録するキー、またはID(enumで作成を想定)
	* @param[in] filepath   ファイル名
	*/
	void LoadTex(int key, char* filePath);																	

	/**
	* テクスチャーを詳細設定して読み込む関数.
	* @param[in] key		登録するキー、またはID(enumで作成を想定)
	* @param[in] filepath   ファイル名
	* @param[in] a			アルファ値  0～255
	* @param[in] r			色のR値 0～255
	* @param[in] g			色のG値 0～255
	* @param[in] b			色のB値 0～255
	* @param[in] size		テクスチャーのサイズが２のべき乗ならtrue,違うならfalse
	*/
	void LoadTexEx(int key, char* filePath,int a, int r, int g, int b, bool size );				

	/**
	* バーテックスを作成する関数.
	* @param[in] key	登録するキー、またはID(enumで作成を想定)
	* @param[in] width	横幅(X軸)
	* @param[in] height 高さ(Y軸)
	* @param[in] depth  奥行(Z軸) デフォルト引数値は0.0f
	*/
	void CreateVtx(int key, float width, float height, float depth = 0.0f);									

	/**
	* バーテックスの変更を行う関数.
	* @param[in] key	登録したキー、またはID
	* @param[in] tuMin  tu値の最小値
	* @param[in] tuMax  tu値の最大値
	* @param[in] tvMin  tv値の最小値
	* @param[in] tvax	tv値の最大値
	* @param[in] color  色情報(ARGB) デフォルト引数値は0xFFFFFFFF
	*/
	void SetVtx(int key, float tuMin, float tuMax, float tvMin, float tvMax, DWORD color = 0xFFFFFFFF);		 

	/**
	* テクスチャーを(XY座標)において描画する関数
	* @param[in] texKey	テクスチャーを登録したキー、またはID
	* @param[in] vtxKey バーテックスを登録したキー、またはID
	* @param[in] center 位置座標をテクスチャーの中心にするならtrue,違うならfalse
	* @param[in] posX	x座標
	* @param[in] posY   y座標
	*/
	void DrawXY(int texKey,int vtxKey,bool center,float posX,float posY);													

	/**
	* テクスチャーをXZ座標で描画する関数
	* @param[in] texKey	テクスチャーを登録したキー、またはID
	* @param[in] vtxKey バーテックスを登録したキー、またはID
	* @param[in] center 位置座標をテクスチャーの中心にするならtrue,違うならfalse
	* @param[in] posX	x座標
	* @param[in] posY   y座標
	* @param[in] posZ   z座標
	*/
	void DrawXZ(int texKey, int vtxKey, bool center, float posX, float posY, float posZ);

	/**
	* テクスチャーを解放する関数
	* @param[in] AllFlag  全て解放するならture,特定のテクスチャーだけを解放するならfalseで第二引数を指定する
	* @param[in] key	登録したキー、またはID。デフォルト引数は999←登録されないだろう数値を代入している要検討
	*/
	void ReleaseTex(bool AllFlag,int key = 999);

	//-------------------------------------------------------------------------------------
	//								Xファイル関連関数
	//-------------------------------------------------------------------------------------
	/**
	* Xファイルを読み込む関数.
	* @param[in] key		 登録するキー、またはID(enumで作成を想定)
	* @param[in] pFilepath   ファイル名
	*/
	void LoadXFile(int key, LPCTSTR pFilePath);					

	/**
	* Xファイルを描画する関数.
	* @param[in] key	登録したキー、またはID
	*/
	void DrawXFile(int key);				

	/**
	* Xファイルを解放する関数.
	* @param[in] AllFlag  全て解放するならture,特定のテクスチャーだけを解放するならfalseで第二引数を指定する
	* @param[in] key	登録したキー、またはID。デフォルト引数は999←登録されないだろう数値を代入している要検討
	*/
	void ReleaseXFile(bool AllFlag,int key = 999);				

	//-----------------------------------------------------------------------------------------------------
	//									入力デバイス関連関数
	//-----------------------------------------------------------------------------------------------------

	/**ダイレクトインプットをアップデートする関数*/
	void UpDateDI();											

	/**
	* キーの状態を確認する関数<br>
	* 第二引数をなんとか変更したいが、いい案が浮かばずそのまま残しておく@haga
	* @param[in] DIK      ダイレクトインプットキー DIK_
	* @param[in] keyName  キーの名前はenumにてA～Zと数字はONE,TWOと英語表記(InputKey.h参照)
	* @return ボタンの状態
	*/
	BUTTON_STATE CheckKey(int DIK, KEYKIND keyName);				

	/**
	* マウスの左ボタンの状態を取得する関数
	* @return ボタンの状態
	*/
	BUTTON_STATE ChecKMouseL();

	/**
	* マウスの右ボタンの状態を取得する関数
	* @return ボタンの状態
	*/
	BUTTON_STATE ChecKMouseR();

	/**
	* マウスのホイールの状態を取得する関数.
	* @return ホイールの状態
	*/
	WHEEL_STATE GetWheelState();								

	/**
	* マウスの座標を取得する関数<br>
	* 最初戻り値D3DXVECTOR2で取得しにしていたが、汎用性がない気がしたのでこの形に変更：@haga
	* @param[out] mousePosX マウス座標xを格納する変数
	* @param[out] mousePosY マウス座標yを格納する変数
	*/
	void GetMousePos(float* mousePosX, float* mousePosY);

	//--------------------------------------------------------------------------
	//							サウンド関連関数
	//--------------------------------------------------------------------------
	/**
	* 音声を読み込む関数.
	* @param[in] key	  登録するキー、またはID(enumで作成を想定)
	* @param[in] filePath ファイル名
	*/
	void LoadSound(int key,TCHAR* filePath);											

	/**
	* 音楽を鳴らす関数
	* @param[in] key		 登録するキー、またはID(enumで作成を想定)
	* @param[in] operation   音楽の再生方法
	*/
	void PlayDSound(int key, SOUND_OPERATION operation);

	//-------------------------------------------------------------------------------
	//								デバック機能
	//-------------------------------------------------------------------------------
	/**
	* デバック用の文字を表示させる関数.
	* @param[in] text 表示した文字
	* @param[in] posX x座標
	* @param[in] posY y座標
	*/
	void DrawDebugFont(std::string text, float posX, float posY);						

	/**
	* デバック用の時間計測を開始する関数.
	* @param[in] timeName	計測したい時間の名前
	*/
	void StartTimer(std::string  timeName);											

	/**
	* デバック用の時間計測を終了する関数.
	* @param[in] timeName	計測を終えたい時間の名前
	*/
	void EndTimer(std::string  timeName);											

	/**
	* デバック用の計測結果を表示する関数.
	* @param[in] timeName	表示したい計測時間の名前
	* @param[in] posX x座標
	* @param[in] posY y座標
	*/
	void DrawResult(std::string  timeName,float posX,float posY);					

	/**
	* デバック用の時間計測した結果を取得する関数.
	* @param[in] timeName	取得したい計測時間の名前
	*/
	DWORD GetResultTime(std::string  timeName);										

	/**
	* デバック用の時間計測した結果全てとその合計時間を表示する関数.
	* @param[in] posX x座標
	* @param[in] posY y座標
	*/
	void DrawAllResult(float posX,float posY);		

private:
	WindowCreator*		m_pWindowCreator;
	GraphicsDevice*		m_pGraphicsDevice;
	InputDevice*		m_pInputDevice;
	SoundFileManager*   m_pSoundFileManager;
	InputKey*			m_pInputKey;
	InputMouse*			m_pInputMouse;
	TextureManager*     m_pTextureManager;
	XFileManager*		m_pXFileManager;
	VertexManager*		m_pVertexManager;
	DebugTimer*			m_pDebugTimer;
	int				    m_wWidth;			//!< ウインドウの幅
	int					m_wHeight;			//!< ウィンドウの高さ
	bool				m_releaseFlag;		//!< メモリ解放したかどうかのフラグ
 };

#endif	// GAMELIB_H

