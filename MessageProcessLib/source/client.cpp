#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<winsock2.h>
#include<windows.h>
#include "include/client.h"

#include <QProcess>

#pragma comment(lib, "ws2_32.lib")
//#define _CRT_SECURE_NO_WARNINGS 1
//#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#define BUFLEN				2048
#define CONNECT_TIME_OUT	(500L * 1000) //unit: us
//#define COL_OF_ONE_LN		81	//column of one line including '\r' and '\n'
/* telnet protocol code */
#define CMD					0xff
//IAC
#define IAC					255
//command code
#define SE					240
#define SB					250
#define WILL				251
#define WONT				252
#define DO					253
#define DONT				254
//option code
#define ECHO				1
#define SUPPRESS_GO_AHEAD	3
#define TEMINAL_TYPE		24
#define ESCAPE				27
#define WINDOW_SIZE			31
#define TERMIANL_SPEED		32

static const char SERVER_PORT_NUM[]	= { "23" };
static const char LOGIN_NAME_BUF[]	= { "root\r\n" };
static const char LOGIN_PWD_BUF[]	= { "rfpesl61831171\r\n" };
static const char INS_DIS_MAC_ADD[]	= { "display mac-address\r\n" };
static const char INS_DIS_ARP[]		= { "display arp\r\n" };
static const char CR_LF[]			= { "\r\n" };

static StateTypeDef state;

static void ResponseToServer(int sock, char *ptrBuf, int len) //待wireshark抓包确认一下
{
	int arrayPos = 0;
	char *cmdPos = 0;
	char *addZeroPos = 0;
	unsigned char sendBuf[BUFLEN] = { '\0' };
	while ((cmdPos = strchr(ptrBuf, IAC)) != NULL)
	{
		if (*cmdPos == IAC && *(cmdPos + 1) == WILL && *(cmdPos + 2) == ECHO)
		{
			sendBuf[arrayPos++] = IAC;
			sendBuf[arrayPos++] = DO;
			sendBuf[arrayPos++] = ECHO;
		}
		if (*cmdPos == IAC && *(cmdPos + 1) == WILL && *(cmdPos + 2) == SUPPRESS_GO_AHEAD)
		{
			sendBuf[arrayPos++] = IAC;
			sendBuf[arrayPos++] = DO;
			sendBuf[arrayPos++] = SUPPRESS_GO_AHEAD;
		}
		if (*cmdPos == IAC && *(cmdPos + 1) == DO && *(cmdPos + 2) == TEMINAL_TYPE)
		{
			sendBuf[arrayPos++] = IAC;
			sendBuf[arrayPos++] = WONT;
			sendBuf[arrayPos++] = TEMINAL_TYPE;
		}
		if (*cmdPos == IAC && *(cmdPos + 1) == DO && *(cmdPos + 2) == WINDOW_SIZE)
		{
			sendBuf[arrayPos++] = IAC;
			sendBuf[arrayPos++] = WONT;
			sendBuf[arrayPos++] = WINDOW_SIZE;
		}
		if (*cmdPos == IAC && *(cmdPos + 1) == DONT && *(cmdPos + 2) == TEMINAL_TYPE)
		{
			sendBuf[arrayPos++] = IAC;
			sendBuf[arrayPos++] = WONT;
			sendBuf[arrayPos++] = TEMINAL_TYPE;
		}
		if (*cmdPos == IAC && *(cmdPos + 1) == DONT && *(cmdPos + 2) == WINDOW_SIZE)
		{
			sendBuf[arrayPos++] = IAC;
			sendBuf[arrayPos++] = WONT;
			sendBuf[arrayPos++] = WINDOW_SIZE;
		}
		//override the cmd in msg
		memcpy(cmdPos, cmdPos + 3, strlen(cmdPos) - 3);
		addZeroPos = cmdPos + strlen(cmdPos) - 3;
		*(addZeroPos) = '\0';
		*(addZeroPos + 1) = '\0';
		*(addZeroPos + 2) = '\0';
	}
	if (send(sock, (char *)sendBuf, strlen((char *)sendBuf), 0) < 0)
	{
		perror("\nsend failed");
		exit(1);
	}
	/*
	if(*cmdPos == IAC && *(cmdPos + 1) == DO && *(cmdPos + 2) == WINDOW_SIZE)
	{
		sendBuf[arrayPos++] = IAC;
		sendBuf[arrayPos++] = WILL;
		sendBuf[arrayPos++] = WINDOW_SIZE;
		if(send(sock, sendBuf, 3, 0) < 0)
		{
			perror("send failed\n");
			exit(1);
		}
		sendBuf[arrayPos++] = IAC;
		sendBuf[arrayPos++] = SB;
		sendBuf[arrayPos++] = WINDOW_SIZE;
		sendBuf[arrayPos++] = 0;
		sendBuf[arrayPos++] = 80;
		sendBuf[arrayPos++] = 0;
		sendBuf[arrayPos++] = 24;
		sendBuf[arrayPos++] = IAC;
		sendBuf[arrayPos++] = SE;
		if(send(sock, sendBuf, 9, 0) < 0)
		{
			perror("send failed\n");
			exit(1);
		}
	}
	*/
}

