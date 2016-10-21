/**
* @file   Vertex.h
* @brief  �o�[�e�b�N�X�N���X��cpp
* @author haga
*/
#include "Vertex.h"

// �R���X�g���N�^
Vertex::Vertex(float width, float height, float depth, float tuMax, float tvMax,float tuMin, float tvMin) :
m_pD3Device(GraphicsDevice::GetInstance().GetDevice()),
m_texWidth(width),
m_texheight(height),
m_texDepth(depth),
m_tuMax(tuMax),
m_tvMax(tvMax),
m_tuMin(tuMin),
m_tvMin(tuMin)
{
	for (int i = 0; i < 4;i++)
	{
		m_color[i] = 0xFFFFFFFF;
	}
	/*
	m_color[0] = 0xFFFFFFFF;
	m_color[1] = 0xFFFFFFFF;
	m_color[2] = 0xFFFFFFFF;
	m_color[3] = 0xFFFFFFFF;
	*/
}

// �f�X�g���N�^
Vertex::~Vertex()
{
}

// �`��(XY���W�ōl����ꍇ)
void Vertex::Draw(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY)
{
	CUSTOMVERTEX vtex[] = {
		{		0.0f,		 0.0f, m_texDepth, 1.0f, m_color[0], m_tuMin, m_tvMin },
		{ m_texWidth,	     0.0f, m_texDepth, 1.0f, m_color[1], m_tuMax, m_tvMin },
		{ m_texWidth, m_texheight, m_texDepth, 1.0f, m_color[2], m_tuMax, m_tvMax },
		{		0.0f, m_texheight, m_texDepth, 1.0f, m_color[3], m_tuMin, m_tvMax },
	};

	for (int i = 0; i < 4; i++)
	{
		vtex[i].x += posX;
		vtex[i].y += posY;
	}

	m_pD3Device->SetTexture(0, pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtex, sizeof(CUSTOMVERTEX));
}

// �`�� XZ���W�ōl����ꍇ
void Vertex::Draw(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ)
{
	CUSTOMVERTEX vtex[] = {
		{		0.0f, m_texheight, m_texDepth, 1.0f, m_color[0], m_tuMin, m_tvMax },
		{ m_texWidth, m_texheight, m_texDepth, 1.0f, m_color[1], m_tuMax, m_tvMax },
		{ m_texWidth, m_texheight,		 0.0f, 1.0f, m_color[2], m_tuMax, m_tvMin },
		{		0.0f, m_texheight,		 0.0f, 1.0f, m_color[3], m_tuMin, m_tvMin },
	};

	for (int i = 0; i < 4; i++)
	{
		vtex[i].x += posX;
		vtex[i].y += posY;
		vtex[i].z += posZ;
	}

	m_pD3Device->SetTexture(0, pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtex, sizeof(CUSTOMVERTEX));
}

// �`��(�e�N�X�`���[�̒��S�ɍ��W�����킹��)������Z���W�ǉ�
void Vertex::DrawCenterPos(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY)
{

	CUSTOMVERTEX vtex[] = {
		{ -m_texWidth, -m_texheight, m_texDepth, 1.0f, m_color[0], m_tuMin, m_tvMin },
		{  m_texWidth, -m_texheight, m_texDepth, 1.0f, m_color[1], m_tuMax, m_tvMin },
		{  m_texWidth,  m_texheight, m_texDepth, 1.0f, m_color[2], m_tuMax, m_tvMax },
		{ -m_texWidth,  m_texheight, m_texDepth, 1.0f, m_color[3], m_tuMin, m_tvMax },
	};

	for (int i = 0; i < 4; i++)
	{
		vtex[i].x += posX;
		vtex[i].y += posY;
	}
	m_pD3Device->SetTexture(0, pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtex, sizeof(CUSTOMVERTEX));
}


// �`��(�e�N�X�`���[�̒��S�ɍ��W�����킹��)������Z���W�ǉ�
void Vertex::DrawCenterPos(LPDIRECT3DTEXTURE9 pTexture, float posX, float posY, float posZ)
{

	CUSTOMVERTEX vtex[] = {
		{ -m_texWidth, m_texheight,  m_texDepth, 1.0f, m_color[0], m_tuMin, m_tvMax },
		{  m_texWidth, m_texheight,  m_texDepth, 1.0f, m_color[1], m_tuMax, m_tvMax },
		{  m_texWidth, m_texheight, -m_texDepth, 1.0f, m_color[2], m_tuMax, m_tvMin },
		{ -m_texWidth, m_texheight, -m_texDepth, 1.0f, m_color[3], m_tuMin, m_tvMin },
	};

	for (int i = 0; i < 4; i++)
	{
		vtex[i].x += posX;
		vtex[i].y += posY;
		vtex[i].z += posZ;
	}
	m_pD3Device->SetTexture(0, pTexture);
	m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, vtex, sizeof(CUSTOMVERTEX));
}

// �e�N�X�`���[�T�C�Y���Z�b�g����֐�
void Vertex::SetTexSize(float texWidth, float texHeight)
{
	m_texWidth = texWidth;
	m_texheight = texHeight;
}

// tu,tv�l��ݒ肷��֐�
void Vertex::SetTuTvVal(float tuMin, float tuMax, float tvMin, float tvMax)
{
	m_tuMin = tuMin;
	m_tvMin = tvMin;
	m_tuMax = tuMax;
	m_tvMax = tvMax;
}

// �F��ݒ肷��֐�
void Vertex::SetColor(DWORD color)
{
	for (int i = 0; i < 4; i++)
	{
		m_color[i] = color;
	}
}