#ifndef LINKSIGNAL_H
#define LINKSIGNAL_H

#include "parser.h"

#include <QObject>
#include <QTcpSocket>
#include <QList>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTcpSocket>

class LinkSignal : public QObject {
    Q_OBJECT
private:
    LinkSignal(){}
    LinkSignal(const LinkSignal& root) = delete;
    LinkSignal& operator=(const LinkSignal&) = delete;
public:
    static LinkSignal& Instance();

    void toJson(QString data);
    void toClient(QString data);
    void toMove(DataPlayer *_dataPlayer, QString direction);
    void moveToJson(DataPlayer *_dataPlayer);
    void getServerInfo(QString serverInfo);
    void stopServer();
    void getStatus(QString status);
    void toListPlayers(QStringList listNickNames);
signals:
    void signalToJson(QString);
    void signalToClient(QString);
    void signalToMove(DataPlayer*, QString);
    void signalMoveToJson(DataPlayer*);
    void signalGetServerInfo(QString);
    void signalStopServer();
    void signalGetStatus(QString);
    void signalToListPlayers(QStringList);
};
#endif // LINKSIGNAL_H