QVector<SNodeInfo> getNodeInfoByShelf(const QString shelfIP, const QString &mainMAC)
{
	QVector<SNodeInfo> curNode;
	SNodeInfo tmpNodeInfo;
	/* Connect to Server */
	SOCKET sockfd;
	int port = atoi(SERVER_PORT_NUM);
	struct sockaddr_in serverAddr;
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return curNode;
	}
	//creat socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("\ncreate socket failed");
		return curNode;
	}
	//connect
	memset(&serverAddr, 0, sizeof(struct sockaddr_in));
	serverAddr.sin_addr.S_un.S_addr = inet_addr(shelfIP.toStdString().c_str());
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in)) < 0)
	{
		perror("\nconnect failed");
		return curNode;
	}

	/* Telnet to Server */
	int recvLen;
	char recvBuf[BUFLEN] = { '\0' };
	int numberOfItems = 0;
	char *ptrStrPos;
	state = ENTER_USR_NAME;
	while (1)
	{
		//recv msg
		memset(recvBuf, '\0', BUFLEN);
		recvLen = recv(sockfd, recvBuf, BUFLEN, 0);
		if (recvLen < 0)
		{
			perror("\nrecv failed");
			return curNode;
		}
		if (recvLen == 0)
		{
			printf("server closed socket\n");
			return curNode;
		}
		if (recvLen > 0)
		{
			//resolve protocol
			if (strchr(recvBuf, CMD) != NULL)
			{
				ResponseToServer(sockfd, recvBuf, strlen(recvBuf));
			}
			//FSM
			switch (state)
			{
			case ENTER_USR_NAME:
				if (strstr(recvBuf, "Username:") != NULL)
				{
					if (send(sockfd, LOGIN_NAME_BUF, strlen(LOGIN_NAME_BUF), 0) < 0)
					{
						perror("\nsend failed");
						return curNode;
					}
					state = ENTER_USR_PWD;
				}
				break;
			case ENTER_USR_PWD:
				if (strstr(recvBuf, "Password:") != NULL)
				{
					if (send(sockfd, LOGIN_PWD_BUF, strlen(LOGIN_PWD_BUF), 0) < 0)
					{
						perror("\nsend failed");
						return curNode;
					}
					state = INPUT_INSTRUCTION_MACADD;
				}
				break;
			case INPUT_INSTRUCTION_MACADD:
				//get mac address
				if (strstr(recvBuf, "<") != NULL)
				{
					if (send(sockfd, INS_DIS_MAC_ADD, strlen(INS_DIS_MAC_ADD), 0) < 0)
					{
						perror("\nsend failed");
						return curNode;
					}
					state = PARSE_STRING;
					Sleep(100); //need to delay 100ms for waiting all of messages
				}
				//solve error circumstance
				else if (strstr(recvBuf, "Authentication fail") != NULL)
				{
					Sleep(2 * 1000); //need to sleep 2 seconds
					if (send(sockfd, CR_LF, strlen(CR_LF), 0) < 0)
					{
						perror("\nsend failed");
						return curNode;
					}
					state = ENTER_USR_NAME;
				}
				break;
			case PARSE_STRING:
				//get mac-address and port number
				if ((ptrStrPos = strstr(recvBuf, "Total items displayed = ")) != NULL)
				{
					QTextStream dataStream(QByteArray(recvBuf), QIODevice::ReadOnly);
					int startFlag = 0, nodeID = -1;
					while (!dataStream.atEnd())
					{
						QString t_lineStr = dataStream.readLine();
						if (startFlag < 2 && !t_lineStr.isEmpty() && t_lineStr[0] == '-')
						{
							startFlag++;
							continue;
						}
						if (startFlag < 2)
							continue;
						if (startFlag == 2 && !t_lineStr.isEmpty() && t_lineStr[0] == '-')
							break;
						QStringList t_curStrList = t_lineStr.split(" ", QString::SkipEmptyParts);
						if (t_curStrList.size() >= 4)
						{
							tmpNodeInfo.macAddress = t_curStrList[0].split("-", QString::SkipEmptyParts).join("");
							tmpNodeInfo.nodeID = t_curStrList[2].split("/", QString::SkipEmptyParts).last().toInt();
							if (tmpNodeInfo.macAddress == mainMAC)
							{
								nodeID = tmpNodeInfo.nodeID;
							}
							curNode.append(tmpNodeInfo);
						}
					}
					for (int i = curNode.size() - 1; i >= 0; --i)
					{
						if (curNode[i].nodeID == nodeID)
							curNode.removeAt(i);
					}
				}
				closesocket(sockfd);
				WSACleanup();
				return curNode;
				break;
			default:
				break;
			}
		}
	}
}

