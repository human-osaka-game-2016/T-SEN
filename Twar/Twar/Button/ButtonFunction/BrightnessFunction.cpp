//===================================================================================================================================//
//!< @file		BrightnessFunction.cpp	
//!< @brief		BrightnessFunctionクラス実装
//!< @author	hagas
//===================================================================================================================================//

//--------------------------------------------------------------------------------------------------------------//
//Includes
//--------------------------------------------------------------------------------------------------------------//

#include "BrightnessFunction.h"
#include "GameLib/GameLib.h"

//--------------------------------------------------------------------------------------------------------------//
//Unnamed namespace
//--------------------------------------------------------------------------------------------------------------//

namespace
{

const	DWORD   BrightnessValMax = 0xffffffff;		// 明度最大値

}

//--------------------------------------------------------------------------------------------------------------//
//Public functions
//--------------------------------------------------------------------------------------------------------------//

BrightnessFunction::BrightnessFunction(Button* pButton, DWORD brightnessVal)
	: ButtonFunction(pButton)
	, m_BrightnessVal(brightnessVal)
	, m_CorrectionBrightnessVal(brightnessVal)
{
}

BrightnessFunction::~BrightnessFunction()
{
	// pButtonのdeleteはButtonFunctionのデストラクタで行う
}

bool BrightnessFunction::Control()
{
	bool hasColliedMouse = m_pButton->Control();

	if(hasColliedMouse)
	{
		m_CorrectionBrightnessVal = BrightnessValMax;
	}
	else
	{
		m_CorrectionBrightnessVal = m_BrightnessVal;
	}

	return hasColliedMouse;
}

void BrightnessFunction::Draw()
{
	// 明度を変更する
	GameLib::Instance().SetVtxColor(m_pButton->GetVtxID(), m_CorrectionBrightnessVal);

	m_pButton->Draw();
}

//==================================================================================================================================//
//END OF FILE
//==================================================================================================================================//
