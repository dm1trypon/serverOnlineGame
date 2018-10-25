#include "server.h"
#include "linksignal.h"

#include <QTcpServer>
#include <QDataStream>
#include <QtNetwork>

Server::Server(int nPort, QObject *parent) : QTcpServer(parent), m_nNextBlockSize(0)
{
    m_ptcpServer = new QTcpServer(this);
    qDebug() << "Server has been started!";
    LinkSignal::Instance().getStatus(RUNNING);

    if (!m_ptcpServer->listen(QHostAddress::Any, static_cast<quint16>(nPort)))
    {
        LinkSignal::Instance().getStatus(STOP);
        errorMessage();
    }

    connect(m_ptcpServer, &QTcpServer::newConnection, this, &Server::slotNewConnection);
    connect(&LinkSignal::Instance(), &LinkSignal::signalStopServer, this, &Server::slotDestroy);
    connect(&LinkSignal::Instance(), &LinkSignal::signalToClient, this, &Server::slotSendAll);

    getIp(nPort);
}

Server::~Server()
{
    m_ptcpServer->close();
    qDeleteAll(clientList.begin(), clientList.end());
    LinkSignal::Instance().getStatus(STOP);
    qDebug() << "Server has been stoped!";
}

void Server::getIp(int nPort)
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if (verificationIP(address))
        {
            QString serverInfo = "<H2>IP: " + address.toString() + " " + "PORT: " + QString::number(nPort) + "</H2>";
            LinkSignal::Instance().getServerInfo(serverInfo);
        }
    }
}

bool Server::verificationIP(const QHostAddress address)
{
    return address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost);
}

void Server::slotDestroy()
{
    delete this;
}

void Server::slotNewConnection()
{
    QTcpSocket* clientSocket = m_ptcpServer->nextPendingConnection();
    clientList << clientSocket;
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::slotReadClient);
}

void Server::slotReadClient()
{
    QByteArray block;
    QTcpSocket* pClientSocket = static_cast<QTcpSocket*>(sender());
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_8);
    if (!m_nNextBlockSize)
    {
        in >> m_nNextBlockSize;
    }
    QString strMessage;
    in >> strMessage;
    LinkSignal::Instance().toJson(strMessage);
}

void Server::slotSendAll(QString data)
{
    foreach(QTcpSocket* client, clientList)
    {
        qDebug() << client << data;
        sendToClient(client, data);
    }
}

void Server::sendToClient(QTcpSocket *pSocket, const QString &str)
{

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_8);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(static_cast<quint16>(arrBlock.size()) - sizeof(quint16));
    pSocket->write(arrBlock);
}

void Server::errorMessage()
{
    qDebug() << "Connection error!";
    m_ptcpServer->close();
    return;
}

void Server::slotDisconnected()
{
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(QObject::sender());
    int idx = clientList.indexOf(clientSocket);
    if (idx!=-1)
    {
        clientList.removeAt(idx);
    }
    qDebug() << "Client" << clientSocket << "has been disconnected!";
    clientSocket->deleteLater();
}