QVector<SNodeInfo> getNodeInfo(const QVector<ShelfInfoOld> &shelfs, const QString &mainMAC)
{
	QVector<SNodeInfo> nodes;
	for (const auto& curShelfInfo : shelfs)
	{
		QVector<SNodeInfo> curNodeInfo;
		curNodeInfo = getNodeInfoByShelf(curShelfInfo.ipAddress, mainMAC);
		for (auto curNode : curNodeInfo)
		{
			curNode.shelfID = curShelfInfo.shelfID;
			nodes.append(curNode);
		}
	}
	return nodes;
}

QVector<ShelfInfoOld> getShelfInfo(const QString &serverIP, const QString &mainIP, const QVector<QString> &shelfIPs, QString &mainMAC)
{
	QVector<ShelfInfoOld> shelfs;
	ShelfInfoOld tmpShelfInfo;
	/* Connect to Server */
	SOCKET sockfd;
	int port = atoi(SERVER_PORT_NUM);
	struct sockaddr_in serverAddr;
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return shelfs;
	}
	//creat socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("\ncreate socket failed");
		return shelfs;
	}
	//connect
	memset(&serverAddr, 0, sizeof(struct sockaddr_in));
	serverAddr.sin_addr.S_un.S_addr = inet_addr(mainIP.toStdString().c_str());
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in)) < 0)
	{
		perror("\nconnect failed");
		return shelfs;
	}
	/* Telnet to Server */
	int recvLen;
	char recvBuf[BUFLEN] = { '\0' };
	int numberOfItems = 0;
	char *ptrStrPos;
	state = ENTER_USR_NAME;
	while (1)
	{
		//recv msg
		memset(recvBuf, '\0', BUFLEN);
		recvLen = recv(sockfd, recvBuf, BUFLEN, 0);
		if (recvLen < 0)
		{
			perror("\nrecv failed");
			return shelfs;
		}
		if (recvLen == 0)
		{
			printf("server closed socket\n");
			return shelfs;
		}
		if (recvLen > 0)
		{
			//resolve protocol
			if (strchr(recvBuf, CMD) != NULL)
			{
				ResponseToServer(sockfd, recvBuf, strlen(recvBuf));
			}
			//FSM
			switch (state)
			{
			case ENTER_USR_NAME:
				if (strstr(recvBuf, "Username:") != NULL)
				{
					if (send(sockfd, LOGIN_NAME_BUF, strlen(LOGIN_NAME_BUF), 0) < 0)
					{
						perror("\nsend failed");
						return shelfs;
					}
					state = ENTER_USR_PWD;
				}
				break;
			case ENTER_USR_PWD:
				if (strstr(recvBuf, "Password:") != NULL)
				{
					if (send(sockfd, LOGIN_PWD_BUF, strlen(LOGIN_PWD_BUF), 0) < 0)
					{
						perror("\nsend failed");
						return shelfs;
					}
					state = INPUT_INSTRUCTION_ARP;
				}
				break;
			case INPUT_INSTRUCTION_ARP:
				if (strstr(recvBuf, "<") != NULL)
				{
					if (send(sockfd, INS_DIS_ARP, strlen(INS_DIS_ARP), 0) < 0)
					{
						perror("\nsend failed");
						return shelfs;
					}
					state = PARSE_STRING;
					Sleep(100); //whether to sleep or not
				}
				else if (strstr(recvBuf, "Authentication fail") != NULL)
				{
					Sleep(2 * 1000);
					if (send(sockfd, CR_LF, strlen(CR_LF), 0) < 0)
					{
						perror("\nsend failed");
						return shelfs;
					}
					state = ENTER_USR_NAME;
				}
				break;
			case PARSE_STRING:
				//get IP, mac-address and GE
				if ((ptrStrPos = strstr(recvBuf, "Total:")) != NULL)
				{
					QTextStream dataStream(QByteArray(recvBuf), QIODevice::ReadOnly);
					bool startFlag = false;
					while (!dataStream.atEnd())
					{
						QString t_lineStr = dataStream.readLine();
						if (!startFlag && !t_lineStr.isEmpty() && t_lineStr[0] == '-')
						{
							startFlag = true;
							continue;
						}
						if (!startFlag)
							continue;
						if (startFlag && !t_lineStr.isEmpty() && t_lineStr[0] == '-')
							break;
						QStringList t_curStrList = t_lineStr.split(" ", QString::SkipEmptyParts);
						if (t_curStrList.size() >= 5)
						{
							if (t_curStrList[4] != QString("Vlanif1") && t_curStrList[0] != serverIP && shelfIPs.contains(t_curStrList[0])) //except main shelf's IP and server's IP 
							{
								tmpShelfInfo.ipAddress = t_curStrList[0];
								tmpShelfInfo.macAddress = t_curStrList[1].split("-", QString::SkipEmptyParts).join("");
								QStringList t_shelfID = t_curStrList[4].split("/", QString::SkipEmptyParts);
								tmpShelfInfo.shelfID = t_shelfID.last().toInt();
								shelfs.append(tmpShelfInfo);
							}
							else if (t_curStrList[0] == serverIP)//(t_curStrList[4] == QString("Vlanif1"))
							{
								mainMAC = t_curStrList[1].split("-", QString::SkipEmptyParts).join("");
							}
						}
					}
					closesocket(sockfd);
					WSACleanup();
					return shelfs;
				}
				break;
			default:
				break;
			}
		}
	}
}

