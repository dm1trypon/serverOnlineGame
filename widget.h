#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void slotAddServerInfo(QString serverInfo);
    void slotStartServer();
    void slotStopServer();
    void slotStatusServer(QString status);
    void slotShowList(QStringList listNickNames);
private:
    QVBoxLayout* pvbxLayout;
    QPushButton* b_start;
    QPushButton* b_stop;
    QListWidget* lw_players;
    QLabel* l_status;
    QLabel* l_host;
    Ui::Widget *ui;
};

#endif // WIDGET_H
