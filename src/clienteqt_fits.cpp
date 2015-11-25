#include "clienteqt_fits.h"


ClienteQtFits::ClienteQtFits() {
    socket = new QTcpSocket(this);
    host = new QString("127.0.0.1");
    port = new int(7777);
    contAux = 0;
}

void ClienteQtFits::conectarse() {
  this->socket->abort();
  this->socket->connectToHost(*host, *port);
   qDebug() << socket->state();
   connect(socket, SIGNAL(connected()), this, SLOT(conectado()));
}

void ClienteQtFits::conectado() {

    qDebug() << "Conectado";
    qDebug() << socket->state();
    for (int k=0; k<4096; k++) {
        this->sendMessage(k);
        //la siguiente línea simula la frecuencia de lectura de los CCDs.
        usleep(125000);
    }
}


void ClienteQtFits::sendMessage(int cont) {
    QDataStream out(socket);



    if ((fmod(cont, 512)) == 0.0) {
        contAux = 0;
    }

    for (int l=0; l<2048; l++) {
        line[l] = matrix(contAux, l);
    }
    contAux = contAux + 1;

    if((out.writeRawData((char*)line, 4096))<=0){
        qDebug() << "Error al escribir en el socket";
    }
    socket->flush();
    qDebug() << "Mensaje enviado: " << cont;
}

void ClienteQtFits::printerror(int status)
{
    if (status)
    {
      fits_report_error(stderr, status); /* print error report */
      exit( status );    /* terminate the program, returning error status */
    }
}

void ClienteQtFits::leerFits()
{
    fitsfile *fptr;
    float nullval, pline[2048];
    int status = 0, anynull=0;
    long fpixel = 1;
    char filename[] = "/home/ievivas/Desarrollo/obs401.qnx3.ccd2.n110.fits";

    if (fits_open_file(&fptr, filename, READONLY, &status))
        printerror(status);

    for (int i=0; i<512; i++)
    {
        if ( fits_read_img(fptr, TFLOAT, fpixel, 2048, &nullval, pline, &anynull, &status) )
                   printerror( status );
        for (int j=0; j<2048; j++)
        {
            matrix(i, j) = quint16(pline[j]);
        }
        fpixel = fpixel + 2100;
        std::cout << 512 - i << std::endl;
    }
}














