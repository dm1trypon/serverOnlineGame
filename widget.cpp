#include "widget.h"
#include "linksignal.h"
#include "ui_widget.h"
#include "server.h"

#include <QTextEdit>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    pvbxLayout = new QVBoxLayout;
    QLabel* l_description = new QLabel("<H1>Server</H1>");
    l_status = new QLabel("Stop");
    l_host = new QLabel;
    lw_players = new QListWidget;
    b_start = new QPushButton("Start");
    b_stop = new QPushButton("Stop");
    b_stop->setEnabled(false);
    pvbxLayout->addWidget(l_description);
    pvbxLayout->addWidget(l_status);
    pvbxLayout->addWidget(l_host);
    pvbxLayout->addWidget(lw_players);
    pvbxLayout->addWidget(b_start);
    pvbxLayout->addWidget(b_stop);
    setLayout(pvbxLayout);

    connect(&LinkSignal::Instance(), &LinkSignal::signalGetServerInfo, this, &Widget::slotAddServerInfo);
    connect(b_start, &QPushButton::clicked, this, &Widget::slotStartServer);
    connect(b_stop, &QPushButton::clicked, this, &Widget::slotStopServer);
    connect(&LinkSignal::Instance(), &LinkSignal::signalGetStatus, this, &Widget::slotStatusServer);
    connect(&LinkSignal::Instance(), &LinkSignal::signalToListPlayers, this, &Widget::slotShowList);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotAddServerInfo(QString serverInfo)
{
    l_host->setText(serverInfo);
}

void Widget::slotStatusServer(QString status)
{
    l_status->setText(status);
}

void Widget::slotStartServer()
{
    b_start->setEnabled(false);
    b_stop->setEnabled(true);
    new Server(8080);
}

void Widget::slotStopServer()
{
    b_stop->setEnabled(false);
    b_start->setEnabled(true);
    LinkSignal::Instance().stopServer();
}

void Widget::slotShowList(QStringList listNickNames)
{
    lw_players->clear();
    lw_players->addItems(listNickNames);
}
