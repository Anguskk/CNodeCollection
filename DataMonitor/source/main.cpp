#include <QApplication>

#include "mainadvisor.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainAdvisor advisor;	  //主方法指导器，用于加载插件和启动工作台
	advisor.start(argc == 1);

	return a.exec();
}
