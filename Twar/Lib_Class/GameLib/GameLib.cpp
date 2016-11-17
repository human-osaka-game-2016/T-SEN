/**
* @file GameLib.cpp
* @brief GameLibクラス実装
* @author haga
*/
#include "Lib/WindowCreator.h"	
#include "Lib/GraphicsDevice.h"
#include "Lib/InputDevice.h"
#include "Lib/InputMouse.h"
#include "Lib/TextureManager.h"
#include "Lib/XFileManager.h"
#include "Lib/SoundFileManager.h"
#include "Lib/VertexManager.h"
#include "Lib/DebugFont.h"
#include "Lib/DebugTimer.h"
#include "GameLib.h"


GameLib::GameLib()
	: m_pWindowCreator(nullptr)
	, m_pGraphicsDevice(nullptr)
	, m_pInputDevice(nullptr)
	, m_pSoundFileManager(nullptr)
	, m_pInputMouse(nullptr)
	, m_pInputKey(nullptr)
	, m_pTextureManager(nullptr)
	, m_pXFileManager(nullptr)
	, m_pVertexManager(nullptr)
	, m_WinWidth(0)
	, m_WinHeight(0)
{
}


GameLib::~GameLib()
{
	ReleaseGameLib();
}

// 初期化関数
void GameLib::InitGameLib(TCHAR*  title, int width, int height, LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM), bool isFullScreen)
{
	m_WinWidth = width;
	m_WinHeight = height;
	HINSTANCE hInstance = GetModuleHandle(NULL);

	m_pWindowCreator = new WindowCreator(title, width, height);

	m_pGraphicsDevice = &GraphicsDevice::GetInstance();

	m_pWindowCreator->MakeWindow(hInstance, WndProc, isFullScreen);
	m_pGraphicsDevice->InitDevice(m_pWindowCreator->GetHwnd(), isFullScreen, m_WinWidth, m_WinHeight);

	m_pGraphicsDevice->SetRenderState3D();

	m_pInputDevice = &InputDevice::GetInstance();
	m_pInputDevice->InitDinput();
	m_pInputDevice->InitDinputKey(m_pWindowCreator->GetHwnd());
	m_pInputDevice->InitDinputMouse(m_pWindowCreator->GetHwnd());
	m_pInputKey = new InputKey();
	m_pInputMouse = new InputMouse();

	m_pSoundFileManager = &SoundFileManager::GetInstance();
	m_pSoundFileManager->InitSound(m_pWindowCreator->GetHwnd());

	m_pTextureManager = new TextureManager();
	m_pXFileManager = new XFileManager();
	m_pVertexManager = new VertexManager();
	m_pDebugTimer = new DebugTimer();
}

// メモリ開放関数
void GameLib::ReleaseGameLib()
{
	delete m_pDebugTimer;
	m_pDebugTimer = nullptr;

	delete m_pVertexManager;
	m_pVertexManager = nullptr;

	delete m_pXFileManager;
	m_pXFileManager = nullptr;

	delete m_pTextureManager;
	m_pTextureManager = nullptr;

	delete m_pInputMouse;
	m_pInputMouse = nullptr;

	delete m_pInputKey;
	m_pInputKey = nullptr;

	delete m_pWindowCreator;
	m_pWindowCreator = nullptr;
}

// ウィンドウタイプを変える関数
void GameLib::ChangeWindowMode()
{
	m_pGraphicsDevice->ChangeDisplayMode();
	m_pWindowCreator->ChangeWindowSize();
}

int GameLib::GetWindowWidth()
{
	return m_WinWidth;
}

int GameLib::GetWindowHeight()
{
	return m_WinHeight;
}

IDirect3DDevice9* GameLib::GetDevice()
{
	return ( m_pGraphicsDevice->GetDevice() );
}

void GameLib::StartRender(DWORD FVF)
{
	m_pGraphicsDevice->StartRender(FVF);
}

void GameLib::EndRender()
{
	m_pGraphicsDevice->EndRender();
}

void GameLib::SetFVF(DWORD FVF)
{
	m_pGraphicsDevice->SetFVF(FVF);
}

void GameLib::LoadTex(int key, char* filePath)
{
	m_pTextureManager->Load(key, filePath);
}

void GameLib::LoadTexEx(int key, char* filePath, int a, int r, int g, int b, bool size)
{
	m_pTextureManager->LoadEx(key, filePath, a, r, g, b, size);
}

LPDIRECT3DTEXTURE9 GameLib::GetTexture(int key)
{
	return m_pTextureManager->GetTex(key);
}

void GameLib::CreateVtx(int key, float width, float height, float depth)
{
	m_pVertexManager->CreateVertex(key, width, height, depth);
}

void GameLib::DrawXY(int texKey, int vtxKey, bool center, float posX, float posY)
{
	m_pVertexManager->Draw(vtxKey, m_pTextureManager->GetTex(texKey), posX, posY);
}

void GameLib::DrawXYCenterPos(int texKey, int vtxKey, float posX, float posY)
{
	m_pVertexManager->DrawCenterPos(vtxKey, m_pTextureManager->GetTex(texKey), posX, posY);
}

void GameLib::DrawXZ(int texKey, int vtxKey, float posX, float posY, float posZ)
{
	m_pVertexManager->Draw(vtxKey, m_pTextureManager->GetTex(texKey), posX, posY, posZ);
}

void GameLib::DrawXZCenterPos(int texKey, int vtxKey, float posX, float posY, float posZ)
{
	m_pVertexManager->DrawCenterPos(vtxKey, m_pTextureManager->GetTex(texKey), posX, posY, posZ);
}

