#pragma once

#include "basetoolsofplate.h"

class CConnectTool : public CBaseToolofPlate
{
	Q_OBJECT

public:
	CConnectTool();
	~CConnectTool();

public slots:
	void OnInitialize();

};
