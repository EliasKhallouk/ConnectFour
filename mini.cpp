#include <QApplication>
#include <QPushButton> 


int main(int argc , char *argv[])
{
    QApplication app(argc, argv);
    QPushButton button("Hello zefoieznfo");
    button.show();
    return app.exec();
}


//commande pour compiler le fichier mini.cpp avec qmake
//qmake
//make
//./main