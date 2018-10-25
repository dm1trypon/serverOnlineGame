#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "parser.h"

#include <QObject>

const int SCENE_WIDTH = 1820;
const int SCENE_HEIGHT = 980;

class Operations : public QObject
{
    Q_OBJECT
public:
    Operations();
    qreal setPositionX();
    qreal setPositionY();
private:
    const qreal SPEED = 5;

     void move(DataPlayer *_dataPlayer, QString direction);
};

#endif // OPERATIONS_H
