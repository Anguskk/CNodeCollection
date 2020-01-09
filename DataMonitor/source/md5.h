/*****************************************************************
**
**                       ���ӿƼ���ѧʵ����
**
** ���ļ���������ΪMD5���������ڶԵ���������ʷ�Ž���md5����
**
** Provider��������չ����
** Author����֣
** Date��2008-08-19
******************************************************************/
#ifndef MD5_H
#define MD5_H
#include <QString>
#include <QByteArray>

class MD5 
{
public:
	MD5();
	~MD5();
	/**
	** ���ܣ�������Ҫ���б�����ַ���
	** ����������
	** ���أ���
	**/
	void setOriginalStr(QString str);

	/**
	** ���ܣ�������Ҫ���б���Ķ�����
	** ����������������
	** ���أ���
	**/
	void setOriginalStr(QByteArray & byteArray);

	/***
	** ���ܣ���ȡ�������������
	** ��������
	** ���أ�����
	***/
	QString getEncodeStr();

private:
	unsigned long int state[4];     /* state (ABCD) */
	unsigned long int count[2];     /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];       /* input buffer */
	unsigned char PADDING[64];  /* What? */

private:
	void MD5Update ( unsigned char *input, unsigned int inputLen);
	void MD5Final (unsigned char digest[16]);
	void MD5Init ();
	void MD5Transform (unsigned long int state[4], unsigned char block[64]);
	void MD5_memcpy (unsigned char* output, unsigned char* input,unsigned int len);
	void Encode (unsigned char *output, unsigned long int *input,unsigned int len);
	void Decode (unsigned long int *output, unsigned char *input, unsigned int len);
	void MD5_memset (unsigned char* output,int value,unsigned int len);
};

#endif

