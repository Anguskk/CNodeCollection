#pragma once

#include "basetoolsofplate.h"

class CDownloadTool : public CBaseToolofPlate
{
	Q_OBJECT

public:
	CDownloadTool();
	~CDownloadTool();

public slots:
	void OnInitialize();

};
