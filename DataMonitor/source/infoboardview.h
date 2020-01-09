#pragma once

#include <QListView>

class CInfoBoardView : public QListView
{
	Q_OBJECT

public:
	CInfoBoardView(QWidget *parent);
	~CInfoBoardView();
};
