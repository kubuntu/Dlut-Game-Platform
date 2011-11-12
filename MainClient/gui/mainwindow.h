#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Global/Global>

namespace Ui {
    class MainWindow;
}

class JRequestGameInfo;
class JRequestUserInfo;
class QListWidgetItem;
class JWidgetAdmin;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void showEvent ( QShowEvent * event );

private:
    Ui::MainWindow *ui;
	JWidgetAdmin *m_widgetadmin;
private slots:
	void on_btn_refresh_myuserinfo_clicked();
	void on_actionShow_admin_window_triggered();
	void on_btn_start_game_clicked();
	void on_list_game_itemClicked(QListWidgetItem* item);
	void on_btn_refresh_list_clicked();
private:
	void updateGameList();
	void updateGameInfo(JID gameId);
private:
    JRequestGameInfo* m_gis;
	JRequestUserInfo* m_requserinfo;
	JID m_currentId;
};

#endif // MAINWINDOW_H
