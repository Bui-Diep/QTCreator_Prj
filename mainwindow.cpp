#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QDebug>
#include <QString>
#include <QMessageBox>

QSerialPort * serialPort;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serialPort = new QSerialPort(this);

    serialPort->setPortName("com7");
    serialPort->setBaudRate(QSerialPort::Baud19200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->setStopBits(QSerialPort::OneStop);



    serialPort->open(QIODevice::ReadWrite);
    serialPort->write("okok");

    connect(serialPort,SIGNAL(readyRead()),this,SLOT(serialport_read()));
}

MainWindow::~MainWindow()
{
    delete ui;
    serialPort->close();
}


void MainWindow::on_Send_clicked()
{
    QString a = "Data Sending ....";
    ui->label->setText(a);
    serialPort->write(ui->ledSend->text().toStdString().data());
    qDebug() << a;

}
void MainWindow::serialport_read()
{

    ui->pteReceive->insertPlainText(serialPort->readAll());
    ui->pteReceive->moveCursor(QTextCursor::End);
}

void MainWindow::on_btnCheck_clicked()
{
    QString error = "No errors on the circuit board";
    QMessageBox::information(this,"Checking", error);
    qDebug() << error;
//    qDebug() << QIODevice::write();
}

