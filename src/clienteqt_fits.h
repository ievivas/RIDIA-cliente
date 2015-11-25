#ifndef CLIENTEQT_H
#define CLIENTEQT_H

#include <QtGui>
#include <QWidget>
#include <QObject>
#include <QTcpSocket>
#include <QtNetwork>
#include <QGenericMatrix>
#include <QFile>
#include <QString>
#include <iostream>
#include <unistd.h>

#include <cfitsio/fitsio.h>
#include <cfitsio/fitsio2.h>
#include <CCfits/CCfits.h>
#include <cfitsio/longnam.h>


class ClienteQtFits : public QObject {
    Q_OBJECT

private:
    QTcpSocket *socket;
    QString *host;
    int *port;
    QGenericMatrix<2048, 512, quint16> matrix; //<columnas, filas, tipo>
    ushort line[2048];
    QFile file;
    QString fileLine, value;
    bool ok;
    int contAux;

public:
    ClienteQtFits();
    void sendMessage(int);
    void conectarse();
    void printerror(int);
    void leerFits();


private slots:
    void conectado();

};

#endif

