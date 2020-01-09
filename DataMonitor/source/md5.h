/*****************************************************************
**
**                       电子科技大学实验室
**
** 该文件包含的类为MD5，该类用于对地震数据历史信进行md5加密
**
** Provider：技术发展中心
** Author：刘郑
** Date：2008-08-19
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
	** 功能：设置需要进行编码的字符串
	** 参数：明文
	** 返回：无
	**/
	void setOriginalStr(QString str);

	/**
	** 功能：设置需要进行编码的二进制
	** 参数：二进制明文
	** 返回：无
	**/
	void setOriginalStr(QByteArray & byteArray);

	/***
	** 功能：获取经过编码的密文
	** 参数：无
	** 返回：密文
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

