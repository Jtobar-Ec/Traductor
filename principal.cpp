#include "principal.h"
#include "ui_principal.h"

#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QInputDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

#define DEFAULT_ANCHO 3

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{

    // Creacion de pantalla de creacion y relleno de la misma
    ui->setupUi(this);
    mImagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);
    mImagen->fill(Qt::white);
    mPainter = new QPainter(mImagen);
    mPainter->setRenderHint(QPainter::Antialiasing);
    mPuedeDibujar = false;
    mColor = Qt::black;
    mAncho = 5;
    mNumLineas = 0;
}

Principal::~Principal()
{
    delete ui;
    delete mPainter;
    delete mImagen;
}

void Principal::paintEvent(QPaintEvent *event)
{
   //El dibujo de la figura

    QPainter painter(this);
    painter.drawImage(0, 0, *mImagen);
    event->accept();
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    mPuedeDibujar = true;
    mInicial = event->pos();
    event->accept();
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{

    if ( !mPuedeDibujar ) {
        event->accept();
        return;
    }
    mFinal = event->pos();
    if(ui->InLibre->isChecked()==true){
        on_actionLibre_checkableChanged(true);
    }

}

void Principal::mouseReleaseEvent(QMouseEvent *event)
{
    mPuedeDibujar = false;
    event->accept();
    if(ui->InLineas->isChecked()==true){
        on_actionLineas_checkableChanged(true);
    }
    if(ui->InRectang->isChecked()==true){
        on_actionRect_nculos_checkableChanged(true);
    }
    if(ui->InCircuferencia->isChecked()==true){
        on_actionCircunferencias_triggered();
    }
}




void Principal::on_actionSalir_triggered()
{
    this->close();
}



void Principal::on_actionNuevo_triggered()
{
    mImagen->fill(Qt::black);
    mNumLineas = 0;
    update();
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar imagen",
                                                         QString(),
                                                         "Imágenes (*.png)");
    if ( !nombreArchivo.isEmpty() ){
        if (mImagen->save(nombreArchivo))
            QMessageBox::information(this,
                                     "Guardar imagen",
                                     "Archivo almacenado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,
                                 "Guardar imagen",
                                 "No se pudo almacenar la imagen.");
    }
}






void Principal::on_actionCircunferencias_triggered()
{

    // DIBUJO DEL CIRCULO

    QPen pincel;
    pincel.setColor(mColor);
    pincel.setWidth(mAncho);

    mPainter->setPen(pincel);
    mPainter->drawEllipse(mInicial.x(),mInicial.y(),mFinal.x()-mInicial.x(),mFinal.y()-mInicial.y());
    update();
}


void Principal::on_actionLineas_checkableChanged(bool checkable)
{

    // DIBUJO DE LA LINEA

    if(checkable==true){
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);

        mPainter->setPen(pincel);
        QLine line(mInicial.x(),mInicial.y(),mFinal.x(),mFinal.y());
        mPainter->drawLine(line);
        update();
    }
}


void Principal::on_actionLibre_checkableChanged(bool checkable)
{

    // MANIPULACION DEL DIBUJO

    if(checkable==true){
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        mPainter->setPen(pincel);
        mPainter->drawEllipse(QRect(QPoint(mInicial.x(),mFinal.y()),QSize(5,5)));
       ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas));
       update();
       mInicial = mFinal;
    }
}


void Principal::on_actionRect_nculos_checkableChanged(bool checkable)
{
    // DIBUJO DEL RECTANGULO

    if(checkable==true){
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        mPainter->setPen(pincel);
        if(mInicial != mFinal)
        {
            mAncho = 10;
            mPainter->drawRect(mInicial.x(),mInicial.y(),mFinal.x()-mInicial.x(),mFinal.y()-mInicial.y());
            update();
        }
    }
}

