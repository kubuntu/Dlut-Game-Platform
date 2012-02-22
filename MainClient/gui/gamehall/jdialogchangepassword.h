#ifndef JDIALOGCHANGEPASSWORD_H
#define JDIALOGCHANGEPASSWORD_H

#include <QDialog>

#include <Global/Global>

namespace Ui {
    class JDialogChangePassword;
}

class JClientChangePasswordProcessor;

class JDialogChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit JDialogChangePassword(QWidget *parent = 0);
    ~JDialogChangePassword();
	void setUserId(JID userId);
	void accept();
private:
    Ui::JDialogChangePassword *ui;
	JID m_userId ;
	JClientChangePasswordProcessor* m_processor;
private slots:
	void receiveResult(JCode code);
};

#endif // JDIALOGCHANGEPASSWORD_H
