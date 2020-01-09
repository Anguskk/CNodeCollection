#pragma once

/****************************˲ʱ��Ϣ����**************************************/
//���������߽ڵ�������ɿ�������
#define CompleteRequestMsg                             0x0001
#define CompleteConfirmMsg                             0x0002

//�շ��ڵ���Ϣ
#define NoteInfoRequestMsg                             0x0003
#define NoteInfoConfirmMsg                             0x0004

//�����Ϣ
#define AnnualInspectionRequestMsg                     0x0005
#define AnnualInspectionConfirmMsg                     0x0006

//���������Ϣ
#define AnnualInspectionDownloadRequestMsg             0x0007
#define AnnualInspectionDownloadConfirmMsg             0x0008

//�����Ϣ
#define ChargingRequestMsg                             0x0009
#define ChargingConfirmMsg                             0x000a

//������Ϣ
#define DownloadRequestMsg                             0x000b
#define DownloadConfirmMsg                             0x000c

//�̼�������Ϣ
#define FirmwareUpgradeRequestMsg                      0x000d
#define FirmwareUpgradeConfirmMsg                      0x000e

//����������Ϣ
#define SystemConfigRequestMsg                         0x000f
#define SystemConfigConfirmMsg                         0x0010

//����״̬
#define ConnectionStatusMsg                            0x00ff
/************************************************************************/

/*****************************����ʱ��Ϣ����*************************/
//���״̬
#define AnnualInspectionStateInfoMsg                0x0101

//�������״̬��Ϣ
#define AnnualInspectionDownloadStateInfoMsg        0x0102

//���״̬��Ϣ
#define ChargingStateInfoMsg                        0x0103

//����״̬��Ϣ
#define DownloadStateInfoMsg                        0x0104
/************************************************************************/

//��Ϣ��ʼ��2���ֽ�Ч����A5A5
//��Ϣ����2�ֽ�
//��Ϣ����4�ֽ�
//��Ϣ����

/*********************��ڵ�����Ϣ��ʽ*******************************/
typedef struct _tagMessageNodeHeader
{
	unsigned short      checkNum;                 //У��
	unsigned short      type;                     //��Ϣ����
	unsigned int        length;                   //��Ϣ����
}SMessageNodeHeader;

typedef struct _tagMessageNodeBase
{
	SMessageNodeHeader      header;                 //У��
	void*                   data;                   //��Ϣ����
}SMessageNodeBase;
/************************************************************************/

/*****************************�ر�״̬***********************************/
typedef struct _tagConfirmCompleteMessage
{
	unsigned char      state[4];                   //0Ϊ������1Ϊ�޷��ر�
}SConfirmCompleteMessage;
/************************************************************************/

/*****************************�ڵ���Ϣ***********************************/
typedef struct _tagConfirmNoteInfoMessage
{
	unsigned char        mac[8];         //mac��ַ��6λ��8λΪ�˶���
}SConfirmMacMessage;
/************************************************************************/

/*****************************���***********************************/
typedef struct _tagRequestAnnualInspectionMessage
{
	unsigned char         date[8];                     //����--20190101
}SRequestAnnualInspectionMessage;

typedef struct _tagConfirmAnnualInspectionMessage
{
	unsigned char         type[4];                        //����--0Ϊ������1Ϊ�޷���죬2Ϊ�������
}SConfirmAnnualInspectionMessage;

typedef struct _tagInfoAnnualInspectionStateMessage
{
	unsigned char         rate[4];                      //���--�ٷֱȣ�0~100��
}SInfoAnnualInspectionStateMessage;
/************************************************************************/

/*****************************�������*********************************/
typedef struct _tagRequestAnnualInspectionDownloadMessage
{
	unsigned char         date[8];                     //����--20190101
}SRequestAnnualInspectionDownloadMessage;

typedef struct _tagConfirmAnnualInspectionDownloadMessage
{
	unsigned char         type[4];                      //����--0Ϊ������1Ϊ�޷�����, 2 ftp is running
}SConfirmAnnualInspectionDownloadMessage;

typedef struct _tagInfoAnnualInspectionDownloadStateMessage
{
	unsigned char         rate[4];                      //���--0Ϊ��ɣ�1Ϊ����ʧ��
}SInfoAnnualInspectionDownloadStateMessage;
/************************************************************************/

