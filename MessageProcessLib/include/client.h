#pragma once

#include <QVector>
#include <QString>

#include "messagesdefinition.h"

#include "messageprocesslib_global.h"

typedef enum
{
	ENTER_USR_NAME,
	ENTER_USR_PWD,
	INPUT_INSTRUCTION_MACADD,
	INPUT_INSTRUCTION_ARP,
	INPUT_INSTRUCTION_PING,
	PARSE_STRING
}StateTypeDef;

//static void ResponseToServer(int, unsigned char *, int);
//struct Node *QueryMacAddFromSwitch(const char *);
MESSAGEPROCESSLIB_EXPORT QVector<SNodeInfo> getNodeInfo(const QVector<ShelfInfoOld> &shelfs, const QString &mainMAC);
MESSAGEPROCESSLIB_EXPORT QVector<ShelfInfoOld> getShelfInfo(const QString &serverIP, const QString &mainIP, const QVector<QString> &shelfIPs, QString &mainMAC);
MESSAGEPROCESSLIB_EXPORT bool scanIPs(const QString &mainIP, const QVector<QString> &shelfIPs);

MESSAGEPROCESSLIB_EXPORT QVector<SNodeInfo> getNodeInfo(const QVector<ShelfInfo> &shelfs);
