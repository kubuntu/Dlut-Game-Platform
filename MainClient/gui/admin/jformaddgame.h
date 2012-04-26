#ifndef JFORMADDGAME_H
#define JFORMADDGAME_H

#include <QFrame>

namespace Ui {
    class JFormAddGame;
}

class JFormAddGame : public QFrame
{
    Q_OBJECT
public:
    explicit JFormAddGame(QWidget *parent = 0);
    ~JFormAddGame();
public slots:
	void reset();
private:
    Ui::JFormAddGame *ui;

private slots:
	void on_btn_game_add_clicked();
};

#endif // JFORMADDGAME_H
