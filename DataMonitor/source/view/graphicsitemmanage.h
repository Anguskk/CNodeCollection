/**************************************************************
Copyright (C),  2016   ���ӿƼ���ѧ.
FileName :  graphicsitemmanage.h
Author :       lz
Version : V1.0
Date : 2016/8/30
Description :        ///ģ������ ͼԪ�����
Other :              ///��������
Function List :      ///��Ҫ�������书��
History :            ///��ʷ�޸ļ�¼
<Author>    <Time>    <Version>    <Desc>
**************************************************************/
#pragma once

#include <QGraphicsItem>

class CGraphicsItemManagePrivate;
class CGraphicsItemManage
{
public:
	/******
	����:  ���캯��
	����:  ��
	����ֵ: ��
	******/
	CGraphicsItemManage();
	/******
	����:  ��������
	����:  ��
	����ֵ: ��
	******/
	~CGraphicsItemManage();

	/******
	����:������ݵ�ͼ��
	����:_data ����
	����ֵ:-1ʧ�� 1 �ɹ�
	******/
	int addData(QGraphicsItem* _data);

	/******
	����:  ��ȡ��������
	����:  vindex ��������
	����ֵ: ��������
	******/
	const QGraphicsItem* getObjectByIndex(const int vindex);

	/******
	����:  ��ȡ������������
	����:  _object ��������
	����ֵ: ͼ������ -1 ʧ�� ����Ϊ��������
	******/
	const int getIndexByObject(const QGraphicsItem * _object);

	/******
	����:  ɾ������
	����:  vindex ɾ����������
	����ֵ: true �ɹ�  false ʧ��
	******/
	bool deleteObjectByIndex(const int vindex);

	/******
	����:ɾ������
	����:_data ��������
	����ֵ:-1ʧ�� 1 �ɹ�
	******/
	int  deleteData(QGraphicsItem * _data);

	/******
	����:���б����޳���ɾ������
	����:_data ��������
	����ֵ:-1ʧ�� 1 �ɹ�
	******/
	int eraseData(QGraphicsItem * _data);

	QVector<QGraphicsItem*> &getAllobjects();

private:
	Q_DECLARE_PRIVATE(CGraphicsItemManage);
	QScopedPointer<CGraphicsItemManagePrivate> d_ptr;
};
