/**
* @file Policy.cpp
* @brief Policyクラス実装
* @author haga
*/
#include "GameLib/GameLib.h"
#include "../../GameData/GameDataManager.h"
#include "../../GameData/GameTimer.h"
#include "Policy.h"
#include "PolicyMenu.h"
#include "PolicyBackGround.h"


namespace sub_scene
{

	Policy::Policy(GameDataManager* pGameDataManager, GameTimer* pGameTimer)
		: SubScene(pGameDataManager, pGameTimer)
		, m_pPolicyMenu(nullptr)
		, m_pPolicyBackGround(nullptr)
		, m_PolicyTextureWidth(2048.f)
		, m_PolicyTextureHeight(2048.f)
	{
		Init();
		m_pPolicyMenu = new PolicyMenu(pGameDataManager);
	}


	Policy::~Policy()
	{
		m_rGameLib.ReleaseAllVertex();
		m_rGameLib.ReleaseAllTex();
		delete m_pPolicyBackGround;
		delete m_pPolicyMenu;
	}

	SUBSCENE_ID Policy::Control()
	{
		SUBSCENE_ID nextSubSceneID=m_pPolicyMenu->Control();
		return nextSubSceneID;
	}

	void Policy::Draw()
	{
		m_pPolicyBackGround->Draw();
		m_pPolicyMenu->Draw();
	}

