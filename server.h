#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QNetworkSession>

class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server(int nPort, QObject *parent = nullptr);
    ~Server();
public slots:
    virtual void slotNewConnection();
private slots:
    void slotReadClient();
    void slotDisconnected();
    void slotSendAll(QString data);
    void slotDestroy();
private:
    const QString RUNNING = "Running";
    const QString STOP = "Stop";

    QString status;
    QList<QTcpSocket*> clientList;
    QTcpServer* m_ptcpServer;
    quint16 m_nNextBlockSize;
    void sendToClient(QTcpSocket* pSocket, const QString& data);
    void errorMessage();
    void senderOut(QString data);
    void changeClientsData(QList<QTcpSocket *> clientList_j, QJsonArray arrClients_j, QJsonDocument _docClients_j);
    bool verificationIP(const QHostAddress address);
    void getIp(int nPort);
};

#endif // SERVER_H
