#pragma once

#include "basetoolsofplate.h"

class CAnnualInspectionDownloadTool : public CBaseToolofPlate
{
	Q_OBJECT

public:
	CAnnualInspectionDownloadTool();
	~CAnnualInspectionDownloadTool();

public slots:
	void OnInitialize();
};
