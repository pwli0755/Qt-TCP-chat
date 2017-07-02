#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_Listen_clicked();

    void on_pushButton_Send_clicked();

    void server_New_Connect();
    void socket_Recv_Data();
    void socket_Disconnect();


private:
    Ui::Widget *ui;
    QTcpServer *m_server;
    QTcpSocket *m_socket;
};

#endif // WIDGET_H
