#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


private slots:

    void on_actionSalir_triggered();

    void on_actionNuevo_triggered();

    void on_actionGuardar_triggered();

    void on_actionCircunferencias_triggered();

    void on_actionLineas_checkableChanged(bool checkable);

    void on_actionLibre_checkableChanged(bool checkable);

    void on_actionRect_nculos_checkableChanged(bool checkable);

private:
    Ui::Principal *ui;
    QImage *mImagen;
    QPainter *mPainter;
    QPoint mInicial;
    QPoint mFinal;
    QPoint mTempInic;
    QPoint mtempFinal;
    bool mPuedeDibujar;
    int mAncho;
    QColor mColor;
    int mNumLineas;
    bool mPuedel;
};
#endif // PRINCIPAL_H
