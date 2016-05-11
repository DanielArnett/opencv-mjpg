#include "TcpServer.h"
#include <QtNetwork/QTcpSocket>
#include <QtCore/QByteArray>
#include <QtCore/QtDebug>
#include <QtCore/QString>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

TcpServer::TcpServer(QObject *parent) :
QObject(parent)
{
    server = new QTcpServer(this);
    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()),
        this, SLOT(newConnection()));
    if (!server->listen(QHostAddress::Any, 9999))
        qDebug() << "Server could not start";
    else
        qDebug() << "Server started!";
    vCapture = new VideoCapture(0);
}
void TcpServer::newConnection()
{
    QTcpSocket *socket = server->nextPendingConnection();
    QByteArray ContentType = ("HTTP/1.0 200 OK\r\n" \
        "Cache-Control: no-cache\r\n" \
        "Cache-Control: private\r\n" \
        "Content-Type: multipart/x-mixed-replace;boundary=--boundary\r\n");
    socket->write(ContentType);
    std::vector<uchar> buff;
    Mat img; //OpenCV Material
    while (1) {
        // Image to Byte Array via OPENCV Method
        buff.clear();buff.empty();
        vCapture->read(img); //Read from webcam

        //TODO set the compression parameters.
        imencode(".jpg", img, buff);
        std::string content(buff.begin(), buff.end());
        QByteArray CurrentImg(QByteArray::fromStdString(content));
        QByteArray BoundaryString = ("--boundary\r\n" \
            "Content-Type: image/jpeg\r\n" \
            "Content-Length: ");
        BoundaryString.append(QString::number(CurrentImg.length()));
        BoundaryString.append("\r\n\r\n");

        socket->write(BoundaryString);
        socket->write(CurrentImg); // Write The Encoded Image
        socket->flush();
    }
}
