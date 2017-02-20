//==================================================================================================================================//
//!< @file		GraphicsDevice.cpp
//!< @brief		GraphicsDeviceクラス実装
//!< @author	haga
//==================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include <d3dx9.h>
#include <d3d9.h>
#include "GraphicsDevice.h"

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

// DirectX初期化関数(中で描画設定も行っている)
HRESULT	 GraphicsDevice::InitDevice(HWND hWnd, bool isFullScreen, int wWidth, int wHeight)
{
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pDirect3D == NULL)
	{
		MessageBox(0, "Direct3Dのインターフェイスの作成に失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}
	else
	{
		// Direct3Dのインターフェイスの作成に成功。下記処理へ移行。 チェック用空処理
	}

	m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &m_D3ddm);

	// 通常ウィンドウモード設定
	ZeroMemory(&m_D3dppWindow,sizeof(D3DPRESENT_PARAMETERS));						// D3DPRESENT_INTERVAL_DEFAULT = 0 が設定→モニタのリフレッシュレート = FPS
	m_D3dppWindow.BackBufferFormat			= m_D3ddm.Format;
	m_D3dppWindow.BackBufferCount			= 1;
	m_D3dppWindow.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	m_D3dppWindow.Windowed					= TRUE;
	m_D3dppWindow.EnableAutoDepthStencil	= TRUE;
	m_D3dppWindow.AutoDepthStencilFormat	= D3DFMT_D24S8;							// Zバッファ24ビット、ステンシルバッファ8ビット なのでOK
	m_D3dppWindow.Flags						= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;	// ダブルステンシル
	
	// フルスクリーンモード設定(BackBufferの数値は仮置き)
	ZeroMemory(&m_D3dppFull, sizeof(D3DPRESENT_PARAMETERS));
	m_D3dppFull.BackBufferWidth				= wWidth;
	m_D3dppFull.BackBufferHeight			= wHeight;
	m_D3dppFull.BackBufferFormat			= m_D3ddm.Format;
	m_D3dppFull.BackBufferCount				= 1;
	m_D3dppFull.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	m_D3dppFull.hDeviceWindow				= hWnd;
	m_D3dppFull.Windowed					= FALSE;
	m_D3dppFull.PresentationInterval		= D3DPRESENT_INTERVAL_DEFAULT;
	m_D3dppFull.EnableAutoDepthStencil		= TRUE;
	m_D3dppFull.AutoDepthStencilFormat		= D3DFMT_D24S8;
	m_D3dppFull.Flags						= 0;
	m_D3dppFull.FullScreen_RefreshRateInHz	= 0;
	//m_d3dppFull.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;
	//m_d3dppFull.PresentationInterval		= D3DPRESENT_INTERVAL_ONE;

	m_IsFullScreen = isFullScreen;			// ウィンドウの状態を保持

	ZeroMemory(&m_D3dpp, sizeof(D3DPRESENT_PARAMETERS));
	if(m_IsFullScreen)
	{
		m_D3dpp = m_D3dppFull;
	}
	else
	{
		m_D3dpp = m_D3dppWindow;
	}

	// デバイスを作成
	m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3dpp, &m_pD3Device);

	if (m_pD3Device == NULL)
	{
		MessageBox(0, "Direct3Dのデバイスの作成に失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}
	else
	{
		// Direct3Dのデバイスの作成に成功。下記処理へ移行。 チェック用空処理
	}

	// ビューポートの設定
	D3DVIEWPORT9 vp;
	vp.X		= 0;
	vp.Y		= 0;
	vp.Width	= m_D3dpp.BackBufferWidth;
	vp.Height	= m_D3dpp.BackBufferHeight;
	vp.MinZ		= 0.f;
	vp.MaxZ		= 1.f;
	if (FAILED(m_pD3Device->SetViewport(&vp)))
	{
		return E_FAIL;
	}
	else
	{
		// ビューポートの設定成功。下記処理へ移行。 チェック用空処理
	}

	// 描画設定
	SetRenderState();
	
	return S_OK;
}

// 描画設定
void GraphicsDevice::SetRenderState()
{
	// 描画の設定
	m_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			// SRCの設定
	m_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pD3Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);

	m_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	m_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}

// 3Dで使用する描画設定 
void GraphicsDevice::SetRenderState3D()
{
	m_pD3Device->SetRenderState(D3DRS_ZENABLE, TRUE);				// Zバッファ処理を有効にする
//  m_pD3Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );	// カリングしない
	m_pD3Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	    // カリングする
}

// 描画開始処理
void GraphicsDevice::StartRender()
{
	// 画面の消去
	m_pD3Device->Clear(0, NULL, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
	// 描画の開始
	m_pD3Device->BeginScene();
}

// 描画開始処理 中で頂点フォーマットも設定している
void GraphicsDevice::StartRender(DWORD FVF)
{
	// 画面の消去
	m_pD3Device->Clear(0, NULL, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
	// 描画の開始
	m_pD3Device->BeginScene();
	// 描画のフォーマットを設定
	m_pD3Device->SetFVF(FVF);
}

// 描画終了処理
void GraphicsDevice::EndRender()
{
	// 描画の終了 
	m_pD3Device->EndScene();

	// 表示
	m_pD3Device->Present(NULL, NULL, NULL, NULL);
}

// 描画のフォーマットを設定する関数
void GraphicsDevice::SetFVF(DWORD FVF)
{
	m_pD3Device->SetFVF(FVF);
}

// ウィンドウモードが変更した場合デバイス関連を再設定する
HRESULT GraphicsDevice::ChangeDisplayMode()
{
	if (m_IsFullScreen)
	{	// 通常モードに変更
		m_D3dpp = m_D3dppWindow;
		m_IsFullScreen = false; 
	}
	else
	{	// フルスクリーンモードに変更
		m_D3dpp = m_D3dppFull;
		m_IsFullScreen = true; 
		
	}

	if (FAILED(m_pD3Device->Reset(&m_D3dpp)))
	{
		return E_FAIL;
	}
	else
	{
		// パラメーターのリセット成功。下記処理へ移行。 チェック用空処理
	}

	// ビューポートの設定
	D3DVIEWPORT9 vp;
	vp.X		= 0;
	vp.Y		= 0;
	vp.Width	= m_D3dpp.BackBufferWidth;
	vp.Height	= m_D3dpp.BackBufferHeight;
	vp.MinZ		= 0.0f;
	vp.MaxZ		= 1.0f;
	if (FAILED(m_pD3Device->SetViewport(&vp)))
	{
		return E_FAIL;
	}
	else
	{
		// ビューポートの設定成功。下記処理へ移行。 チェック用空処理
	}

	return S_OK;
}

GraphicsDevice::~GraphicsDevice()
{
	if(m_pD3Device != NULL)
	{
		m_pD3Device->Release();
		m_pD3Device = NULL;
	}
	else
	{
		// インターフェイス作成及びデバイス作成に失敗した場合にこの分岐にはいる。 チェック用空処理
	}

	if(m_pDirect3D != NULL)
	{
		m_pDirect3D->Release();
		m_pDirect3D = NULL;
	}
	else
	{
		// インターフェイス作成に失敗した場合にこの分岐にはいる。 チェック用空処理
	}
}

//--------------------------------------------------------------------------------------------------------------//
//Private functions
//--------------------------------------------------------------------------------------------------------------//

GraphicsDevice::GraphicsDevice()
	: m_pDirect3D(NULL)
	, m_pD3Device(NULL)
{}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
