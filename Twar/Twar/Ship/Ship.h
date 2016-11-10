#ifndef SHIP_H
#define	SHIP_H

#include "fbx/FbxRelated.h"
#include "../CameraController/CameraController.h"
//#include "ShipManager.h"
#include "GameLib/Lib/GraphicsDevice.h"
#include "GameLib/Lib/InputKey.h"
#include "GameLib/Lib/InputMouse.h"



class Ship
{
	friend class ShipManager;

protected:
	typedef struct STATUS
	{
		int m_hp;
		float m_speed;
	}Status;

	enum ATTR
	{
		PLAYER,
		ALLY,
		ENEMY
	};

	IDirect3DDevice9*		m_pD3Device;			//!< Direct3Dのデバイス
	D3DXVECTOR3		        m_ObjPos;				//!< 座標
	CameraController*		m_pcameraController;				//!< カメラコントローラー
//	ClickPosConverter		m_clickPosConverter;
	FbxModel*				m_pFbx;
	ATTR					m_Attr;
	InputKey				m_InputKey;
	InputMouse				m_Mouse;				//!< マウス
	D3DXMATRIX				m_Rotation;
	int						m_Rotate;

	virtual void Player() = 0;
	virtual void Ally() = 0;
	virtual void Enemy() = 0;

private:

	

public:
	Ship(D3DXVECTOR3* pos);
	~Ship();
	virtual void Draw();
	virtual void Control();
	void TransWorld(const D3DXVECTOR3* pos, const D3DXMATRIX* rotation);
};

#endif	//	SHIP_H