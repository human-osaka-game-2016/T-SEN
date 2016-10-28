/**
* @file  Light.h
* @brief ライトに関するクラス
* @author haga
*/

#include "Light.h"

// コンストラクタ 環境光
Light::Light(LPDIRECT3DDEVICE9 pD3Device,D3DXVECTOR3 direction) :
m_pD3Device(pD3Device),
m_direction(direction),
m_ambientColor(0x00111111)
{
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse.r = 1.0f;
	m_light.Diffuse.g = 1.0f;
	m_light.Diffuse.b = 1.0f;
	m_light.Specular.r = 1.0f;
	m_light.Specular.g = 1.0f;
	m_light.Specular.b = 1.0f;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_light.Direction, &m_direction);
	m_light.Range = 500.0f;
}

// コンストラクタ 
Light::Light(LPDIRECT3DDEVICE9 pD3Device,D3DXVECTOR3 lightPos, D3DXVECTOR3 direction) :
m_pD3Device(pD3Device),
m_direction(direction),
m_lightPos(lightPos),
m_ambientColor(0x00111111)
{
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));
	m_light.Type = D3DLIGHT_SPOT;
	m_light.Diffuse.r = 1.0f;
	m_light.Diffuse.g = 1.0f;
	m_light.Diffuse.b = 1.0f;
	m_light.Specular.r = 1.0f;
	m_light.Specular.g = 1.0f;
	m_light.Specular.b = 1.0f;
	m_light.Position = m_lightPos;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_light.Direction, &m_direction);
	m_light.Range = 500.0f;
}

// デストラクタ
Light::~Light()
{
}

// ライト使用する関数
void Light::LightUp()
{


	m_pD3Device->SetLight(0, &m_light);
	m_pD3Device->LightEnable(0, TRUE);
	m_pD3Device->SetRenderState(D3DRS_LIGHTING, TRUE);				     // ライトを有効にする
	m_pD3Device->SetRenderState(D3DRS_AMBIENT, m_ambientColor);			 // アンビエントライト(環境光)を設定する
	m_pD3Device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);		     // スペキュラ(鏡面反射)を有効にする
}
 
// ライトの種類を設定する
void Light::SetLightType(D3DLIGHTTYPE type)
{
	m_light.Type = type;
}


// ライトの座標と向きをセットする
void Light::SetLightPos(D3DXVECTOR3 pos)
{
	m_light.Position = pos;

}

// ライトの向きをセットする
void  Light::SetLightDirection(D3DXVECTOR3 direction)
{
	m_direction = direction;
	D3DXVec3Normalize((D3DXVECTOR3*)&m_light.Direction, &direction);
}

// ライトの距離をセットする
void Light::SetLightRange(float range)
{
	m_light.Range = range;
}

// ディフューズをセットする
void Light::SetDiffuse(float dR, float dG, float dB)
{
	m_light.Diffuse.r = dR;
	m_light.Diffuse.g = dG;
	m_light.Diffuse.b = dB;
}

// ライトのスペキュラをセットする
void Light::SetSpecular(float dR, float dG, float dB)
{
	m_light.Specular.r = dR;
	m_light.Specular.g = dG;
	m_light.Specular.b = dB;
}