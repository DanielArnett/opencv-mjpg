#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QtCore/QObject>
#include <QtNetwork/QTcpServer>
#include "opencv2/videoio.hpp"

using namespace cv;
class TcpServer : public QObject
{
    Q_OBJECT

public:
    explicit TcpServer(QObject *parent = 0);
    void newConnection();
private:
    QTcpServer* server;
    VideoCapture* vCapture;
};

#endif
