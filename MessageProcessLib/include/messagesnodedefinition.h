#pragma once

/****************************瞬时消息类型**************************************/
//服务器告诉节点任务完成可以下线
#define CompleteRequestMsg                             0x0001
#define CompleteConfirmMsg                             0x0002

//收发节点信息
#define NoteInfoRequestMsg                             0x0003
#define NoteInfoConfirmMsg                             0x0004

//年检消息
#define AnnualInspectionRequestMsg                     0x0005
#define AnnualInspectionConfirmMsg                     0x0006

//年检下载消息
#define AnnualInspectionDownloadRequestMsg             0x0007
#define AnnualInspectionDownloadConfirmMsg             0x0008

//充电消息
#define ChargingRequestMsg                             0x0009
#define ChargingConfirmMsg                             0x000a

//下载消息
#define DownloadRequestMsg                             0x000b
#define DownloadConfirmMsg                             0x000c

//固件升级消息
#define FirmwareUpgradeRequestMsg                      0x000d
#define FirmwareUpgradeConfirmMsg                      0x000e

//参数设置消息
#define SystemConfigRequestMsg                         0x000f
#define SystemConfigConfirmMsg                         0x0010

//连接状态
#define ConnectionStatusMsg                            0x00ff
/************************************************************************/

/*****************************不定时消息类型*************************/
//年检状态
#define AnnualInspectionStateInfoMsg                0x0101

//年检下载状态消息
#define AnnualInspectionDownloadStateInfoMsg        0x0102

//充电状态消息
#define ChargingStateInfoMsg                        0x0103

//下载状态消息
#define DownloadStateInfoMsg                        0x0104
/************************************************************************/

//消息开始有2个字节效验码A5A5
//消息类型2字节
//消息长度4字节
//消息内容

/*********************与节点仪消息格式*******************************/
typedef struct _tagMessageNodeHeader
{
	unsigned short      checkNum;                 //校验
	unsigned short      type;                     //消息类型
	unsigned int        length;                   //消息长度
}SMessageNodeHeader;

typedef struct _tagMessageNodeBase
{
	SMessageNodeHeader      header;                 //校验
	void*                   data;                   //消息类型
}SMessageNodeBase;
/************************************************************************/

/*****************************关闭状态***********************************/
typedef struct _tagConfirmCompleteMessage
{
	unsigned char      state[4];                   //0为正常，1为无法关闭
}SConfirmCompleteMessage;
/************************************************************************/

/*****************************节点信息***********************************/
typedef struct _tagConfirmNoteInfoMessage
{
	unsigned char        mac[8];         //mac地址（6位）8位为了对齐
}SConfirmMacMessage;
/************************************************************************/

/*****************************年检***********************************/
typedef struct _tagRequestAnnualInspectionMessage
{
	unsigned char         date[8];                     //日期--20190101
}SRequestAnnualInspectionMessage;

typedef struct _tagConfirmAnnualInspectionMessage
{
	unsigned char         type[4];                        //类型--0为正常，1为无法年检，2为已做年检
}SConfirmAnnualInspectionMessage;

typedef struct _tagInfoAnnualInspectionStateMessage
{
	unsigned char         rate[4];                      //年检--百分比（0~100）
}SInfoAnnualInspectionStateMessage;
/************************************************************************/

/*****************************年检下载*********************************/
typedef struct _tagRequestAnnualInspectionDownloadMessage
{
	unsigned char         date[8];                     //日期--20190101
}SRequestAnnualInspectionDownloadMessage;

typedef struct _tagConfirmAnnualInspectionDownloadMessage
{
	unsigned char         type[4];                      //类型--0为正常，1为无法下载, 2 ftp is running
}SConfirmAnnualInspectionDownloadMessage;

typedef struct _tagInfoAnnualInspectionDownloadStateMessage
{
	unsigned char         rate[4];                      //年检--0为完成，1为下载失败
}SInfoAnnualInspectionDownloadStateMessage;
/************************************************************************/

/*******************************充电*************************************/
typedef struct _tagRequestChargingMessage
{
	unsigned char         monitoring[4];                //开启电量监控--0为关闭，1为开启
}SRequestChargingMessage;

