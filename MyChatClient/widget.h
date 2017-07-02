#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
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
    void on_pushButton_Connect_clicked() ;   //连接按钮
    void on_pushButton_Send_clicked() ; //发送按钮

    void sockt_recv_data();
    void socket_disconnect();

private:
    Ui::Widget *ui;
    QTcpSocket *m_socket;

};

#endif // WIDGET_H
