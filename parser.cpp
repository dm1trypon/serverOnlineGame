#include "parser.h"
#include "linksignal.h"
#include "operations.h"

#include <QJsonDocument>
#include <QJsonObject>

Parser::Parser()
{
    connect(&LinkSignal::Instance(), &LinkSignal::signalToJson, this, &Parser::slotFromDataString);
    connect(&LinkSignal::Instance(), &LinkSignal::signalMoveToJson, this, &Parser::moveJson);
}

void Parser::slotFromDataString(QString data)
{
    QJsonDocument docData = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject objData = docData.object();

    if (onMethod(objData, NEW_PLAYER))
    {
        LinkSignal::Instance().toClient(newPlayerJson(objData));
    }

    if (onMethod(objData, MOVE))
    {
        findObject(objData, MOVE);
    }

    if (onMethod(objData, DEL_PLAYER))
    {
        LinkSignal::Instance().toClient(delPlayerJson(objData));
    }
}

void Parser::poolDataPlayer(QJsonObject objFound, QString directions)
{
    DataPlayer *_dataPlayer = new DataPlayer();
    _dataPlayer->nickName = objFound.value(NICKNAME).toString();
    _dataPlayer->posX = objFound.value(POSX).toDouble();
    _dataPlayer->posY = objFound.value(POSY).toDouble();
    directionMove(_dataPlayer, directions);
}

void Parser::directionMove(DataPlayer *_dataPlayer, QString direction)
{
    if (direction == LEFT)
    {
        LinkSignal::Instance().toMove(_dataPlayer, direction);
    }

    if (direction == RIGHT)
    {
        LinkSignal::Instance().toMove(_dataPlayer, direction);
    }

    if (direction == UP)
    {
        LinkSignal::Instance().toMove(_dataPlayer, direction);
    }

    if (direction == DOWN)
    {
        LinkSignal::Instance().toMove(_dataPlayer, direction);
    }
}

bool Parser::onMethod(QJsonObject objMethod, QString type)
{
    return objMethod.value(TYPE) == type;
}

QString Parser::newPlayerJson(QJsonObject objData)
{
    QJsonObject objNewPlayer;
    objNewPlayer.insert(TYPE, NEW_PLAYER);
    objNewPlayer.insert(NICKNAME, objData.value(NICKNAME));
    objNewPlayer.insert(POSX, &Operations::setPositionX);
    objNewPlayer.insert(POSY, &Operations::setPositionY);
    QJsonDocument docNewPlayer(objNewPlayer);
    QString strJson(docNewPlayer.toJson(QJsonDocument::Compact));
    objNewPlayer.remove(TYPE);
    arrPlayers.append(objNewPlayer);
    listNickNames.append(objNewPlayer.value(NICKNAME).toString());
    LinkSignal::Instance().toListPlayers(listNickNames);
    return strJson;
}

void Parser::moveJson(DataPlayer* _dataPlayer)
{
    QJsonObject objMovePlayer;
    objMovePlayer.insert(TYPE, MOVE);
    objMovePlayer.insert(NICKNAME, _dataPlayer->nickName);
    objMovePlayer.insert(POSX, _dataPlayer->posX);
    objMovePlayer.insert(POSY, _dataPlayer->posY);
    QJsonDocument docMovePlayer(objMovePlayer);
    QString strJson(docMovePlayer.toJson(QJsonDocument::Compact));
    objMovePlayer.remove(TYPE);
    findObject(objMovePlayer, NEW_POSITION);
    LinkSignal::Instance().toClient(strJson);
}

QString Parser::delPlayerJson(QJsonObject objData)
{
    findObject(objData, DEL_PLAYER);
    QJsonObject objDelPlayer;
    objDelPlayer.insert(TYPE, DEL_PLAYER);
    objDelPlayer.insert(NICKNAME, objData.value(NICKNAME));
    QJsonDocument docDelPlayer(objDelPlayer);
    QString strJson(docDelPlayer.toJson(QJsonDocument::Compact));
    return strJson;
}

void Parser::findObject(QJsonObject objData, QString operation)
{
    int iterator = 0;
    foreach(QJsonValue valArrPlayers, arrPlayers)
    {
        if (onFindNickName(valArrPlayers, objData))
        {
            if (operation == DEL_PLAYER)
            {
                arrPlayers.removeAt(iterator);
                listNickNames.removeAt(iterator);
                LinkSignal::Instance().toListPlayers(listNickNames);
            }

            if (operation == MOVE)
            {
                poolDataPlayer(valArrPlayers.toObject(), objData.value(DIRECTION).toString());
            }

            if (operation == NEW_POSITION)
            {
                arrPlayers[iterator] = objData;
            }
        }
        iterator++;
    }
}

bool Parser::onFindNickName(QJsonValue valArrPlayers, QJsonObject objData)
{
    return valArrPlayers.toObject().value(NICKNAME) == objData.value(NICKNAME);
}
