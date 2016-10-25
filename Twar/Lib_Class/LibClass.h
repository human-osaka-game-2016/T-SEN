/**
* @file LibClass.h
* @brief Lib_Classのヘッダーファイルをまとめたヘッダーファイル<br>
* ヘッダーをフィルターごとに分けている<br>
* あくまでこのヘッダーは確認用なので、includeはしないこと
* @author haga
*/

#ifndef LIB_CLASS_H
#define LIB_CLASS_H

//--------------------------------------------
//　　　　　 DirectXGraphics
//--------------------------------------------
#include "./GameLib/GraphicsDevice.h"			//!< GraphicsDeviceのクラス
#include "./GameLib/Vertex.h"					//!< 頂点クラス
#include "./GameLib/XFile.h"					//!< Xファイルクラス
#include "./Font/Font.h"			//!< フォントクラス

//-------------------------------------------
//　　　　　　 DirectInput
//-------------------------------------------
#include "./GameLib/InputDevice.h"			//!< DirectInputデバイス関連クラス
#include "./GameLib/InputKey.h"				//!< キーボード操作関連クラス
#include "./GameLib/InputMouse.h"				//!< マウス操作関連クラス

//-------------------------------------------
//				DirectSound
//-------------------------------------------
#include "./GameLib/SoundFileManager.h"

//-------------------------------------------
//　　　　　	WindowCreater
//-------------------------------------------
#include "./GameLib/WindowCreator.h"			//!< Window関連クラス

//-------------------------------------------
//				その他
//-------------------------------------------
#include "./Camera/Camera.h"					//!< カメラクラス
#include "./Light/Light.h"					//!< ライトクラス
#include "./GameLib/DebugTimer.h"				//!< デバックタイマークラス

/*
設定するLib
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"d3d9.lib")
#pragma comment (lib,"d3dx9.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"shlwapi.lib")
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"Dsound.lib")
#pragma comment (lib,"Lib_Class.lib")
*/

#endif