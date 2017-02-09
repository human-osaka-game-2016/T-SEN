/**
* @file Alignment.h
* @brief Alignmentクラスヘッダ
* @author haga
*/

#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include "UI.h"
class Alignment : public UI
{
public:

	Alignment(int texID, int zoomTexID, int vtxID);

	virtual ~Alignment();

	virtual void Control();
	virtual void Draw();

private:
	int				m_TexID;
	int				m_ZoomTexID;
	int				m_VtxID;
};

#endif // ALIGNMENT_H
