/**
* @file	DebugTimer.cpp
* @brief デバックの為の時間を計測するクラスのcpp
* @author haga
*/
#include <windows.h>
#include <string>
#include "DebugTimer.h"

// コンストラクタ
DebugTimer::DebugTimer()
{
}

// デストラクタ
DebugTimer::~DebugTimer()
{
	m_debugTime.clear();
}

// 計測する時間をセットする
void DebugTimer::SetDebugTimer(std::string  timeName)
{
	DebugTime temp;
	temp.timeName = timeName;
	temp.time = 0;
	temp.measureFlag = true;
	m_debugTime.push_back(temp);
}

// 時間計測開始
void DebugTimer::StartTimer(std::string  timeName)
{
	for (auto itr = m_debugTime.begin(); itr != m_debugTime.end(); itr++)
	{
		if (itr->timeName == timeName)
		{
			if (itr->measureFlag == true)
			{
				itr->time = timeGetTime();
			}
			break;
		}
	}
}

// 時間計測終了
void DebugTimer::EndTimer(std::string  timeName)
{
	DWORD currentTime = timeGetTime();
	for (auto itr = m_debugTime.begin(); itr != m_debugTime.end();itr++)
	{
		if (itr->timeName == timeName && itr->measureFlag == true)
		{
			currentTime -= itr->time;
			itr->time = currentTime;
			itr->measureFlag = false;
			break;
		}
	}
}

// 時間計測再計測
void DebugTimer::ReStart(std::string  timeName)
{
	for (auto itr = m_debugTime.begin(); itr != m_debugTime.end(); itr++)
	{
		if (itr->timeName == timeName)
		{
			if (itr->measureFlag == false)
			{
				itr->time = timeGetTime();
				itr->measureFlag = true;
			}
			break;
		}
	}
}

// 計測結果の取得
DWORD DebugTimer::GetResult(std::string  timeName)
{
	DWORD timeResult = 0;

	for (auto itr = m_debugTime.begin(); itr != m_debugTime.end(); itr++)
	{
		if (itr->timeName == timeName)
		{

			timeResult = itr->time;

			break;
		}
	}

	return timeResult;
}

// 計測結果表示
void DebugTimer::DrawResult(std::string  timeName, D3DXVECTOR2 pos)
{
	for (auto itr = m_debugTime.begin(); itr != m_debugTime.end(); itr++)
	{
		if (itr->timeName == timeName)
		{
			if (itr->measureFlag == false)
			{
				std::string  Str =
					timeName +":"+ std::to_string(itr->time) + "ミリ秒" +"\n";
				DebugFont timeDisp;
				timeDisp.Draw(Str.c_str(), pos);
			}
			break;
		}
	}
}


// 時間の総合計を表示する
void DebugTimer::DrawSumResult(D3DXVECTOR2 pos)
{
	DWORD TotalTime = 0;				// 時間を合計するための器

	for (auto i: m_debugTime)
	{
		if (i.measureFlag == false)		// 計測し終わっていたら加算する
		{
			TotalTime += i.time;
		}
	}

	std::string  Str =
		"合計時間は:" +  std::to_string(TotalTime) + "ミリ秒" + "\n";
	DebugFont timeDisp;
	timeDisp.Draw(Str.c_str(), pos);
}


// すべての計測時間と合計時間を表示する
void DebugTimer::DrawAllResult(D3DXVECTOR2 pos)
{
	DebugFont timeDisp;					// 表示用フォント
	int fontHeight = timeDisp.GetFontHeight();	// 1文字の高さ
	int dispCount = 0;							// 表示数

	for (auto i : m_debugTime)
	{
		if (i.measureFlag == false)
		{
			pos.y += (fontHeight * dispCount);				// 文字の高さ分座標をずらす
			std::string  Str =
				i.timeName + ":" + std::to_string(i.time) + "ミリ秒" + "\n";
			timeDisp.Draw(Str.c_str(), pos);
			dispCount++;
			
		}
	}

	// 1つでも結果表示しているなら総合計を表示する
	if (dispCount != 0)
	{
		pos.y += fontHeight;
		DrawSumResult(pos);
	}
	
}