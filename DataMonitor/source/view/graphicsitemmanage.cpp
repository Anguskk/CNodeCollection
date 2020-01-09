/**************************************************************
Copyright (C),  2016   ���ӿƼ���ѧ.
FileName :  graphicsitemmanage.cpp
Author :       lz
Version : V1.0
Date : 2016/8/30
Description :        ///ģ������ ��λ�������ά���Թ����
Other :              ///��������
Function List :      ///��Ҫ�������书��
History :            ///��ʷ�޸ļ�¼
<Author>    <Time>    <Version>    <Desc>
**************************************************************/
#include "graphicsitemmanage.h"

//���ݱ�����
class CGraphicsItemManagePrivate
{
	Q_DECLARE_PUBLIC(CGraphicsItemManage)
public:
	/************************************************************************
	Function:       CGraphicsNodeItem()
	Description:    ���캯��
	Input:          width ��ȣ�height �߶ȣ�info �ڵ���Ϣ��parent ��object
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CGraphicsItemManagePrivate(CGraphicsItemManage *parent):q_ptr(parent){}

	/************************************************************************
	Function:       ~CGraphicsNodeItemPrivate()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	virtual ~CGraphicsItemManagePrivate(){}

private:
	QVector<QGraphicsItem*>      m_allItems;                                // ͼ������ӳ��

	CGraphicsItemManage           *q_ptr;                                   //��ָ��
};

/******
����:  ���캯��
����:  ��
����ֵ: ��
******/
CGraphicsItemManage::CGraphicsItemManage()
	:d_ptr(new CGraphicsItemManagePrivate(this))
{
}

/******
����:  ��������
����:  ��
����ֵ: ��
******/
CGraphicsItemManage::~CGraphicsItemManage()
{
	Q_D(CGraphicsItemManage);
	for (int t_index = 0; t_index < d->m_allItems.size(); t_index++)
	{
		delete d->m_allItems[t_index];
		d->m_allItems[t_index] = NULL;
	}
	d->m_allItems.clear();
}
/******
����:������ݵ�ͼ��
����:_data ����
����ֵ:-1ʧ�� 1 �ɹ�
******/
int CGraphicsItemManage::addData(QGraphicsItem* _data )
{
	Q_D(CGraphicsItemManage);
	if (getIndexByObject(_data) != -1)
		return -1;
	 d->m_allItems.append(_data);
	 return d->m_allItems.size() -1;
}
/******
����:  ��ȡ��������
����:  vindex ��������
����ֵ: ��������
******/
const QGraphicsItem* CGraphicsItemManage::getObjectByIndex( const int vindex )
{
	Q_D(CGraphicsItemManage);
	if (vindex < 0 || vindex >= d->m_allItems.size()) 
		return nullptr;

    return d->m_allItems.at(vindex);
}
/******
����:  ��ȡ������������
����:  _object ��������
����ֵ: ͼ������ -1 ʧ�� ����Ϊ��������
******/
const int CGraphicsItemManage::getIndexByObject( const QGraphicsItem * _object )
{
	Q_D(CGraphicsItemManage);
	for (int t_index = 0; t_index < d->m_allItems.size(); t_index++)
	{
        if (d->m_allItems.at(t_index) == _object)
			return t_index;
	}
	return -1;
}
/******
����:  ɾ������
����:  vindex ɾ����������
����ֵ: true �ɹ�  false ʧ��
******/
bool CGraphicsItemManage::deleteObjectByIndex( const int vindex )
{
	Q_D(CGraphicsItemManage);
	if (vindex < 0 || vindex >= d->m_allItems.size()) 
		return false;
    delete d->m_allItems[vindex];
	d->m_allItems[vindex] = nullptr;
	d->m_allItems.remove(vindex);
	return true;
}
/******
����:ɾ������
����:_data ��������
����ֵ:-1ʧ�� 1 �ɹ�
******/
int CGraphicsItemManage::deleteData(QGraphicsItem * _data )
{
	Q_D(CGraphicsItemManage);
	for (int t_index = 0; t_index < d->m_allItems.size(); t_index++)
	{
		if (d->m_allItems.at(t_index) == _data){
			delete d->m_allItems[t_index];
			d->m_allItems[t_index] = nullptr;
			d->m_allItems.remove(t_index);
			return 1;
		}
	}
	return -1;
}

/******
����:���б����޳���ɾ������
����:_data ��������
����ֵ:-1ʧ�� 1 �ɹ�
******/
int CGraphicsItemManage::eraseData(QGraphicsItem * _data )
{
	Q_D(CGraphicsItemManage);
	for (int t_index = 0; t_index < d->m_allItems.size(); t_index++)
	{
		if (d->m_allItems[t_index] == _data){
			d->m_allItems.remove(t_index);
			return 1;
		}
	}
	return -1;
}

QVector<QGraphicsItem*> & CGraphicsItemManage::getAllobjects()
{
	Q_D(CGraphicsItemManage);
	return d->m_allItems;
}
