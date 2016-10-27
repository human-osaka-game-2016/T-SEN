/**
* @file XFileManager.h
* @brief Xファイルを一括で扱うクラスのh
* @haga
*/
#ifndef XFILE_MANAGER_H
#define XFILE_MANAGER_H

#include <d3dx9.h>
#include <map>


class XFile;

class XFileManager
{
private:
	std::map<int,XFile>  m_xFile;	//!< Xファイルを格納する変数

public:
	/**コンストラクタ*/
	XFileManager();
	/**デストラクタ*/
	~XFileManager();

	/**
	* Xファイルをロードする関数
	* @param[in] key 登録するキー
	* @param[in] pFilePath ファイル名
	*/
	void Load(int key,LPCTSTR pFilePath);

	/**
	* Xファイルを描画する関数
	* @param[in] key 登録したキー
	*/
	void Draw(int key);

	/**
	* Xファイルを解放する関数
	* @param[in] key 登録したキー
	*/
	void Release(int key);

	/**
	* マネージャーが管理しているすべてのファイルを解放する関数
	*/
	void ReleaseALL();
};

#endif	// XFILE_MANAGER_H

