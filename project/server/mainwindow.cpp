#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../common/network/networkeventsender.h"

#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_scene = Scene::SharedPtr(new Scene());
    ui->sceneWidget->setScene(m_scene);

    QObject::connect(ui->triangleTool, SIGNAL(clicked(bool)),
                     ui->sceneWidget, SLOT(onTriangleToolClicked(bool)));
    QObject::connect(ui->rectangleTool, SIGNAL(clicked(bool)),
                     ui->sceneWidget, SLOT(onRectangleToolClicked(bool)));
    QObject::connect(ui->circleTool, SIGNAL(clicked(bool)),
                     ui->sceneWidget, SLOT(onCircleToolClicked(bool)));
    QObject::connect(ui->moveTool, SIGNAL(clicked(bool)),
                     ui->sceneWidget, SLOT(onMoveToolClicked(bool)));

    QObject::connect(ui->nodeSizeSlider, SIGNAL(sliderMoved(int)),
                     ui->sceneWidget, SLOT(setNewNodeSize(int)));

    QSharedPointer<SceneEventListener> listener = QSharedPointer<SceneEventListener>(new NetworkEventSender(m_scene));
    ui->sceneWidget->setListener(listener);
}

MainWindow::~MainWindow()
{
    delete ui;
}

