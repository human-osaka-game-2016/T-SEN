/**
* @file SceneFactory.h
* @brief  シーンを作成するクラスのh
* @author haga
*/
#ifndef SCENE_FACTORY_H
#define SCENE_FACTORY_H

class Scene;
class SaveDataManager;
/**
* シーンを作成するクラス
*/
class SceneFactory
{
public:
	/**
	* 実体を取得する関数<br>
	* Singletonパターン
	*/
	static SceneFactory& Instance()
	{
		static SceneFactory sceneFactory;

		return sceneFactory;
	}

	/**
	* 初期化関数
	* @param[in] saveDataManager セーブデータを管理するクラス
	*/
	void Init(SaveDataManager* saveDataManager);

	/**
	* シーン作成する関数
	* @param sceneID 作成したいシーンのID
	* @return pScene 作成したシーン
	*/
	Scene* CreateScene(SCENE_ID sceneID);

	/**デストラクタ*/
	~SceneFactory(){};

private:
	/**
	* コンストラクタ<br>
	* Singletonパターンの為private
	*/
	SceneFactory(){};
	SaveDataManager* m_pSaveDataManager;	 //!< セーブデータを管理するクラス
};

#endif // SCENE_FACTORY_H
