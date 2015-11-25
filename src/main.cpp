#include <QtCore/QCoreApplication>
#include <clienteqt_fits.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ClienteQtFits c;
    c.leerFits();
    //c.llenarMatriz();
    c.conectarse();
    
    return a.exec();
}
