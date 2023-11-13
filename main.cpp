#include <QCoreApplication>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpServer* server{
        new QTcpServer(&a)
    };

    std::cout << "filled ports on localhost in your device are (wait for the done message) :\n";

    for (int i{0} , j{0};i<20000;++i){
        if (server->listen(QHostAddress::Any , i)){
            server->close();
        }else{
            std::cout << ':' << i << ' ';
            ++j;
            if (j%10 == 0){
                std::cout << '\n';
            }
        }


    }

    std::cout << "\ndone";

    QObject::connect(server , &QTcpServer::newConnection , [=](){
        std::cout << "\n\nNew Tester Connected !";
        QTcpSocket* socket = server->nextPendingConnection();
        QObject::connect(socket , &QTcpSocket::readyRead , [=](){
            std::cout << "\n\nNew Data Recived:\n";
            std::cout << QString(socket->readAll()).toStdString();
            socket->close();
        });
    });

    int port;
    std::cout << "\nInsert the port for your test server : ";
    std::cin >> port;
    server->listen(QHostAddress::Any , port);
    std::cout << "\nTest Tcp Sockets are ready :";


    return a.exec();
}
