/**
* @file GraphicsDevice.cpp
* @brief グラフィックスデバイス関連のクラスのcpp
* @author haga
*/
#include <d3dx9.h>
#include <d3d9.h>
#include "GraphicsDevice.h"


// コンストラクタ
GraphicsDevice::GraphicsDevice():
m_pDirect3D(NULL),
m_pD3Device(NULL)
{
}

// デストラクタ
GraphicsDevice::~GraphicsDevice()
{
	if (m_pD3Device != NULL)
	{
		m_pD3Device->Release();
		m_pD3Device = NULL;
	}

	if (m_pDirect3D != NULL)
	{
		m_pDirect3D->Release();
		m_pDirect3D = NULL;
	}
}

// DirectX初期化関数(中で描画設定も行っている)
HRESULT	 GraphicsDevice::InitDevice(HWND hWnd, bool wType, int wWidth, int wHeight)
{
	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pDirect3D == NULL)
	{
		MessageBox(0, "Direct3Dのインターフェイスの作成に失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}

	m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&m_d3ddm);

	m_wType = wType;			// ウィンドウの状態を保持

	// 通常ウィンドウモード
	ZeroMemory(&m_d3dppWindow,sizeof(D3DPRESENT_PARAMETERS));		// D3DPRESENT_INTERVAL_DEFAULT = 0 が設定→モニタのリフレッシュレート = FPS
	m_d3dppWindow.BackBufferFormat = m_d3ddm.Format;
	m_d3dppWindow.BackBufferCount  = 1;
	m_d3dppWindow.SwapEffect       = D3DSWAPEFFECT_DISCARD;
	m_d3dppWindow.Windowed		   = TRUE;
	m_d3dppWindow.EnableAutoDepthStencil = TRUE;
	m_d3dppWindow.AutoDepthStencilFormat = D3DFMT_D24S8;			// Zバッファ24ビット、ステンシルバッファ8ビット なのでOK
	m_d3dppWindow.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;	// ダブルステンシル
	
	// フルスクリーンモード(BackBufferの数値は仮置き)
	ZeroMemory(&m_d3dppFull, sizeof(D3DPRESENT_PARAMETERS));
	m_d3dppFull.BackBufferWidth = wWidth;
	m_d3dppFull.BackBufferHeight = wHeight;
	m_d3dppFull.BackBufferFormat = m_d3ddm.Format;
	m_d3dppFull.BackBufferCount = 1;
	m_d3dppFull.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dppFull.hDeviceWindow = hWnd;
	m_d3dppFull.Windowed = FALSE;
	m_d3dppFull.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	m_d3dppFull.EnableAutoDepthStencil = TRUE;
	m_d3dppFull.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_d3dppFull.Flags = 0;
	m_d3dppFull.FullScreen_RefreshRateInHz = 0;
	//m_d3dppFull.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	//m_d3dppFull.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	ZeroMemory(&m_d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	if (m_wType)
	{
		m_d3dpp = m_d3dppWindow;
	}
	else
	{
		m_d3dpp = m_d3dppFull;
	}

	// デバイスを作る
	m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&m_d3dpp, &m_pD3Device);

	if (m_pD3Device == NULL)
	{
		MessageBox(0, "Direct3Dのデバイスの作成に失敗しました。", NULL, MB_OK);
		return E_FAIL;
	}

	// ビューポートの設定
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = m_d3dpp.BackBufferWidth;
	vp.Height = m_d3dpp.BackBufferHeight;
	vp.MinZ = 0.f;
	vp.MaxZ = 1.f;
	if (FAILED(m_pD3Device->SetViewport(&vp)))
	{
		return E_FAIL;
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
	m_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRCの設定
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
	m_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
	// 描画の開始
	m_pD3Device->BeginScene();
}

// 描画開始処理 中で頂点フォーマットも設定している
void GraphicsDevice::StartRender(DWORD FVF)
{
	// 画面の消去
	m_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
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
	if (m_wType)
	{
		m_d3dpp = m_d3dppFull;
		m_wType = false; // フルスクリーンモードに変更
	}
	else
	{
		m_d3dpp = m_d3dppWindow;
		m_wType = true; // 通常モードに変更
	}
	if (FAILED(m_pD3Device->Reset(&m_d3dpp)))
	{
		return E_FAIL;
	}

	// ビューポートの設定
	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = m_d3dpp.BackBufferWidth;
	vp.Height = m_d3dpp.BackBufferHeight;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;
	if (FAILED(m_pD3Device->SetViewport(&vp)))
	{
		return E_FAIL;
	}

	return S_OK;
}