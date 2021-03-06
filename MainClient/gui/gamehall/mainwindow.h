#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <Global/Global>
#include <DataStruct/JUserInfo>
#include <DataStruct/JGameInfo>
#include <DataStruct/JGameList>

namespace Ui {
    class MainWindow;
}

template <class T>
class JRequestInformation;
class QListWidgetItem;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
private slots:
	void on_btn_update_myuserinfo_clicked();
	void on_btn_refresh_myuserinfo_clicked();
	void on_btn_start_game_clicked();
	void on_list_game_itemClicked(QListWidgetItem* item);
	void on_btn_refresh_list_clicked();
	void On_socket_disconnected();
	void on_btn_changepswd_clicked();

private:
	void updateGameList();
	void updateGameInfo(JID gameId);
private:
	JRequestInformation<JUserInfo>* m_requestUserInfo;
	JRequestInformation<JGameInfo>* m_requestGameInfo;
	JRequestInformation<JGameList>* m_requestGameList ;
	JID m_currentId;
	JUserInfo m_myUserInfo;
};

#endif // MAINWINDOW_H