	void Policy::Init()
	{
		m_rGameLib.LoadTex(POLICY_TEX, "../Resouce/PolicyScene/seiryaku_0.png");
		m_rGameLib.LoadTex(BACKGROUND_TEX, "../Resouce/PolicyScene/background_1.png");
		m_rGameLib.LoadTex(LVUP_TEX,"../Resouce/PolicyScene/LvUPButton_1.png");
		m_rGameLib.LoadTex(CREATSHIP_TEX, "../Resouce/PolicyScene/CreatShipButton_1.png");

		// Policy::Policy_TEXのテクスチャーにおける位置座標
		D3DXVECTOR2		texPos[VTX_MAX] =
		{
			{ 0.0f, 0.0f },
			{ 0.0f, 840.f },
			{ 270.f, 840.f },
			{ 0.0f, 0.0f },
			{ 810.f, 0.0f },
			{ 0.0f, 1000.f },
			{ 200.f, 1000.f },
			{ 0.0f, 1130.f },
			{ 180.f, 1130.f },
			{ 1080.f, 0.f },
			{ 1410.f, 0.f },
			{ 1080.f, 210.f },
			{ 1080.f, 390.f },
			{ 1324.f, 390.f },
		};

		m_pPolicyBackGround = new PolicyBackGround(Policy::BACKGROUND_TEX,Policy::BACKGROUND_VTX);

		//ホームボタンVertex作成ブロック
		{
			float width = 270.f;
			float height = 160.f;
			m_rGameLib.CreateVtx(HOME_BUTTON_VTX, width, height);
			m_rGameLib.SetVtxUV(HOME_BUTTON_VTX, texPos[HOME_BUTTON_VTX].x / m_PolicyTextureWidth, (texPos[HOME_BUTTON_VTX].x + width) / m_PolicyTextureWidth,
				texPos[HOME_BUTTON_VTX].y / m_PolicyTextureHeight, (texPos[HOME_BUTTON_VTX].y + height) / m_PolicyTextureHeight);
		}

		//PUSH時ホームボタンVertex作成ブロック
		{
			float width = 270.f;
			float height = 160.f;
			m_rGameLib.CreateVtx(HOME_PUSH_BUTTON_VTX , width, height);
			m_rGameLib.SetVtxUV(HOME_PUSH_BUTTON_VTX , texPos[HOME_PUSH_BUTTON_VTX ].x / m_PolicyTextureWidth, (texPos[HOME_PUSH_BUTTON_VTX ].x + width) / m_PolicyTextureWidth,
				texPos[HOME_PUSH_BUTTON_VTX ].y / m_PolicyTextureHeight, (texPos[HOME_PUSH_BUTTON_VTX ].y + height) / m_PolicyTextureHeight);
		}

		//強化郡Vertex作成ブロック
		{
			float width = 810.f;
			float height = 840.f;
			m_rGameLib.CreateVtx(ENHANCEMENT_VTX, width, height);
			m_rGameLib.SetVtxUV(ENHANCEMENT_VTX, texPos[ENHANCEMENT_VTX].x / m_PolicyTextureWidth, (texPos[ENHANCEMENT_VTX].x + width) / m_PolicyTextureWidth,
				texPos[ENHANCEMENT_VTX].y / m_PolicyTextureHeight, (texPos[ENHANCEMENT_VTX].y + height) / m_PolicyTextureHeight);
		}
		//交流郡Vertex作成ブロック
		{
			float width = 270.f;
			float height = 665.f;
			m_rGameLib.CreateVtx(EXCHANGE_VTX, width, height);
			m_rGameLib.SetVtxUV(EXCHANGE_VTX, texPos[EXCHANGE_VTX].x / m_PolicyTextureWidth, (texPos[EXCHANGE_VTX].x + width) / m_PolicyTextureWidth,
				texPos[EXCHANGE_VTX].y / m_PolicyTextureHeight, (texPos[EXCHANGE_VTX].y + height) / m_PolicyTextureHeight);
		}
		//決済ボタンVertex作成ブロック
		{
			float width = 200.f;
			float height = 130.f;
			m_rGameLib.CreateVtx(SETTLEMENT_BUTTON_VTX, width, height);
			m_rGameLib.SetVtxUV(SETTLEMENT_BUTTON_VTX, texPos[SETTLEMENT_BUTTON_VTX].x / m_PolicyTextureWidth, (texPos[SETTLEMENT_BUTTON_VTX].x + width) / m_PolicyTextureWidth,
				texPos[SETTLEMENT_BUTTON_VTX].y / m_PolicyTextureHeight, (texPos[SETTLEMENT_BUTTON_VTX].y + height) / m_PolicyTextureHeight);
		}
		//PUSH時の決済ボタンVertex作成ブロック
		{
			float width = 200.f;
			float height = 130.f;
			m_rGameLib.CreateVtx(SETTLEMENT_PUSH_BUTTON_VTX, width, height);
			m_rGameLib.SetVtxUV(SETTLEMENT_BUTTON_VTX, texPos[SETTLEMENT_PUSH_BUTTON_VTX].x / m_PolicyTextureWidth, (texPos[SETTLEMENT_PUSH_BUTTON_VTX].x + width) / m_PolicyTextureWidth,
				texPos[SETTLEMENT_PUSH_BUTTON_VTX].y / m_PolicyTextureHeight, (texPos[SETTLEMENT_PUSH_BUTTON_VTX].y + height) / m_PolicyTextureHeight);
		}
		//キャンセルボタンVertex作成ブロック
		{
			float width = 180.f;
			float height = 100.f;
			m_rGameLib.CreateVtx(CANCELLATION_BUTTON_VTX, width, height);
			m_rGameLib.SetVtxUV(CANCELLATION_BUTTON_VTX, texPos[CANCELLATION_BUTTON_VTX].x / m_PolicyTextureWidth, (texPos[CANCELLATION_BUTTON_VTX].x + width) / m_PolicyTextureWidth,
				texPos[CANCELLATION_BUTTON_VTX].y / m_PolicyTextureHeight, (texPos[CANCELLATION_BUTTON_VTX].y + height) / m_PolicyTextureHeight);
		}
		//PUSH時のキャンセルボタンVertex作成ブロック
		{
			float width = 180.f;
			float height = 100.f;
			m_rGameLib.CreateVtx(CANCELLATION_PUSH_BUTTON_VTX, width, height);
			m_rGameLib.SetVtxUV(CANCELLATION_PUSH_BUTTON_VTX, texPos[CANCELLATION_PUSH_BUTTON_VTX].x / m_PolicyTextureWidth, (texPos[CANCELLATION_PUSH_BUTTON_VTX].x + width) / m_PolicyTextureWidth,
				texPos[CANCELLATION_PUSH_BUTTON_VTX].y / m_PolicyTextureHeight, (texPos[CANCELLATION_PUSH_BUTTON_VTX].y + height) / m_PolicyTextureHeight);
		}
		//
		{
			float width = 330.f;
			float height = 210.f;
			m_rGameLib.CreateVtx(MYMONEY_VTX, width, height);
			m_rGameLib.SetVtxUV(MYMONEY_VTX, texPos[MYMONEY_VTX].x / m_PolicyTextureWidth, (texPos[MYMONEY_VTX].x + width) / m_PolicyTextureWidth,
				texPos[MYMONEY_VTX].y / m_PolicyTextureHeight, (texPos[MYMONEY_VTX].y + height) / m_PolicyTextureHeight);
		}
		//合計金額Vertex作成ブロック
		{
			float width = 330.f;
			float height = 210.f;
			m_rGameLib.CreateVtx(SUMMONEY_VTX, width, height);
			m_rGameLib.SetVtxUV(SUMMONEY_VTX, texPos[SUMMONEY_VTX].x / m_PolicyTextureWidth, (texPos[SUMMONEY_VTX].x + width) / m_PolicyTextureWidth,
				texPos[SUMMONEY_VTX].y / m_PolicyTextureHeight, (texPos[SUMMONEY_VTX].y + height) / m_PolicyTextureHeight);
		}
		//政略Vertex作成ブロック
		{
			float width = 300.f;
			float height = 120.f;
			m_rGameLib.CreateVtx(POLICY_VTX, width, height);
			m_rGameLib.SetVtxUV(POLICY_VTX, texPos[POLICY_VTX].x / m_PolicyTextureWidth, (texPos[POLICY_VTX].x + width) / m_PolicyTextureWidth,
				texPos[POLICY_VTX].y / m_PolicyTextureHeight, (texPos[POLICY_VTX].y + height) / m_PolicyTextureHeight);
		}

		//強化フィルターVertex作成ブロック
		{
			float width = 244.f;
			float height = 169.f;
			m_rGameLib.CreateVtx(ENHANCEMENT_FILTER_VTX, width, height);
			m_rGameLib.SetVtxUV(ENHANCEMENT_FILTER_VTX, texPos[ENHANCEMENT_FILTER_VTX].x / m_PolicyTextureWidth, (texPos[ENHANCEMENT_FILTER_VTX].x + width) / m_PolicyTextureWidth,
				texPos[ENHANCEMENT_FILTER_VTX].y / m_PolicyTextureHeight, (texPos[ENHANCEMENT_FILTER_VTX].y + height) / m_PolicyTextureHeight);
		}

		//交流フィルターVertex作成ブロック
		{
			float width = 244.f;
			float height = 169.f;
			m_rGameLib.CreateVtx(EXCHANGE_FILTER_VTX, width, height);
			m_rGameLib.SetVtxUV(EXCHANGE_FILTER_VTX, texPos[EXCHANGE_FILTER_VTX].x / m_PolicyTextureWidth, (texPos[EXCHANGE_FILTER_VTX].x + width) / m_PolicyTextureWidth,
				texPos[EXCHANGE_FILTER_VTX].y / m_PolicyTextureHeight, (texPos[EXCHANGE_FILTER_VTX].y + height) / m_PolicyTextureHeight);
		}

		//LvupVertex作成ブロック
		{
			float width = 90.f;
			float height = 50.f;
			m_rGameLib.CreateVtx(LVUP_VTX, width, height);
		}

		//造船Vertex作成ブロック
		{
			float width = 100.f;
			float height = 70.f;
			m_rGameLib.CreateVtx(CREATSHIP_VTX, width, height);
		}
	}
}

