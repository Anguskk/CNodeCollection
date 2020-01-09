#pragma once
#include "basetoolsofplate.h"

class CAboutTools :public CBaseToolofPlate
{
	Q_OBJECT
protected slots:
	void OnInitialize();
public:
	CAboutTools(void){};
	~CAboutTools(void){};
};

