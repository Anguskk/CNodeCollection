#pragma once

#include "basetoolsofplate.h"

class CAnnualInspectionReportTool : public CBaseToolofPlate
{
	Q_OBJECT

public:
	CAnnualInspectionReportTool();
	~CAnnualInspectionReportTool();

public slots:
	void OnInitialize();

};
