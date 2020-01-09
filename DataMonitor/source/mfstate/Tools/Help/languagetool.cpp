#include "languagetool.h"

#include <QMessageBox>
#include <QMainWindow>
#include <QCoreApplication>

#include "platform.h"
#include "datamonitor.h"

#include "selectlanguagedialog.h"

CLanguageTool::CLanguageTool()
{

}

CLanguageTool::~CLanguageTool()
{

}

void CLanguageTool::OnInitialize()
{
	CSelectLanguageDialog dlg(m_pwd);
	if (dlg.exec() != QDialog::Accepted) return;

	QString language = dlg.GetLanguage();
	if (language != PlatForm::getPlatformLanguage())
	{
		PlatForm::setPlatformLanguage(language);
		if(QMessageBox::information(m_pwd,tr("Language Settings"),tr("The language is changed,do you restart the application?"),
			QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
		{
			dynamic_cast<CDataMonitor*>(m_pwd)->setIsCloseStartNewProgress(true);
			qApp->quit();
		}
	}
}
