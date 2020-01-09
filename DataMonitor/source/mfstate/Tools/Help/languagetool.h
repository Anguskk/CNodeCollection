#ifndef CLANGUAGETOOL_H
#define CLANGUAGETOOL_H

#include "basetoolsofplate.h"

class CLanguageTool : public CBaseToolofPlate
{
	Q_OBJECT

public:
	CLanguageTool();
	~CLanguageTool();

public slots:
	void OnInitialize();
};

#endif // LICENSETOOL_H
