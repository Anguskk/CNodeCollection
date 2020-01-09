#pragma once

#include "basetoolsofplate.h"

class CAnnualInspectionTool : public CBaseToolofPlate
{
	Q_OBJECT

public:
	CAnnualInspectionTool();
	~CAnnualInspectionTool();

public slots:
	void OnInitialize();

};
