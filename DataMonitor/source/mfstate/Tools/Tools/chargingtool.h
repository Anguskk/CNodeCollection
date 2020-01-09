#pragma once

#include "basetoolsofplate.h"

class CChargingTool : public CBaseToolofPlate
{
	Q_OBJECT

public:
	CChargingTool();
	~CChargingTool();

public slots:
	void OnInitialize();

};
