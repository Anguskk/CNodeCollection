#pragma once

#include "basetoolsofplate.h"

class CSetupShelfTool : public CBaseToolofPlate
{
	Q_OBJECT

public:
	CSetupShelfTool();
	~CSetupShelfTool();

public slots :
	void OnInitialize();

};
