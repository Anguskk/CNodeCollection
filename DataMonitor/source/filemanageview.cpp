#include "filemanageview.h"

#include <QFileSystemModel>

CFileManageView::CFileManageView(QWidget *parent)
	: QTreeView(parent)
{
	auto *model = new QFileSystemModel;
	model->setRootPath(QDir::currentPath());
	setModel(model);
}

CFileManageView::~CFileManageView()
{
}
