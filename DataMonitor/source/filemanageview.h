#pragma once

#include <QTreeView>

class CFileManageView : public QTreeView
{
	Q_OBJECT

public:
	CFileManageView(QWidget *parent);
	~CFileManageView();
};
