#include <iostream>

#include <QApplication>
#include <QObject>
#include "TcpServer.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString test = "Hello";
    QObject test2;
    int i = 0;
    TcpServer server;
}
