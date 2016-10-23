/**
* @file GameLib.h
* @brief  Facadeパターンのライブラリ作成
* @author haga
*/
#ifndef GAMELIB_H
#define GAMELIB_H

#include <windows.h>
#include <iostream>
#include "WindowCreator.h"	
#include "GraphicsDevice.h"
#include "InputDevice.h"
#include "InputKey.h"
#include "InputMouse.h"
#include "TextureManager.h"
#include "XFileManager.h"
#include "SoundFileManager.h"
#include "VertexManager.h"
#include "DebugFont.h"
#include "DebugTimer.h"
using namespace std;

/**
* ライブラリのクラス
*/
class GameLib
{
private:
	WindowCreator		m_windowCreator;
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

public:
	GameLib(char* title, int width, int height);
	~GameLib();

	/**初期化関数*/
	void InitGameLib(HINSTANCE hInstance, LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp), bool windowType);

	/**メモリ開放関数*/
	void ReleaseGameLib();

	/**ウィンドウ関連関数*/
	void ChangeWindowMode();						//!< ウィンドウサイズを変える関数
	int GetWindowWidth(){ return m_wWidth; }		//!< ウィンドウの横幅を取得する関数
	int GetWindowHeight(){ return m_wHeight; }		//!< ウィンドウの縦幅を取得する関数

	/**描画関連関数*/
	//----SetRenderState系の再設定は関数作るか、それとも下記のGetDeviceでなんとかしてもらうか検討する--------//
	const IDirect3DDevice9* GetDevice();						//!< デバイスを取得する関数
	void StartRender(DWORD FVF = D3DFVF_CUSTOMVERTEX);			//!< 描画開始処理関数
	void EndRender();											//!< 描画終了処理関数
	void SetFVF(DWORD FVF);										//!< 頂点フォーマットを設定する関数

	/**テクスチャー関連関数*/
	void LoadTex(int key, char* filePath);																	//!< テクスチャーを読み込む関数
	void LoadTexEx(int key, char* filePath,int a, int r, int g, int b, bool size );							//!< テクスチャーを詳細設定して読み込む関数
	void CreateVtx(int key, float width, float height, float depth = 0.0f);									//!< バーテックスを作成する関数
	void SetVtx(int key, float tuMin, float tuMax, float tvMin, float tvMax, DWORD color = 0xFFFFFFFF);		//!< バーテックスの変更を行う関数
	void DrawXY(int key,bool center,float posX,float posY);													//!< テクスチャー(XY座標)を描画する関数
	void DrawXZ(int key, bool center,float posX, float posY, float posZ);									//!< テクスチャー(XZ座標)を描画する関数
	void ReleaseTex(bool AllFlag,int key = 999);

	/**Xファイル関連関数*/
	void LoadXFile(int key, LPCTSTR pFilePath);					//!< Xファイルを読み込む関数
	void DrawXFile(int key);									//!< Xファイルを描画する関数
	void ReleaseXFile(bool AllFlag,int key = 999);				//!< Xファイルを解放する関数

	/**入力デバイス関連関数*/
	void UpDateDI();											//!< ダイレクトインプットをアップデートする関数
	BUTTONSTATE CheckKey(int DIK, KEYKIND keyName);				//!< キーの状態を確認する関数
	BUTTONSTATE ChecKMouse(MOUSEBUTTON mouseButton);			//!< マウスのボタンの状態を取得する関数
	WHEEL_STATE GetWheelState();								//!< マウスのホイールの状態を取得する関数
	D3DXVECTOR2 GetMousePos();									//!< マウスの座標を取得する関数

	/**サウンド関連関数*/
	void LoadSound(TCHAR* filePath);											//!< 音声を読み込む関数
	void PlayDSound(TCHAR* filePath, SOUND_MODE sMode);							//!< 音楽を鳴らす関数

	/**デバック機能*/
	void DrawFont(std::string text, float posX, float posY);						//!< 文字を表示させる関数
	void StartTimer(std::string  timeName);											//!< 時間計測を開始する関数
	void EndTimer(std::string  timeName);											//!< 時間計測を終了する関数
	void DrawResult(std::string  timeName,float posX,float posY);					//!< 計測結果を表示する関数
	DWORD GetResultTime(std::string  timeName);										//!< 計測結果を取得する関数
	void DrawAllResult(float posX,float posY);										//!< すべての時間結果とその合計時間を表示する関数
 };

#endif	// GAMELIB_H