bool scanIPs(const QString &mainIP, const QVector<QString> &shelfIPs)
{
	bool status = false;
	int i = 0;
	/* Connect to Server */
	SOCKET sockfd;
	int port = atoi(SERVER_PORT_NUM);
	struct sockaddr_in serverAddr;
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return status;
	}
	//creat socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("\ncreate socket failed");
		return status;
	}
	//connect
	memset(&serverAddr, 0, sizeof(struct sockaddr_in));
	serverAddr.sin_addr.S_un.S_addr = inet_addr(mainIP.toStdString().c_str());
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in)) < 0)
	{
		perror("\nconnect failed");
		return status;
	}
	/* Telnet to Server */
	int recvLen;
	char recvBuf[BUFLEN] = { '\0' };
	int numberOfItems = 0;
	char *ptrStrPos;
	state = ENTER_USR_NAME;
	while (1)
	{
		//recv msg
		memset(recvBuf, '\0', BUFLEN);
		recvLen = recv(sockfd, recvBuf, BUFLEN, 0);
		if (recvLen < 0)
		{
			perror("\nrecv failed");
			return status;
		}
		if (recvLen == 0)
		{
			printf("server closed socket\n");
			return status;
		}
		if (recvLen > 0)
		{
			//resolve protocol
			if (strchr(recvBuf, CMD) != NULL)
			{
				ResponseToServer(sockfd, recvBuf, strlen(recvBuf));
			}
			//FSM
			switch (state)
			{
			case ENTER_USR_NAME:
				if (strstr(recvBuf, "Username:") != NULL)
				{
					if (send(sockfd, LOGIN_NAME_BUF, strlen(LOGIN_NAME_BUF), 0) < 0)
					{
						perror("\nsend failed");
						return status;
					}
					state = ENTER_USR_PWD;
				}
				break;
			case ENTER_USR_PWD:
				if (strstr(recvBuf, "Password:") != NULL)
				{
					if (send(sockfd, LOGIN_PWD_BUF, strlen(LOGIN_PWD_BUF), 0) < 0)
					{
						perror("\nsend failed");
						return status;
					}
					state = INPUT_INSTRUCTION_PING;
				}
				break;
			case INPUT_INSTRUCTION_PING:
				if (strstr(recvBuf, "<") != NULL)
				{
					if (i == shelfIPs.size())
					{
						status = true;
						return status;
					}
					QString pingStr = QString("ping -c 1 -t 500 %1").arg(shelfIPs[i]);
					if (send(sockfd, pingStr.toStdString().c_str(), strlen(pingStr.toStdString().c_str()), 0) < 0)
					{
						perror("\nsend failed");
						return status;
					}
					if (send(sockfd, CR_LF, strlen(CR_LF), 0) < 0)
					{
						perror("\nsend failed");
						return status;
					}
					i++;
				}
				else if (strstr(recvBuf, "Authentication fail") != NULL)
				{
					Sleep(2 * 1000);
					if (send(sockfd, CR_LF, strlen(CR_LF), 0) < 0)
					{
						perror("\nsend failed");
						return status;
					}
					state = ENTER_USR_NAME;
				}
				break;
			default:
				break;
			}
		}
	}
}

