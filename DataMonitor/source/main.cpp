#include <QApplication>

#include "mainadvisor.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	MainAdvisor advisor;	  //������ָ���������ڼ��ز������������̨
	advisor.start(argc == 1);

	return a.exec();
}
