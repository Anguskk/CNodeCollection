#pragma once

#include "basetoolsofplate.h"

class CFirmwareUpgradeTool : public CBaseToolofPlate
{
	Q_OBJECT

public:
	CFirmwareUpgradeTool();
	~CFirmwareUpgradeTool();

public slots :
	void OnInitialize();

};
