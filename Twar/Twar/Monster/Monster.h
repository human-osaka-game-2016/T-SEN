/**
* @file		Monster.h
* @brief	Monsterクラスヘッダ
* @author	haga
* @todo		現在まだ実装できていない部分がある
*/

#ifndef MONSTER_H
#define MONSTER_H

#include <d3dx9.h>
#include <vector>

class Collision;
class FbxModel;

/***
* 敵であるモンスターのクラス
*/
class Monster
{
public:
	/**
	* コンストラクタ
	* @param model	FbxModelクラスのインスタンスへのポインタ
	*/
	Monster(FbxModel* model);

	/**デストラクタ*/
	~Monster();

	/**
	* コントロール関数
	* @return 消滅したかどうか
	*/
	bool Control();

	/**描画関数*/
	void Draw();

private:

	/***ステータス(仮置き)*/
	struct STATUS
	{
		int Hp;				//!< HP
		int Power;			//!< 攻撃力
		int AttackInteval;	//!< 攻撃間隔
	};

	/**状態*/
	enum STATE
	{
		STANDBY,			//!< 待機
		COMBAT,				//!< 戦闘
		MOVING,				//!< 移動
		DEATH,				//!< 死亡
	};

	D3DXVECTOR3						m_Pos;						//!< 位置座標
	D3DXMATRIX						m_MatWorld;					//!< ワールド変換行列
	float							m_Angle;					//!< 角度(向く方向)
	FbxModel*						m_pModel;					//!< モデルデータ
	Collision*						m_Collision;				//!< 衝突クラス
	Monster::STATUS					m_Status;					//!< ステータス
	Monster::STATE					m_State;					//!< 敵の状態
	int								m_AttackInterValCount;		//!< 攻撃間隔をカウント	
	int								m_NonAttackTimeCount;		//!< 攻撃していないときをカウント
	int								m_MoveTimeCount;			//!< 移動時間をカウント
	bool							m_IsMoving;					//!< 移動したかどうか
	int								m_FadeOutTimeCount;			//!< HPが0になった後海中に消えて行く時間をカウント
	bool							m_HasDisappeared;			//!< 消滅したかどうか
	//std::vector<MonsterBullet*>	m_pBullet;					//!< モンスターの発射する弾
	//Collision*					m_pCollision				//!< 衝突判定を行うためのクラスへのインスタンス

	/**衝突を判断する関数*/
	void	JudgeColllision();

	/**索敵する関数*/
	void	SearchTarget();

	/**攻撃を行う関数*/
	void	AttackTarget();

	/**移動を行う関数*/
	void	Move();

	/**沈む行動を行う関数*/
	void	Fall();

	/**浮上する関数*/
	void	Rise();

	/**姿勢制御関数*/
	void	ControlAttitude();

	/**
	* 平行移動関数.
	* @param x	x座標における移動量
	* @param y	y座標における移動量
	* @param z	z座標における移動量
	*/
	void MoveParallel(float x, float y, float z);

};

#endif	// MONSTER_H