typedef struct _tagConfirmChargingMessage
{
	unsigned char         type[4];                      //类型--0为成功，1为失败
}SConfirmChargingMessage;

typedef struct _tagInfoChargingStateMessage
{
	unsigned char         electricity[4];               //电量--百分比（0~100）
}SInfoChargingStateMessage;
/************************************************************************/

/*****************************下载***************************************/
typedef struct _tagRequestDownloadMessage
{
	unsigned char        type[4];                     //类型，0为正常下载，1为强制
}SRequestDownloadMessage;

typedef struct _tagConfirmDownloadMessage
{
	unsigned char         type[4];                      //类型--0为正常，1为故障
}SConfirmDownloadMessage;

typedef struct _tagInfomDownloadStateMessage
{
	unsigned int         count;               //文件总数
	unsigned int         curNum;              //当前发送个数
}SInfoDownloadStateMessage;
/************************************************************************/

/*****************************固件升级消息*******************************/
typedef struct _tagRequestFirmwareUpgradeMessage
{
	unsigned int         count;               //版本号
}SRequestFirmwareUpgradeMessage;

typedef struct _tagConfirmFirmwareUpgradeMessage
{
	unsigned char         type[4];           //类型--0为相等，1为当前版本小于节点，2为当前版本大于节点, 3 ftp is running
}SConfirmFirmwareUpgradeMessage;
/*****************************固件升级消息*******************************/

/*****************************参数设置消息*******************************/
//采样率
typedef enum
{
	ADS_SPS_250 = 0,
	ADS_SPS_500 = 0x08,
	ADS_SPS_1000 = 0x10,
	ADS_SPS_2000 = 0x18,
	ADS_SPS_4000 = 0x20,
}ADS_SPSTypeDef;

//增益
typedef enum
{
	ADS_GAIN_1 = 0x00,
	ADS_GAIN_2 = 0x01,
	ADS_GAIN_4 = 0x02,
	ADS_GAIN_8 = 0x03,
	ADS_GAIN_16 = 0x04,
	ADS_GAIN_32 = 0x05,
	ADS_GAIN_64 = 0x06,
}ADS_GainTypeDef;

//滤波器类型
typedef enum
{
	ADS_FIR_LIN = 0x00,             //线性
	ADS_FIR_MIN = 0x04,             //最小相位
}ADS_FIRTypeDef;

typedef struct _tagRequestSystemConfigMessage
{
	uint8_t qcDailyTestEnable;      //日检次数--按照前2位检查日检有效

	uint8_t qcDailyTestHour;        //时
	uint8_t qcDailyTestMinute;      //分
	uint8_t qcDailyTestSecond;      //秒

	uint8_t qcDailyTestHour2;        //时
	uint8_t qcDailyTestMinute2;      //分
	uint8_t qcDailyTestSecond2;      //秒

	uint8_t qcDailySleepEnable;      //日休眠次数--按照前2位检查日检有效

	uint8_t qcDailySleepStartHour;        //时
	uint8_t qcDailySleepStartMinute;      //分
	uint8_t qcDailySleepStartSecond;      //秒

	uint8_t qcDailySleepEndHour;        //时
	uint8_t qcDailySleepEndMinute;      //分
	uint8_t qcDailySleepEndSecond;      //秒

	uint8_t qcDailyTestStartHour2;        //时
	uint8_t qcDailyTestStartMinute2;      //分
	uint8_t qcDailyTestStartSecond2;      //秒

	uint8_t qcDailyTestEndHour2;        //时
	uint8_t qcDailyTestEndMinute2;      //分
	uint8_t qcDailyTestEndSecond2;      //秒

	uint8_t adsSampleRate;          //采样率
	uint8_t adsGain;                //增益
	uint8_t adsFilterType;          //滤波器类型

	uint8_t placeholder;            //占位符
}SRequestSystemConfigMessage;

typedef struct _tagConfirmSystemConfigMessage
{
	unsigned char         type[4];           //类型--0为成功，1为失败
}SConfirmSystemConfigMessage;
/*****************************参数设置消息*******************************/
