//================================================================================================================================//
//!< @file		ScaleFunction.cpp
//!< @brief		ScaleFunctionクラス実装
//!< @author	haga
//================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "ScaleFunction.h"
#include "GameLib/GameLib.h"

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

ScaleFunction::ScaleFunction(Button* pButton, float scaleVal)
	: ButtonFunction(pButton)
	, m_ScaleVal(scaleVal)
	, m_CorrectionScaleVal(0.0f)
{
}

ScaleFunction::~ScaleFunction()
{
	// pButtonのdeleteはButtonFunctionのデストラクタで行う
}

bool ScaleFunction::Control()
{
	bool hasColliedMouse = m_pButton->Control();

	if(hasColliedMouse)
	{
		m_CorrectionScaleVal = m_ScaleVal;
	}
	else
	{
		m_CorrectionScaleVal = 0.0f;
	}

	return hasColliedMouse;
}

void ScaleFunction::Draw()
{
	// ボタンに補正値を足してサイズを変更する
	{
		float buttonWidth = m_pButton->GetButtonWidth() + m_CorrectionScaleVal;
		float buttonHeight = m_pButton->GetButtonHeight() + m_CorrectionScaleVal;
		GameLib::Instance().SetVtxSize(m_pButton->GetVtxID(), buttonWidth, buttonHeight);
	}

	m_pButton->Draw();
}

//=============================================================================================================================//
//END OF FILE
//=============================================================================================================================//
