#ifndef JWIDGETADMIN_H
#define JWIDGETADMIN_H

#include <Global/Global>

#include <QFrame>

namespace Ui {
    class JWidgetAdmin;
}
class JSendCommand;

class JWidgetAdmin : public QFrame
{
    Q_OBJECT

public:
    explicit JWidgetAdmin(QWidget *parent = 0);
    ~JWidgetAdmin();

private:
    Ui::JWidgetAdmin *ui;
	JSendCommand* m_send;
private slots:
	void on_btn_reset_clicked();
	void on_btn_add_clicked();
	void on_btn_restart_mainserver_clicked();
	void on_btn_shutdown_mainserver_clicked();
	void on_send_receiveCommandResult(JID type,JCode result);
};

#endif // JWIDGETADMIN_H
