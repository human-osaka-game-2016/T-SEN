#include "GameLib.h"


GameLib::GameLib(char* title, int width, int height):
m_windowCreator(title,width,height),
m_pGraphicsDevice(NULL),
m_pInputDevice(NULL),
m_pSoundFileManager(NULL),
m_pInputMouse(NULL),
m_pInputKey(NULL),
m_pTextureManager(NULL),
m_pXFileManager(NULL),
m_pVertexManager(NULL),
m_wWidth(width),
m_wHeight(height),
m_releaseFlag(false)
{	
}


GameLib::~GameLib()
{
	if (!m_releaseFlag)
	{
		ReleaseGameLib();
	}
}

// 初期化関数
void GameLib::InitGameLib(HINSTANCE hInstance, LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp), bool windowType)
{
	m_pGraphicsDevice = &GraphicsDevice::GetInstance();
	if (windowType)				// ウィンドウサイズ
	{
		m_windowCreator.MakeWindow(hInstance, WndProc, true);
		m_pGraphicsDevice->InitDevice(m_windowCreator.GetHwnd(), true, m_wWidth, m_wHeight);
	}
	else						// フルスクリーンサイズ
	{
		m_windowCreator.MakeWindow(hInstance, WndProc, false);
		m_pGraphicsDevice->InitDevice(m_windowCreator.GetHwnd(), false, m_wWidth, m_wHeight);
	}

	m_pGraphicsDevice->SetRenderState3D();

	m_pInputDevice = &InputDevice::GetInstance();
	m_pInputDevice->InitDinput();
	m_pInputDevice->InitDinputKey(m_windowCreator.GetHwnd());
	m_pInputDevice->InitDinputMouse(m_windowCreator.GetHwnd());
	m_pInputKey = new InputKey();
	m_pInputMouse = new InputMouse();

	m_pSoundFileManager = &SoundFileManager::GetInstance();
	m_pSoundFileManager->InitSound(m_windowCreator.GetHwnd());

	m_pTextureManager = new TextureManager();
	m_pXFileManager = new XFileManager();
	m_pVertexManager = new VertexManager();
	m_pDebugTimer = new DebugTimer();
}

// メモリ開放関数
void GameLib::ReleaseGameLib()
{
	if (!m_releaseFlag)
	{
		delete m_pDebugTimer;
		delete m_pVertexManager;
		delete m_pXFileManager;
		delete m_pTextureManager;
		delete m_pInputMouse;
		delete m_pInputKey;

		m_releaseFlag = true;
	}
}

// ウィンドウタイプを変える関数
void GameLib::ChangeWindowMode()
{
	m_pGraphicsDevice->ChangeDisplayMode();
	m_windowCreator.ChangeWindowSize();
}

const IDirect3DDevice9* GameLib:: GetDevice()
{
	return (m_pGraphicsDevice->GetDevice());
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
	m_pTextureManager->LoadEx(key, filePath,a,r,g,b,size);
}

void GameLib::CreateVtx(int key, float width, float height, float depth)
{
	m_pVertexManager->CreateVertex(key,width,height,depth);
}

void GameLib::DrawXY(int key, bool center, float posX, float posY)
{
	if (center)
	{
		m_pVertexManager->DrawCenterPos(key,m_pTextureManager->GetTex(key),posX,posY);
	}
	else
	{
		m_pVertexManager->Draw(key, m_pTextureManager->GetTex(key), posX, posY);
	}
}

void GameLib::DrawXZ(int key, bool center, float posX, float posY, float posZ)
{
	if (center)
	{
		m_pVertexManager->DrawCenterPos(key, m_pTextureManager->GetTex(key), posX, posY,posZ);
	}
	else
	{
		m_pVertexManager->Draw(key, m_pTextureManager->GetTex(key), posX, posY,posZ);
	}
}

void GameLib::SetVtx(int key,float tuMin, float tuMax, float tvMin, float tvMax, DWORD color)
{
	m_pVertexManager->SetTuTv(key,tuMin, tuMax, tvMin, tvMax);
	m_pVertexManager->SetColor(key,color);
}

void GameLib::ReleaseTex(bool AllFlag, int key)
{
	if (AllFlag)			// すべて破棄するなら
	{
		m_pTextureManager->ReleaseALL();
		m_pVertexManager->ReleaseALL();
	}
	else
	{
		if (key != 999)
		{
			m_pTextureManager->Release(key);
			m_pVertexManager->Release(key);
		}
	}
}

void GameLib::LoadXFile(int key, LPCTSTR pFilePath)
{
	m_pXFileManager->Load(key,pFilePath);
}

void GameLib::DrawXFile(int key)
{
	m_pXFileManager->Draw(key);
}

void GameLib::ReleaseXFile(bool AllFlag, int key)
{
	if (AllFlag)			// すべて破棄するなら
	{
		m_pXFileManager->ReleaseALL();
	}
	else
	{
		if (key != 999)
		{
			m_pXFileManager->Release(key);
		}
		
	}
}

void GameLib::UpDateDI()
{
	m_pInputKey->UpdateKey();
	m_pInputMouse->UpdateMouse();
}

BUTTON_STATE GameLib::CheckKey(int DIK, KEYKIND keyName)
{
	BUTTON_STATE state;

	switch (m_pInputKey->CheckKey(DIK, keyName))
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

BUTTON_STATE GameLib::ChecKMouse(MOUSEBUTTON mouseButton)
{
	BUTTON_STATE state;
	
	switch (m_pInputMouse->ChecKMouse(mouseButton))
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
	return (m_pInputMouse->GetWheelState());
}

void GameLib::GetMousePos(float* mousePosX, float* mousePosY)
{
	*mousePosX = static_cast<float>(m_pInputMouse->GetPosX());
	*mousePosY = static_cast<float>(m_pInputMouse->GetPosY());
}

void GameLib::LoadSound(int key,TCHAR* filePath)
{
	m_pSoundFileManager->LoadSound(key,filePath);
}

void GameLib::PlayDSound(int key, SOUND_OPERATION operation)
{
	switch (operation)
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

void GameLib::DrawFont(std::string text, float posX, float posY)
{
	DebugFont font;
	font.Draw(text.c_str(),D3DXVECTOR2(posX,posY));
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
	m_pDebugTimer->DrawResult(timeName,D3DXVECTOR2(posX,posY));
}

DWORD GameLib::GetResultTime(std::string  timeName)
{
	return (m_pDebugTimer->GetResult(timeName));
}

void GameLib::DrawAllResult(float posX, float posY)
{
	m_pDebugTimer->DrawAllResult(D3DXVECTOR2(posX, posY));
}