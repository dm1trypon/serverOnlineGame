#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QJsonArray>

const QString UP = "up";
const QString DOWN = "down";
const QString RIGHT = "right";
const QString LEFT = "left";

struct DataPlayer
{
    qreal posX;
    qreal posY;
    QString nickName;
};

class Parser : public QObject
{
    Q_OBJECT
public:
    Parser();
private slots:
    void slotFromDataString(QString data);
private:
    const QString NEW_PLAYER = "new_player";
    const QString MOVE = "move";
    const QString DEL_PLAYER = "del_player";
    const QString TYPE = "type";
    const QString NICKNAME = "nickname";
    const QString POSX = "posX";
    const QString POSY = "posY";
    const QString DIRECTION = "direction";
    const QString NEW_POSITION = "new_position";

    QJsonArray arrPlayers;
    QStringList listNickNames;

    bool onMethod(QJsonObject objMethod, QString type);
    bool onFindNickName(QJsonValue valArrPlayers, QJsonObject objData);
    QString newPlayerJson(QJsonObject objData);
    QString delPlayerJson(QJsonObject objData);
    void findObject(QJsonObject objData, QString operation);
    void moveJson(DataPlayer *_dataPlayer);
    void directionMove(DataPlayer* _dataPlayer,QString direction);
    void poolDataPlayer(QJsonObject objFound, QString direction);
};

#endif // PARSER_H
