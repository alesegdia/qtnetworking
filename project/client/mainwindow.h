#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../common/scene/scene.h"
#include "../common/network/networkeventreceiver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void connectButtonClicked();
    void socketError(QAbstractSocket::SocketError);
    void socketConnected();
    void socketDisconnected();

signals:
    void launchConnection(QString ip);

private:
    Ui::MainWindow *ui;
    Scene::SharedPtr m_scene;
    NetworkEventReceiver::SharedPtr m_networkEventReceiver;
    QString m_lastTriedConnectionIP = "";

};

#endif // MAINWINDOW_H
