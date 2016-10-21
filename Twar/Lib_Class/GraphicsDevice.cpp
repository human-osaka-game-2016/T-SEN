/**
* @file GraphicsDevice.cpp
* @brief �O���t�B�b�N�X�f�o�C�X�֘A�̃N���X��cpp
* @author haga
*/
#include <d3dx9.h>
#include <d3d9.h>
#include "GraphicsDevice.h"


// �R���X�g���N�^
GraphicsDevice::GraphicsDevice():
m_pDirect3D(NULL),
m_pD3Device(NULL)
{
}

// �f�X�g���N�^
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

// DirectX�������֐�(���ŕ`��ݒ���s���Ă���)
HRESULT	 GraphicsDevice::InitDevice(HWND hWnd, bool wType, int wWidth, int wHeight)
{
	// �E�B���h�E�֘A����ێ�����
	m_hWnd    = hWnd;
	m_wWidth  = wWidth;
	m_wHeight = wHeight;

	m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pDirect3D == NULL)
	{
		MessageBox(0, "Direct3D�̃C���^�[�t�F�C�X�̍쐬�Ɏ��s���܂����B", NULL, MB_OK);
		return E_FAIL;
	}

	m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&m_d3ddm);

	m_wType = wType;			// �E�B���h�E�̏�Ԃ�ێ�

	// �ʏ�E�B���h�E���[�h
	ZeroMemory(&m_d3dppWindow,sizeof(D3DPRESENT_PARAMETERS));		// D3DPRESENT_INTERVAL_DEFAULT = 0 ���ݒ聨���j�^�̃��t���b�V�����[�g = FPS
	m_d3dppWindow.BackBufferFormat = m_d3ddm.Format;
	m_d3dppWindow.BackBufferCount  = 1;
	m_d3dppWindow.SwapEffect       = D3DSWAPEFFECT_DISCARD;
	m_d3dppWindow.Windowed		   = TRUE;
	m_d3dppWindow.EnableAutoDepthStencil = TRUE;
	m_d3dppWindow.AutoDepthStencilFormat = D3DFMT_D24S8;			// Z�o�b�t�@24�r�b�g�A�X�e���V���o�b�t�@8�r�b�g �Ȃ̂�OK
	m_d3dppWindow.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;	// �_�u���X�e���V��
	
	// �t���X�N���[�����[�h(BackBuffer�̐��l�͉��u��)
	ZeroMemory(&m_d3dppFull, sizeof(D3DPRESENT_PARAMETERS));
	m_d3dppFull.BackBufferWidth = m_wWidth;
	m_d3dppFull.BackBufferHeight = m_wHeight;
	m_d3dppFull.BackBufferFormat = m_d3ddm.Format;
	m_d3dppFull.BackBufferCount = 1;
	m_d3dppFull.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dppFull.hDeviceWindow = hWnd;
	m_d3dppFull.Windowed = FALSE;
	m_d3dppFull.EnableAutoDepthStencil = TRUE;
	m_d3dppFull.AutoDepthStencilFormat = D3DFMT_UNKNOWN;
	m_d3dppFull.Flags = 0;
	m_d3dppFull.FullScreen_RefreshRateInHz = 0;
	m_d3dppFull.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_d3dppFull.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	ZeroMemory(&m_d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	if (m_wType)
	{
		m_d3dpp = m_d3dppWindow;
	}
	else
	{
		m_d3dpp = m_d3dppFull;
	}

	// �f�o�C�X�����
	m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&m_d3dpp, &m_pD3Device);

	if (m_pD3Device == NULL)
	{
		MessageBox(0, "Direct3D�̃f�o�C�X�̍쐬�Ɏ��s���܂����B", NULL, MB_OK);
		return E_FAIL;
	}

	// �r���[�|�[�g�̐ݒ�
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

	// �`��ݒ�
	SetRenderState();
	
	return S_OK;
}

// �`��ݒ�
void GraphicsDevice::SetRenderState()
{
	// �`��̐ݒ�
	m_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);  //SRC�̐ݒ�
	m_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pD3Device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);

	m_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	m_pD3Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);

	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
}

// 3D�Ŏg�p����`��ݒ� 
void GraphicsDevice::SetRenderState3D()
{
	m_pD3Device->SetRenderState(D3DRS_ZENABLE, TRUE);				// Z�o�b�t�@������L���ɂ���
//  m_pD3Device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );	// �J�����O���Ȃ�
	m_pD3Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	    // �J�����O����
}

// �`��J�n����
void GraphicsDevice::StartRender()
{
	// ��ʂ̏���
	m_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
	// �`��̊J�n
	m_pD3Device->BeginScene();
}

// �`��J�n���� ���Œ��_�t�H�[�}�b�g���ݒ肵�Ă���
void GraphicsDevice::StartRender(DWORD FVF)
{
	// ��ʂ̏���
	m_pD3Device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);
	// �`��̊J�n
	m_pD3Device->BeginScene();
	// �`��̃t�H�[�}�b�g��ݒ�
	m_pD3Device->SetFVF(FVF);
}

// �`��I������
void GraphicsDevice::EndRender()
{
	// �`��̏I�� 
	m_pD3Device->EndScene();

	// �\��
	m_pD3Device->Present(NULL, NULL, NULL, NULL);
}

// �`��̃t�H�[�}�b�g��ݒ肷��֐�
void GraphicsDevice::SetFVF(DWORD FVF)
{
	m_pD3Device->SetFVF(FVF);
}


// ���C�g�ݒ�
void GraphicsDevice::SetLight()
{
	D3DXVECTOR3 vecDirection(1, 1, 1);
	D3DLIGHT9	light;

	// ���C�g�����Ă� ���F�ŋ��ʔ��˂���ɐݒ�
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;
	//light.Position = D3DXVECTOR3(0.0f, 5.0f, -30.0f);
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDirection);
	light.Range = 200.0f;

	m_pD3Device->SetLight(0, &light);
	m_pD3Device->LightEnable(0, TRUE);
	m_pD3Device->SetRenderState(D3DRS_LIGHTING, TRUE);				// ���C�g��L���ɂ���
	m_pD3Device->SetRenderState(D3DRS_AMBIENT, 0x00111111);			// �A���r�G���g���C�g(����)��ݒ肷��
	m_pD3Device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);		// �X�y�L����(���ʔ���)��L���ɂ���
}

// �E�B���h�E���[�h���ύX�����ꍇ�f�o�C�X�֘A���Đݒ肷��
HRESULT GraphicsDevice::ChangeDisplayMode()
{
	if (m_wType)
	{
		m_d3dpp = m_d3dppFull;
		m_wType = false; // �t���X�N���[�����[�h�ɕύX
	}
	else
	{
		m_d3dpp = m_d3dppWindow;
		m_wType = true; // �ʏ탂�[�h�ɕύX
	}
	if (FAILED(m_pD3Device->Reset(&m_d3dpp)))
	{
		return E_FAIL;
	}

	// �r���[�|�[�g�̐ݒ�
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