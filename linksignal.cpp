#include "linksignal.h"

LinkSignal &LinkSignal::Instance()
{
    static LinkSignal theSingleInstance;
    return theSingleInstance;
}

void LinkSignal::toJson(QString data)
{
    emit signalToJson(data);
}

void LinkSignal::toClient(QString data)
{
    emit signalToClient(data);
}

void LinkSignal::toMove(DataPlayer *_dataPlayer, QString direction)
{
    emit signalToMove(_dataPlayer, direction);
}

void LinkSignal::moveToJson(DataPlayer *_dataPlayer)
{
    emit signalMoveToJson(_dataPlayer);
}

void LinkSignal::getServerInfo(QString serverInfo)
{
    emit signalGetServerInfo(serverInfo);
}

void LinkSignal::stopServer()
{
    emit signalStopServer();
}

void LinkSignal::getStatus(QString status)
{
    emit signalGetStatus(status);
}

void LinkSignal::toListPlayers(QStringList listNickNames)
{
    emit signalToListPlayers(listNickNames);
}
