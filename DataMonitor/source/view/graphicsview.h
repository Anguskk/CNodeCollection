/********************************************************************
Copyright (C), 2016, ���ӿƼ���ѧ.
FileName:    graphicsview.h
Author:      LYH
Version:     V1.0
Date:        2019/05/24
Description:             ///ģ������
���ļ���Ҫ�����Ա�����ϵ����������.
Other:                   ///����������
Function List:           ///��Ҫ�������书��
History:                 ///��ʷ�޸ļ�¼
<author>    <time>    <version>     <desc>
********************************************************************/
#pragma once

#include <QGraphicsView>

#include "messagesdefinition.h"

class CGraphicsViewPrivate;
class CGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	/************************************************************************
	Function:       CGraphicsView()
	Description:    ���캯��
	Input:          parent ������
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	CGraphicsView(QWidget *parent);

	/************************************************************************
	Function:       ~CGraphicsView()
	Description:    ��������
	Input:          ��
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	~CGraphicsView();

	/************************************************************************
	Function:       getMarginAndSpacing()
	Description:    ��ȡ�߽�ͼ��
	Input:          ��
	Output:         margin �߽�,spacing ���
	Return:         ��
	Others:         ��
	************************************************************************/
	void getMarginAndSpacing(int &margin,int &spacing);

	/************************************************************************
	Function:       calculateSize()
	Description:    �������м���
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void calculateSize();

protected:
	/************************************************************************
	Function:       onViewEvent()
	Description:    ִ�и����¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void onViewEvent(QEvent *event);

	/************************************************************************
	Function:       mousePressEvent()
	Description:    ������¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void mousePressEvent(QMouseEvent *event);

	/************************************************************************
	Function:       mouseReleaseEvent()
	Description:    ����ͷ��¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void mouseReleaseEvent(QMouseEvent *event);

	/************************************************************************
	Function:       mouseDoubleClickEvent()
	Description:    ���˫���¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void mouseDoubleClickEvent(QMouseEvent *event);

	/************************************************************************
	Function:       mouseMoveEvent()
	Description:    ����ƶ��¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void mouseMoveEvent(QMouseEvent *event);

#ifndef QT_NO_WHEELEVENT
	/************************************************************************
	Function:       wheelEvent()
	Description:    �������¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void wheelEvent(QWheelEvent *event);
#endif

	/************************************************************************
	Function:       keyPressEvent()
	Description:    ���̰����¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void keyPressEvent(QKeyEvent *event);

	/************************************************************************
	Function:       keyReleaseEvent()
	Description:    �����ͷ��¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void keyReleaseEvent(QKeyEvent *event);

	/************************************************************************
	Function:       focusInEvent()
	Description:    ����focus�¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void focusInEvent(QFocusEvent *event);

	/************************************************************************
	Function:       focusOutEvent()
	Description:    �˳�focus�¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void focusOutEvent(QFocusEvent *event);

	/************************************************************************
	Function:       enterEvent()
	Description:    �������¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void enterEvent(QEvent *event);

	/************************************************************************
	Function:       leaveEvent()
	Description:    ����뿪�¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void leaveEvent(QEvent *event);

	/************************************************************************
	Function:       contextMenuEvent()
	Description:    �Ҽ��˵��¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void contextMenuEvent(QContextMenuEvent *event);

	/************************************************************************
	Function:       resizeEvent()
	Description:    ��С�仯�¼�
	Input:          event �¼�
	Output:         ��
	Return:         ��
	Others:         ��
	************************************************************************/
	void resizeEvent(QResizeEvent *event) override;

private:
	Q_DECLARE_PRIVATE(CGraphicsView);
	QScopedPointer<CGraphicsViewPrivate> d_ptr;
};