QVector<SNodeInfo> getNodeInfoByShelf(const QString shelfIP)
{
	QVector<SNodeInfo> curNode;
	SNodeInfo tmpNodeInfo;
	/* Connect to Server */
	SOCKET sockfd;
	int port = atoi(SERVER_PORT_NUM);
	struct sockaddr_in serverAddr;
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	unsigned long int socketMode = 1; //1 for non-block mode
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return curNode;
	}
	//creat socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("\ncreate socket failed");
		return curNode;
	}
	//connect
	memset(&serverAddr, 0, sizeof(struct sockaddr_in));
	serverAddr.sin_addr.S_un.S_addr = inet_addr(shelfIP.toStdString().c_str());
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	ioctlsocket(sockfd, FIONBIO, &socketMode);
	if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
		struct timeval timeoutTime;
		timeoutTime.tv_sec = 0;
		timeoutTime.tv_usec = CONNECT_TIME_OUT;
		fd_set writefds;
		FD_ZERO(&writefds);
		FD_SET(sockfd, &writefds);
		if (select(sockfd + 1, NULL, &writefds, NULL, &timeoutTime) > 0)
		{
			if (FD_ISSET(sockfd, &writefds))
			{
				socketMode = 0;
				ioctlsocket(sockfd, FIONBIO, &socketMode);
			}
		}
		else
		{
			closesocket(sockfd);
			WSACleanup();
			return curNode;
		}
	}

	/* Telnet to Server */
	int recvLen;
	char recvBuf[BUFLEN] = { '\0' };
	char waitBuf[BUFLEN] = { '\0' };
	int numberOfItems = 0;
	char *ptrStrPos;
	state = ENTER_USR_NAME;
	while (1)
	{
		//recv msg
		memset(recvBuf, '\0', BUFLEN);
		recvLen = recv(sockfd, recvBuf, BUFLEN, 0);
		if (recvLen < 0)
		{
			perror("\nrecv failed");
			return curNode;
		}
		if (recvLen == 0)
		{
			printf("server closed socket\n");
			return curNode;
		}
		if (recvLen > 0)
		{
			//resolve protocol
			if (strchr(recvBuf, CMD) != NULL)
			{
				ResponseToServer(sockfd, recvBuf, strlen(recvBuf));
			}
			//FSM
			switch (state)
			{
			case ENTER_USR_NAME:
				if (strstr(recvBuf, "Username:") != NULL)
				{
					if (send(sockfd, LOGIN_NAME_BUF, strlen(LOGIN_NAME_BUF), 0) < 0)
					{
						perror("\nsend failed");
						return curNode;
					}
					state = ENTER_USR_PWD;
				}
				break;
			case ENTER_USR_PWD:
				if (strstr(recvBuf, "Password:") != NULL)
				{
					if (send(sockfd, LOGIN_PWD_BUF, strlen(LOGIN_PWD_BUF), 0) < 0)
					{
						perror("\nsend failed");
						return curNode;
					}
					state = INPUT_INSTRUCTION_MACADD;
				}
				break;
			case INPUT_INSTRUCTION_MACADD:
				//get mac address
				if (strstr(recvBuf, "<") != NULL)
				{
					if (send(sockfd, INS_DIS_MAC_ADD, strlen(INS_DIS_MAC_ADD), 0) < 0)
					{
						perror("\nsend failed");
						return curNode;
					}
					state = PARSE_STRING;
					//Sleep(200); //need to delay 100ms for waiting all of messages
				}
				//solve error circumstance
				else if (strstr(recvBuf, "Authentication fail") != NULL)
				{
					Sleep(2 * 1000); //need to sleep 2 seconds
					if (send(sockfd, CR_LF, strlen(CR_LF), 0) < 0)
					{
						perror("\nsend failed");
						return curNode;
					}
					state = ENTER_USR_NAME;
				}
				break;
			case PARSE_STRING:
				//get mac-address and port number
				strcat(waitBuf, recvBuf);
				if ((ptrStrPos = strstr(waitBuf, "Total items displayed = ")) != NULL && strstr(waitBuf, "<") != NULL)
				{
					QTextStream dataStream(QByteArray(waitBuf), QIODevice::ReadOnly);
					int startFlag = 0, nodeID = -1;
					while (!dataStream.atEnd())
					{
						QString t_lineStr = dataStream.readLine();
						if (t_lineStr.isEmpty())
							continue;
						if (startFlag < 2 && !t_lineStr.isEmpty() && t_lineStr[0] == '-')
						{
							startFlag++;
							continue;
						}
						if (startFlag < 2)
							continue;
						if (startFlag == 2 && !t_lineStr.isEmpty() && t_lineStr[0] == '-')
							break;
						QStringList t_curStrList = t_lineStr.split(" ", QString::SkipEmptyParts);
						nodeID = t_curStrList[2].split("/", QString::SkipEmptyParts).last().toInt();
						if (nodeID <= 16)
						{
							tmpNodeInfo.macAddress = t_curStrList[0].split("-", QString::SkipEmptyParts).join("");
							tmpNodeInfo.nodeID = nodeID;
							curNode.append(tmpNodeInfo);
						}
					}
					closesocket(sockfd);
					WSACleanup();
					return curNode;
				}
				break;
			default:
				break;
			}
		}
	}
}

QVector<SNodeInfo> getNodeInfo(const QVector<ShelfInfo> &shelfs)
{
	QVector<SNodeInfo> nodes;
	for (const auto& curShelfInfo : shelfs)
	{
		QVector<SNodeInfo> curNodeInfo;
		curNodeInfo = getNodeInfoByShelf(curShelfInfo.ipAddress);
		for (auto curNode : curNodeInfo)
		{
			curNode.shelfID = curShelfInfo.shelfID;
			nodes.append(curNode);
		}
	}
	return nodes;
}
