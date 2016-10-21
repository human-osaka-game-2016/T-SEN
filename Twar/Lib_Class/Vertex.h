/**
* @file   Vertex.h
* @brief  �o�[�e�b�N�X�N���X
* @author haga
*/
#ifndef VERTEX_H
#define VERTEX_H

#include "GraphicsDevice.h"

/**
* �J�X�^���o�[�e�b�N�X�\����.
*/
struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;	//!< ���W�n
	DWORD	color;			//!< �F
	FLOAT	tu, tv;			//!< �e�N�X�`���[��tu,tv�l
};


/**
* �o�[�e�b�N�X�N���X
*/
class Vertex
{
private:
	IDirect3DDevice9*		m_pD3Device;			//!< �f�o�C�X
	float					m_texWidth;		  	    //!< �e�N�X�`���[�̕�
	float					m_texheight;			//!< �e�N�X�`���[�̍���
	float					m_texDepth;				//!< �e�N�X�`���[�̉��s��
	float					m_tuMax;				//!< �e�N�X�`���[��tu�ő�l
	float					m_tuMin;				//!< �e�N�X�`���[��tu�ŏ��l
	float					m_tvMax;				//!< �e�N�X�`���[��tv�ő�l
	float					m_tvMin;				//!< �e�N�X�`���[��tv�ŏ��l
	DWORD                   m_color[4];				//!< �F�̒l

public:
	
	/**
	* �R���X�g���N�^.
	* ���l���w�肷��Ƃ��Ɏg�p<br>
	* ���s���w�肷��ꍇ�ɍ쐬.
	* @param[in] width  ��
	* @param[in] height ����
	* @param[in] deoth	���s��
	* @param[in] tuMax	 tu�l�̍ő�l
	* @param[in] tvMax	 tv�l�̍ő�l
	* @param[in] tuMin	 tu�l�̍ŏ��l
	* @param[in] tvMin	 tv�l�̍ŏ��l
	*/
	Vertex(float width,float height,float depth = 0.0f,float tuMax = 1.0f,float tvMax = 1.0f,float tuMin = 0.0f,float tvMin = 0.0f);

	/**�f�X�g���N�^*/
	~Vertex();

	/**
	* �ʏ�`��֐�<br>
	* �e�N�X�`���[�̍���ɍ��W���Z�b�g����<br>
	* @param[in] texture �e�N�X�`���[�N���X�̃|�C���^
	* @param[in] posX     X���W
	* @param[in] posY     Y���W
	*/
	void Draw(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY);

	/**
	* �ʏ�`��֐�<br>
	* �e�N�X�`���[�̍���ɍ��W���Z�b�g����<br>
	* �������Z���W�������Ƃ��ēn��.
	* @param[in] texture �e�N�X�`���[�N���X�̃|�C���^
	* @param[in] posX     X���W
	* @param[in] posY     Y���W
	* @param[in] posZ	  Z���W(�f�t�H���g������0.0f)
	*/
	void Draw(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ);

	/**
	* �`��֐�<br>
	* �e�N�X�`���[�̒��S�ɍ��W���Z�b�g����<br>
	* @param[in] texture �e�N�X�`���[�N���X�̃|�C���^
	* @param[in] posX     X���W
	* @param[in] posY     Y���W
	*/
	void DrawCenterPos(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY);

	/**
	* �`��֐�<br>
	* �e�N�X�`���[�̒��S�ɍ��W���Z�b�g����<br>
	* Z���W�������Ƃ��ēn��.
	* @param[in] texture �e�N�X�`���[�N���X�̃|�C���^
	* @param[in] posX     X���W
	* @param[in] posY     Y���W
	* @param[in] posZ	  Z���W(�f�t�H���g������0.0f)
	*/
	void DrawCenterPos(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ);

	/**
	* �e�N�X�`���[�T�C�Y���Z�b�g����֐�.
	* @param[in] texWidth  �e�N�X�`���[�̕�
	* @param[in] texHeight �e�N�X�`���[�̍���
	*/
	void SetTexSize(float texWidth, float texHeight);

	/**
	* tu,tv�l��ݒ肷��֐�.
	* @param[in] tuMin tu�l�̍ŏ��l
	* @param[in] tuMax tu�l�̍ő�l
	* @param[in] tvMin tv�l�̍ŏ��l
	* @param[in] tvMax tv�l�̍ő�l
	*/
	void SetTuTvVal(float tuMin,float tuMax, float tvMin,float tvMax);

	/**
	* �e�N�X�`���[�F���Z�b�g����֐�.
	* @param[in] color  �F�̐ݒ�
	*/
	void SetColor(DWORD color);

};

#endif