void GameLib::SetVtx(int key, float tuMin, float tuMax, float tvMin, float tvMax, DWORD color)
{
	m_pVertexManager->SetTuTv(key, tuMin, tuMax, tvMin, tvMax);
	m_pVertexManager->SetColor(key, color);
}

void GameLib::ReleaseTex(int key)
{
	m_pTextureManager->Release(key);
}

void GameLib::ReleaseAllTex()
{
	m_pTextureManager->ReleaseALL();
}

void GameLib::ReleaseVertex(int key)
{
	m_pVertexManager->Release(key);
}

void GameLib::ReleaseAllVertex()
{
	m_pVertexManager->ReleaseALL();
}

void GameLib::LoadXFile(int key, LPCTSTR pFilePath)
{
	m_pXFileManager->Load(key, pFilePath);
}

void GameLib::DrawXFile(int key)
{
	m_pXFileManager->Draw(key);
}

void GameLib::ReleaseXFile(int key)
{
	m_pXFileManager->Release(key);
}

void  GameLib::ReleaseAllXFile()
{
	m_pXFileManager->ReleaseALL();
}

void GameLib::UpdateDI()
{
	m_pInputKey->UpdateKey();
	m_pInputMouse->UpdateMouse();
}

BUTTON_STATE GameLib::CheckKey(int DIK, KEYKIND keyName)
{
	BUTTON_STATE state;

	switch(m_pInputKey->CheckKey(DIK, keyName))
	{
	case BTN_ON:
		state = ON;
		break;

	case BTN_OFF:
		state = OFF;
		break;

	case BTN_PUSH:
		state = PUSH;
		break;

	case BTN_RELEASE:
		state = RELEASE;
		break;
	}
	return state;
}

BUTTON_STATE GameLib::ChecKMouseL()
{
	BUTTON_STATE state;

	switch(m_pInputMouse->ChecKMouse(MouseLeft))
	{
	case BTN_ON:
		state = ON;
		break;

	case BTN_OFF:
		state = OFF;
		break;

	case BTN_PUSH:
		state = PUSH;
		break;

	case BTN_RELEASE:
		state = RELEASE;
		break;
	}
	return state;
}

BUTTON_STATE GameLib::ChecKMouseR()
{
	BUTTON_STATE state;

	switch(m_pInputMouse->ChecKMouse(MouseRight))
	{
	case BTN_ON:
		state = ON;
		break;

	case BTN_OFF:
		state = OFF;
		break;

	case BTN_PUSH:
		state = PUSH;
		break;

	case BTN_RELEASE:
		state = RELEASE;
		break;
	}
	return state;
}

WHEEL_STATE GameLib::GetWheelState()
{
	WHEEL_STATE state;

	switch(m_pInputMouse->GetWheelState())
	{
	case WHEEL_NONE:
		state = ROLL_NONE;
		break;

	case WHEEL_UP:
		state = ROLL_UP;
		break;

	case WHEEL_DOWN:
		state = ROLL_DOWN;
		break;
	}
	return state;
}

void GameLib::GetMousePos(float* mousePosX, float* mousePosY)
{
	*mousePosX = static_cast<float>( m_pInputMouse->GetPosX() );
	*mousePosY = static_cast<float>( m_pInputMouse->GetPosY() );
}

void GameLib::ShowMouseCursor(bool isVisible)
{
	m_pInputMouse->ShowMouseCursor(isVisible);
}

void GameLib::SetMousePos(int x, int y)
{
	m_pInputMouse->SetMouseCursor(x, y);
}

void GameLib::SetMousePosCenter()
{
	m_pInputMouse->SetMouseCenter();
}

void GameLib::RestrictMouseCursor()
{
	m_pInputMouse->RestrictCursor();
}

void GameLib::LoadSound(int key, TCHAR* filePath)
{
	m_pSoundFileManager->LoadSound(key, filePath);
}

void GameLib::PlayDSound(int key, SOUND_OPERATION operation)
{
	switch(operation)
	{
	case SOUND_PLAY:
		m_pSoundFileManager->SoundPlayer(key, SOUND_MODE::Play);
		break;

	case SOUND_STOP:
		m_pSoundFileManager->SoundPlayer(key, SOUND_MODE::Stop);
		break;

	case SOUND_LOOP:
		m_pSoundFileManager->SoundPlayer(key, SOUND_MODE::PlayLoop);
		break;

	case SOUND_RESET:
		m_pSoundFileManager->SoundPlayer(key, SOUND_MODE::Reset);
		break;

	case SOUND_RESET_PLAY:
		m_pSoundFileManager->SoundPlayer(key, SOUND_MODE::Reset_Play);
		break;

	case SOUND_STOP_RESET:
		m_pSoundFileManager->SoundPlayer(key, SOUND_MODE::Stop_Reset);
		break;

	}

}

void GameLib::DrawDebugFont(std::string text, float posX, float posY)
{
	DebugFont font;
	font.Draw(text.c_str(), D3DXVECTOR2(posX, posY));
}

void GameLib::StartTimer(std::string  timeName)
{
	m_pDebugTimer->SetDebugTimer(timeName);
	m_pDebugTimer->StartTimer(timeName);
}

void GameLib::EndTimer(std::string  timeName)
{
	m_pDebugTimer->EndTimer(timeName);
}

void GameLib::DrawResult(std::string  timeName, float posX, float posY)
{
	m_pDebugTimer->DrawResult(timeName, D3DXVECTOR2(posX, posY));
}

DWORD GameLib::GetResultTime(std::string  timeName)
{
	return ( m_pDebugTimer->GetResult(timeName) );
}

void GameLib::DrawAllResult(float posX, float posY)
{
	m_pDebugTimer->DrawAllResult(D3DXVECTOR2(posX, posY));
}