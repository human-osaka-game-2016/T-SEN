#include "Ship.h"


Ship::Ship(D3DXVECTOR3* pos):
m_ObjPos(*pos),
m_pD3Device(GraphicsDevice::GetInstance().GetDevice()),
m_pcameraController(&CameraController::GetInstance())
{
	
}


Ship::~Ship()
{
}

void Ship::Control()
{
}

void Ship::Player()
{
}

void Ship::Ally()
{
}

void Ship::Enemy()
{
}

void Ship::Draw()
{
}

void Ship::TransWorld(const D3DXVECTOR3* pos, const D3DXMATRIX* rotation)
{
	D3DXMATRIX      matWorld;						// ワールド座標
	D3DXVECTOR3		vecTarget(-0.5f, 0.f, 0.f);
	D3DXMATRIX		matPos;							// 移動用行列
	//	D3DXMATRIX		Rotation;
	//	D3DXMATRIX		tmpPos;
	D3DXMatrixIdentity(&matWorld);					// 単位行列
	//	D3DXMatrixRotationY(&Rotation, rotate * 3.141592f / 180.f);
	D3DXVec3TransformCoord(&vecTarget, &vecTarget, rotation);
	D3DXVec3Add(&vecTarget, &vecTarget, pos);
	D3DXMatrixTranslation(&matPos, vecTarget.x, vecTarget.y, vecTarget.z);
	//	tmpPos = Rotation;
	//	Rotation *= matPos;
	D3DXMatrixMultiply(&matWorld, &matWorld, rotation);
	//	matPos *= tmpPos;
	D3DXMatrixMultiply(&matWorld, &matWorld, &matPos);
	m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);


	//	下のやり方で〇速ってのが表現できる
	//	oldは前のフレームのもので前のフレームで行った変換情報も所持している
	/*
	D3DXMATRIX      matWorld;						// ワールド座標
	D3DXMATRIX		matPos;							// 移動用行列
	static bool first = true;
	D3DXMatrixIdentity(&matWorld);					// 単位行列
	D3DXMatrixTranslation(&matPos, pos.x, pos.y, pos.z);
	matPos *= matRotate;
	if (first)
	{
	D3DXMatrixMultiply(&matWorld, &matWorld, &matPos);
	first = false;
	}
	else
	{
	D3DXMatrixMultiply(&matWorld, &oldWorld, &matPos);
	}

	m_pD3Device->SetTransform(D3DTS_WORLD, &matWorld);
	oldWorld = matWorld;
	*/
}

