/**
* @file		TitleCommonDeclaration.h
* @brief	TitleSceneで使用されるenumなどをまとめたファイル
* @author	haga
*/

#ifndef TITLE_COMMON_DECLARATION_H
#define TITLE_COMMON_DECLARATION_H

/**TitleSceneで使用するenum*/
namespace title_enum
{

/**TextureID*/
enum TEXTURE_ID
{
	BACKGROUND_TEX,			//!< タイトル背景
	LOGO_TEX,				//!< タイトルロゴ
	BUTTON_TEX,				//!< タイトルで使用するボタン
	SAVE_DATA_TEX,			//!< セーブデータスロット関連
	TEX_MAX
};

/**VertexID*/
enum VERTEX_ID
{
	BACKGROUND_VTX,				//!< タイトル背景
	LOGO_VTX,					//!< タイトルロゴ
	START_BTN_VTX,				//!< スタートボタン
	CONTINUE_BTN_VTX,			//!< コンティニューボタン
	RETURN_BTN_VTX,				//!< 戻るボタン(セーブ画面で使用する)
	SAVE_SLOT_VTX,				//!< セーブスロット
	AUTO_SAVE_VTX,				//!< オートセーブスロット
	SAVE_DATA_VTX,				//!< 現在選んでいるセーブデータを表示する画面 
	VTX_MAX			
};

}

#endif	// TITLE_COMMON_DECLARATION_H
