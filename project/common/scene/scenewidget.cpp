#include "scenewidget.h"

SceneWidget::SceneWidget(QWidget *parent)
    : QWidget(parent)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

SceneWidget::~SceneWidget()
{

}

void SceneWidget::setScene(Scene::SharedPtr scene)
{
    m_scene = scene;
}

void SceneWidget::sceneUpdated()
{
    repaint();
}

void SceneWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if( false == m_scene.isNull() )
    {
        m_scene->render(painter);
    }
    else
    {
        painter.setPen(Qt::red);
        painter.drawText(QRectF(0, 0, 300, 300), "SCENE NOT SET IN THE WIDGET");
    }
}

Scene::SharedPtr SceneWidget::scene()
{
    return m_scene;
}

