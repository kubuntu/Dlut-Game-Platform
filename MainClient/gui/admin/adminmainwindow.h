#ifndef ADMINMAINWINDOW_H
#define ADMINMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class AdminMainWindow;
}

class JWidgetAdmin;
class JFormAddGame;
class JWidgetAddInvitationCode;

class AdminMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMainWindow(QWidget *parent = 0);
    ~AdminMainWindow();

private:
    Ui::AdminMainWindow *ui;
	JWidgetAdmin *m_widgetadmin;
	JFormAddGame *m_formAddGame;
	JWidgetAddInvitationCode* m_widgetAddInvitationCode;
private slots:
	void on_actionShow_admin_window_triggered();
	void on_actionAdd_game_triggered();
	void on_actionAdd_invitation_code_triggered();
	void On_socket_disconnected();
};

#endif // ADMINMAINWINDOW_H