/*******************************���*************************************/
typedef struct _tagRequestChargingMessage
{
	unsigned char         monitoring[4];                //�����������--0Ϊ�رգ�1Ϊ����
}SRequestChargingMessage;

typedef struct _tagConfirmChargingMessage
{
	unsigned char         type[4];                      //����--0Ϊ�ɹ���1Ϊʧ��
}SConfirmChargingMessage;

typedef struct _tagInfoChargingStateMessage
{
	unsigned char         electricity[4];               //����--�ٷֱȣ�0~100��
}SInfoChargingStateMessage;
/************************************************************************/

/*****************************����***************************************/
typedef struct _tagRequestDownloadMessage
{
	unsigned char        type[4];                     //���ͣ�0Ϊ�������أ�1Ϊǿ��
}SRequestDownloadMessage;

typedef struct _tagConfirmDownloadMessage
{
	unsigned char         type[4];                      //����--0Ϊ������1Ϊ����
}SConfirmDownloadMessage;

typedef struct _tagInfomDownloadStateMessage
{
	unsigned int         count;               //�ļ�����
	unsigned int         curNum;              //��ǰ���͸���
}SInfoDownloadStateMessage;
/************************************************************************/

/*****************************�̼�������Ϣ*******************************/
typedef struct _tagRequestFirmwareUpgradeMessage
{
	unsigned int         count;               //�汾��
}SRequestFirmwareUpgradeMessage;

typedef struct _tagConfirmFirmwareUpgradeMessage
{
	unsigned char         type[4];           //����--0Ϊ��ȣ�1Ϊ��ǰ�汾С�ڽڵ㣬2Ϊ��ǰ�汾���ڽڵ�, 3 ftp is running
}SConfirmFirmwareUpgradeMessage;
/*****************************�̼�������Ϣ*******************************/

/*****************************����������Ϣ*******************************/
//������
typedef enum
{
	ADS_SPS_250 = 0,
	ADS_SPS_500 = 0x08,
	ADS_SPS_1000 = 0x10,
	ADS_SPS_2000 = 0x18,
	ADS_SPS_4000 = 0x20,
}ADS_SPSTypeDef;

//����
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

//�˲�������
typedef enum
{
	ADS_FIR_LIN = 0x00,             //����
	ADS_FIR_MIN = 0x04,             //��С��λ
}ADS_FIRTypeDef;

typedef struct _tagRequestSystemConfigMessage
{
	uint8_t qcDailyTestEnable;      //�ռ����--����ǰ2λ����ռ���Ч

	uint8_t qcDailyTestHour;        //ʱ
	uint8_t qcDailyTestMinute;      //��
	uint8_t qcDailyTestSecond;      //��

	uint8_t qcDailyTestHour2;        //ʱ
	uint8_t qcDailyTestMinute2;      //��
	uint8_t qcDailyTestSecond2;      //��

	uint8_t qcDailySleepEnable;      //�����ߴ���--����ǰ2λ����ռ���Ч

	uint8_t qcDailySleepStartHour;        //ʱ
	uint8_t qcDailySleepStartMinute;      //��
	uint8_t qcDailySleepStartSecond;      //��

	uint8_t qcDailySleepEndHour;        //ʱ
	uint8_t qcDailySleepEndMinute;      //��
	uint8_t qcDailySleepEndSecond;      //��

	uint8_t qcDailyTestStartHour2;        //ʱ
	uint8_t qcDailyTestStartMinute2;      //��
	uint8_t qcDailyTestStartSecond2;      //��

	uint8_t qcDailyTestEndHour2;        //ʱ
	uint8_t qcDailyTestEndMinute2;      //��
	uint8_t qcDailyTestEndSecond2;      //��

	uint8_t adsSampleRate;          //������
	uint8_t adsGain;                //����
	uint8_t adsFilterType;          //�˲�������

	uint8_t placeholder;            //ռλ��
}SRequestSystemConfigMessage;

typedef struct _tagConfirmSystemConfigMessage
{
	unsigned char         type[4];           //����--0Ϊ�ɹ���1Ϊʧ��
}SConfirmSystemConfigMessage;
/*****************************����������Ϣ*******************************/
