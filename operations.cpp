#include "operations.h"
#include "linksignal.h"

Operations::Operations()
{
    connect(&LinkSignal::Instance(), &LinkSignal::signalToMove, this, &Operations::move);
}

qreal Operations::setPositionX()
{
    srand(static_cast<uint>(time(nullptr)));
    qreal setX = rand() % (SCENE_WIDTH);
    return setX;
}

qreal Operations::setPositionY()
{
    srand(static_cast<uint>(time(nullptr)));
    qreal setY = rand() % (SCENE_HEIGHT);
    return setY;
}

void Operations::move(DataPlayer* _dataPlayer, QString direction)
{
    if (direction == LEFT)
    {
        _dataPlayer->posX -= SPEED;
        LinkSignal::Instance().moveToJson(_dataPlayer);
    }
    if (direction == RIGHT)
    {
        _dataPlayer->posX += SPEED;
        LinkSignal::Instance().moveToJson(_dataPlayer);
    }
    if (direction == UP)
    {
        _dataPlayer->posY -= SPEED;
        LinkSignal::Instance().moveToJson(_dataPlayer);
    }
    if (direction == DOWN)
    {
        _dataPlayer->posY += SPEED;
        LinkSignal::Instance().moveToJson(_dataPlayer);
    }
}
