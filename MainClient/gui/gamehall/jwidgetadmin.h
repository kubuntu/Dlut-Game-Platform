#ifndef JWIDGETADMIN_H
#define JWIDGETADMIN_H

#include <Global/Global>

#include <QWidget>

namespace Ui {
    class JWidgetAdmin;
}
class JCommandSendBase;

class JWidgetAdmin : public QWidget
{
    Q_OBJECT

public:
    explicit JWidgetAdmin(QWidget *parent = 0);
    ~JWidgetAdmin();

private:
    Ui::JWidgetAdmin *ui;
	JCommandSendBase* m_send;
private slots:
	void on_btn_reset_clicked();
	void on_btn_add_clicked();
	void on_btn_restart_mainserver_clicked();
	void on_btn_shutdown_mainserver_clicked();
	void on_send_receiveCommandResult(JID type,JCode result);
};

#endif // JWIDGETADMIN_H
