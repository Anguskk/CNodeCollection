#include "BaseToolsofPlate.h"

CBaseToolofPlate::~CBaseToolofPlate()
{
	delete m_action;
}

void CBaseToolofPlate::init(QToolBar * toolbar,QMenu * menu,QIcon icon,QString text,QMainWindow *pwd,bool bActionchecked, QActionGroup *actionGroup)
{
	m_pwd = pwd;
	m_action = new QAction(icon,text,(QWidget*)m_pwd);
	if(toolbar != NULL) toolbar->addAction(m_action);
	if(menu != NULL) menu->addAction(m_action);
	m_action->setEnabled(false);
	m_action->setCheckable(bActionchecked);
	if (bActionchecked)
		m_action->setChecked(false);
	if (actionGroup != nullptr)
		actionGroup->addAction(m_action);
	connect(m_action,SIGNAL(triggered()),this,SLOT(OnInitialize()));

}

void CBaseToolofPlate::setToolsState( bool flag )
{
	if (!m_bActicon)
 	   m_action->setEnabled(flag);
}

CBaseToolofPlate::CBaseToolofPlate()
{
	m_bActicon = false;
	m_bupdateDataFlag = false;
}

void CBaseToolofPlate::setToolsActionState( bool flag )
{
	m_bActicon = flag;
	m_action->setEnabled(flag);
}

void CBaseToolofPlate::closeSubWd()
{

}