#ifndef JWIDGETADDINVITATIONCODE_H
#define JWIDGETADDINVITATIONCODE_H

#include <QFrame>

namespace Ui {
    class JWidgetAddInvitationCode;
}

class JWidgetAddInvitationCode : public QFrame
{
    Q_OBJECT

public:
    explicit JWidgetAddInvitationCode(QWidget *parent = 0);
    ~JWidgetAddInvitationCode();
	void reset() ;
private slots:
	void on_btn_rand_create_clicked();
	void on_btn_send_clicked();
private:
    Ui::JWidgetAddInvitationCode *ui;
};

#endif // JWIDGETADDINVITATIONCODE_H
