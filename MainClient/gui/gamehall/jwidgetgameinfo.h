#ifndef JWIDGETGAMEINFO_H
#define JWIDGETGAMEINFO_H

#include <QWidget>

class JGameInfo;
class JUserInfo;

namespace Ui {
	class JWidgetGameInfo;
}

class JWidgetGameInfo : public QWidget
{
	Q_OBJECT

public:
	explicit JWidgetGameInfo(QWidget *parent = 0);
	~JWidgetGameInfo();
	void clear();
	void setGameInfo(const JGameInfo& gameinfo);
	void setUserInfo(const JUserInfo& userinfo);

private:
	Ui::JWidgetGameInfo *ui;

private slots:
	void on_btn_expand_clicked();
};

#endif // JWIDGETGAMEINFO_H
