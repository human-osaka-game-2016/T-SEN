/**
* @file LibClass.h
* @brief Lib_Classのヘッダーファイルをまとめたヘッダーファイル<br>
* ヘッダーをフィルターごとに分けている.
* @author haga
*/

#ifndef LIB_CLASS_H
#define LIB_CLASS_H

//--------------------------------------------
//　　　　　 DirectXGraphics
//--------------------------------------------
#include "GraphicsDevice.h"			//!< GraphicsDeviceのクラス
#include "Texture.h"				//!< テクスチャクラス
#include "Vertex.h"					//!< 頂点クラス
#include "XFile.h"					//!< Xファイルクラス
#include "Font.h"					//!< フォントクラス

//-------------------------------------------
//　　　　　　 DirectInput
//-------------------------------------------
#include "InputDevice.h"			//!< DirectInputデバイス関連クラス
#include "InputKey.h"				//!< キーボード操作関連クラス
#include "InputMouse.h"				//!< マウス操作関連クラス

//-------------------------------------------
//				DirectSound
//-------------------------------------------
#include "DSound.h"					//!< DirectSoundデバイス関連クラス
#include "SoundPlayer.h"			//!< 音楽再生クラス

//-------------------------------------------
//　　　　　	WindowCreater
//-------------------------------------------
#include "WindowCreator.h"			//!< Window関連クラス

//-------------------------------------------
//				その他
//-------------------------------------------
#include "Camera.h"					//!< カメラクラス
#include "Light.h"					//!< ライトクラス
#include "DebugTimer.h"				//!< デバックタイマークラス

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