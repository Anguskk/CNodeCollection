#pragma once

#include "basetoolsofplate.h"

class CSetupTool : public CBaseToolofPlate
{
	Q_OBJECT

public:
	CSetupTool();
	~CSetupTool();

public slots:
	void OnInitialize();

};
