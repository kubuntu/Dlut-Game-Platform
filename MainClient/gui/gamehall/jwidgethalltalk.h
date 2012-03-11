#ifndef JWIDGETHALLTALK_H
#define JWIDGETHALLTALK_H

#include <QWidget>

#include <DataStruct/JUserInfo>

namespace Ui {
    class JWidgetHallTalk;
}
class JClientHallTalkProcessor;
template <class T>
class JRequestInformation;

class JWidgetHallTalk : public QWidget
{
    Q_OBJECT

public:
    explicit JWidgetHallTalk(QWidget *parent = 0);
    ~JWidgetHallTalk();

private:
    Ui::JWidgetHallTalk *ui;
	JClientHallTalkProcessor* m_processor;
	JRequestInformation<JUserInfo>* m_requserinfo;
private slots:
	void showMessage(const QString& msg);
	void sendMessageInEdit();
};

#endif // JWIDGETHALLTALK_H
