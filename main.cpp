#include <QCoreApplication>
#include <QtNetwork/QTcpServer>
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

    return a.exec();
}
