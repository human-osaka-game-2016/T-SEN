/**
* @file		TitleCommonDeclaration.h
* @brief	TitleSceneで使用されるenumなどをまとめたファイル
* @author	haga
*/

#ifndef TITLE_COMMON_DECLARATION_H
#define TITLE_COMMON_DECLARATION_H

namespace title_scene
{

/**TextureID*/
enum TEXTURE_ID
{
	TITLE_BACKGROUND,		//!< タイトル背景
	TITLE_LOGO,				//!< タイトルロゴ
	TITLE_BUTTON,			//!< タイトルで使用するボタン
	SAVE_SLOT,				//!< セーブデータスロット関連
	TEX_MAX
};

/**VertexID*/
enum VERTEX_ID
{
	BACKGROUND,				//!< タイトル背景
	LOGO,					//!< タイトルロゴ
	START_BTN,				//!< スタートボタン
	CONTINUE_BTN,			//!< コンティニューボタン
	RETURN_BTN,				//!< 戻るボタン(セーブ画面で使用する)
	SAVE_SLOT,				//!< セーブスロット
	AUTO_SAVE_SLOT,			//!< オートセーブスロット
	SAVE_DATA_DISPLAY,		//!< 現在選んでいるセーブデータを表示する画面 
	VTX_MAX			
};

}

#endif	// TITLE_COMMON_DECLARATION_H
