#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets/QMessageBox>
#include <QTime>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_socket=new QTcpSocket();

    QObject::connect(m_socket,&QTcpSocket::readyRead,this,&Widget::sockt_recv_data);
    QObject::connect(m_socket,&QTcpSocket::disconnected,this,&Widget::socket_disconnect);

    ui->pushButton_Send->setShortcut(QKeySequence(tr("ctrl+return")));

    ui->lineEdit_IP->setText("127.0.0.1");
    ui->lineEdit_Port->setText("1234");
    ui->pushButton_Send->setEnabled(false);
}

Widget::~Widget()
{
    delete m_socket;
    delete ui;
}

void Widget::on_pushButton_Connect_clicked()    //连接按钮
{
    QString IP;
    qint16 port;

    if (ui->pushButton_Connect->text() == QString("连接"))
    {
        IP=ui->lineEdit_IP->text();
        port=ui->lineEdit_Port->text().toInt();

        m_socket->abort();
        m_socket->connectToHost(IP,port);

            if (!m_socket->waitForConnected())
                {

                    QMessageBox msgBox;
                     msgBox.setText("连接超时！");
                     msgBox.resize(40,30);
                     msgBox.exec();
                    return;
                }

         QMessageBox msgBox;
          msgBox.setText("连接成功！");
          msgBox.resize(40,30);
          msgBox.exec();

        ui->pushButton_Send->setEnabled(true);
        ui->pushButton_Connect->setText("断开连接");
       }
    else
    {
        m_socket->disconnectFromHost();
        ui->pushButton_Connect->setText("连接");
        ui->pushButton_Send->setEnabled(false);
    }
}

void Widget::on_pushButton_Send_clicked()  //发送按钮
{
    if (ui->textEdit->toPlainText()== QString()) //空消息检测
    {
        QMessageBox msgb;
        msgb.setText("不能发送空消息！");
        msgb.resize(60,40);
        msgb.exec();
        return;
    }
    ui->textBrowser->setTextColor(Qt::gray);
    ui->textBrowser->setCurrentFont(QFont("Times New Roman",10));
    ui->textBrowser->append("From Client:  "+QTime::currentTime().toString());

     ui->textBrowser->setTextColor(Qt::black);
     ui->textBrowser->setCurrentFont(QFont("Times New Roman",16));
    ui->textBrowser->append(ui->textEdit->toPlainText().toUtf8());

    m_socket->write(ui->textEdit->toPlainText().toUtf8());
    m_socket->flush();
    ui->textEdit->clear();
}

void Widget:: sockt_recv_data()
{
    QByteArray data_tmp;
    data_tmp = m_socket->readAll();
    if (!data_tmp.isEmpty())
    {
        //QString str = ui->textBrowser->toPlainText();

        QString str=QString(data_tmp);

        ui->textBrowser->setTextColor(Qt::gray);
        ui->textBrowser->setCurrentFont(QFont("Times New Roman",10));
        ui->textBrowser->append("From Server:  "+QTime::currentTime().toString());

         ui->textBrowser->setTextColor(Qt::black);
         ui->textBrowser->setCurrentFont(QFont("Times New Roman",16));
        ui->textBrowser->append(str);



    }
}

void Widget:: socket_disconnect()
{
    ui->pushButton_Send->setEnabled(false);
    ui->pushButton_Connect->setText("连接");
    QMessageBox msgBox;
     msgBox.setText("连接断开！");
     msgBox.resize(40,30);
     msgBox.exec();
}

