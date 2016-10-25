/**
* @file GraphicsDevice.h
* @brief グラフィックスデバイス関連のクラスのh
* @author haga
*/
#ifndef GRAPHIC_DEVICE_H
#define GRAPHIC_DEVICE_H

#include <d3d9.h>
#include <d3dx9.h>

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//!< 頂点フォーマットのマクロ
#define USERVERTE_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)				//!< 頂点フォーマットのマクロ(法線ベクトルを含む)
/**
* DirectXのデバイス関連のクラス.
*/
class GraphicsDevice
{
private:
	IDirect3D9*				m_pDirect3D;	//!< Direct3Dのインターフェイス
	IDirect3DDevice9*		m_pD3Device;	//!< Direct3Dのデバイス
	D3DDISPLAYMODE			m_d3ddm;		//!< ディスプレイ
	D3DPRESENT_PARAMETERS	m_d3dpp;		//!< パラメーター
	D3DPRESENT_PARAMETERS	m_d3dppWindow;	//!< 通常パラメーター
	D3DPRESENT_PARAMETERS	m_d3dppFull;	//!< フルスクリーン用パラメーター
	bool					m_wType;		//!< ウィンドウタイプ trueなら通常 falseならフルスクリーン

public:
	/**コンストラクタ*/
	GraphicsDevice();

	/**デストラクタ*/
	~GraphicsDevice();

	/**
	* GraphicsDeviceの実体を取得する関数<br>
	* Singletonパターン.
	* @return graphicsDevice グラフィックデバイス
	*/
	static GraphicsDevice& GetInstance()
	{
		static GraphicsDevice graphicsDevice;
		return graphicsDevice;
	}

	/**
	* DirectX初期化関数.
	* @param[in] hWnd    ウィンドウハンドル
	* @param[in] wType   ウィンドウタイプ  trueなら通常 falseならフルスクリーン
	* @param[in] wWidth  ウィンドウサイズ幅
	* @param[in] wHeight ウィンドウサイズ高さ
	* @retval S_OK		DirectX初期化成功
	* @retval E_FAIL	DirectX初期化失敗
	*/
	HRESULT	 InitDevice(HWND hWnd,bool wType,int wWidth,int wHeight);

	/**
	* RenderStateの初期設定.
	*/
	void SetRenderState();

	/**
	* 3D描画で使用するRenderStateの初期設定
	*/
	void SetRenderState3D();

	/**
	* デバイス取得
	* @ruturn m_pD3Device グラフィックデバイス
	*/
	IDirect3DDevice9* GetDevice(){ return m_pD3Device; };

	/**描画開始処理*/
	void StartRender();

	/**
	* 描画開始処理<br>
	* 中で頂点フォーマットの設定も行っている.
	* @param[in] FVF 柔軟な頂点フォーマット
	*/
	void StartRender(DWORD FVF);

	/**描画終了処理*/
	void EndRender();
	
	/**
	* 頂点フォーマットをセットする関数.
	* @param[in] FVF 柔軟な頂点フォーマット
	*/
	void SetFVF(DWORD FVF);

	/**
	* ウィンドウモードを変えたときに再設定する関数
	*/
	HRESULT ChangeDisplayMode();

};


#endif	// GRAPHIC_DEVICE_H