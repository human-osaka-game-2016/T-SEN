/**
* @file GraphicsDevice.h
* @brief �O���t�B�b�N�X�f�o�C�X�֘A�̃N���X��h
* @author haga
*/
#ifndef GRAPHIC_DEVICE_H
#define GRAPHIC_DEVICE_H

#include <d3d9.h>
#include <d3dx9.h>

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)		//!< ���_�t�H�[�}�b�g�̃}�N��
#define USERVERTE_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)				//!< ���_�t�H�[�}�b�g�̃}�N��(�@���x�N�g�����܂�)
/**
* DirectX�̃f�o�C�X�֘A�̃N���X.
*/
class GraphicsDevice
{
private:
	HWND					m_hWnd;			//!< �E�B���h�E�n���h��
	IDirect3D9*				m_pDirect3D;	//!< Direct3D�̃C���^�[�t�F�C�X
	IDirect3DDevice9*		m_pD3Device;	//!< Direct3D�̃f�o�C�X
	D3DDISPLAYMODE			m_d3ddm;		//!< �f�B�X�v���C
	D3DPRESENT_PARAMETERS	m_d3dpp;		//!< �p�����[�^�[
	D3DPRESENT_PARAMETERS	m_d3dppWindow;	//!< �ʏ�p�����[�^�[
	D3DPRESENT_PARAMETERS	m_d3dppFull;	//!< �t���X�N���[���p�p�����[�^�[
	int						m_wWidth;		//!< �E�B���h�E�A�������̓N���C�A���g�̈�̕�
	int						m_wHeight;		//!< �E�B���h�E�A�������̓N���C�A���g�̈�̍���
	bool					m_wType;		//!< �E�B���h�E�^�C�v true�Ȃ�ʏ� false�Ȃ�t���X�N���[��

public:
	/**�R���X�g���N�^*/
	GraphicsDevice();

	/**�f�X�g���N�^*/
	~GraphicsDevice();

	/**
	* GraphicsDevice�̎��̂��擾����֐�<br>
	* Singleton�p�^�[��.
	* @return graphicsDevice �O���t�B�b�N�f�o�C�X
	*/
	static GraphicsDevice& GetInstance()
	{
		static GraphicsDevice graphicsDevice;
		return graphicsDevice;
	}

	/**
	* DirectX�������֐�.
	* @param[in] hWnd    �E�B���h�E�n���h��
	* @param[in] wType   �E�B���h�E�^�C�v  true�Ȃ�ʏ� false�Ȃ�t���X�N���[��
	* @param[in] wWidth  �E�B���h�E�T�C�Y��
	* @param[in] wHeight �E�B���h�E�T�C�Y����
	* @retval S_OK		DirectX����������
	* @retval E_FAIL	DirectX���������s
	*/
	HRESULT	 InitDevice(HWND hWnd,bool wType,int wWidth,int wHeight);

	/**
	* RenderState�̏����ݒ�.
	*/
	void SetRenderState();

	/**
	* 3D�`��Ŏg�p����RenderState�̏����ݒ�
	*/
	void SetRenderState3D();

	/**
	* �f�o�C�X�擾
	* @ruturn m_pD3Device �O���t�B�b�N�f�o�C�X
	*/
	IDirect3DDevice9* GetDevice(){ return m_pD3Device; };

	/**�`��J�n����*/
	void StartRender();

	/**
	* �`��J�n����<br>
	* ���Œ��_�t�H�[�}�b�g�̐ݒ���s���Ă���.
	* @param[in] FVF �_��Ȓ��_�t�H�[�}�b�g
	*/
	void StartRender(DWORD FVF);

	/**�`��I������*/
	void EndRender();
	
	/**
	* ���_�t�H�[�}�b�g���Z�b�g����֐�.
	* @param[in] FVF �_��Ȓ��_�t�H�[�}�b�g
	*/
	void SetFVF(DWORD FVF);

	/**
	* ���C�g��{�ݒ�
	*/
	void SetLight();

	/**
	* �E�B���h�E���[�h��ς����Ƃ��ɍĐݒ肷��֐�
	*/
	HRESULT ChangeDisplayMode();

};


#endif	// GRAPHIC_DEVICE_H