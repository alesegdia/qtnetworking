#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scene = Scene::SharedPtr(new Scene());
    ui->sceneWidget->setScene(m_scene);

    QSharedPointer<QTcpSocket> socket(new QTcpSocket());

    m_networkEventReceiver = NetworkEventReceiver::SharedPtr(new NetworkEventReceiver(m_scene, socket));

    QObject::connect(ui->connectButton, SIGNAL(pressed()),
                     this, SLOT(connectButtonClicked()));

    QObject::connect(this, SIGNAL(launchConnection(QString)),
                     m_networkEventReceiver.data(), SLOT(launchConnection(QString)));

    QObject::connect(m_networkEventReceiver.data(), SIGNAL(sceneUpdated()),
                     ui->sceneWidget, SLOT(sceneUpdated()));

    QObject::connect(socket.data(), SIGNAL(error(QAbstractSocket::SocketError)),
                     this, SLOT(socketError(QAbstractSocket::SocketError)));
    QObject::connect(socket.data(), SIGNAL(connected()),
                     this, SLOT(socketConnected()));
    QObject::connect(socket.data(), SIGNAL(disconnected()),
                     this, SLOT(socketDisconnected()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectButtonClicked()
{
    emit launchConnection(ui->hostLineEdit->text());
    m_lastTriedConnectionIP = ui->hostLineEdit->text();
    ui->statusLabel->setText("Trying to connect to " + m_lastTriedConnectionIP);
}

void MainWindow::socketError(QAbstractSocket::SocketError)
{
    ui->statusLabel->setText("There was an error trying to connect.");
}

void MainWindow::socketConnected()
{
    ui->statusLabel->setText("Successfully connected to " + m_lastTriedConnectionIP);
}

void MainWindow::socketDisconnected()
{
    ui->statusLabel->setText("Disconnected.");
}
