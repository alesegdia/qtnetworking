#include "editablescenewidget.h"

#include <QDebug>
#include <QMouseEvent>

EditableSceneWidget::EditableSceneWidget(QWidget *parent)
    : SceneWidget(parent),
      m_infoLabel(this)
{
    m_infoLabel.setText("No tool selected");
    QPalette pal;
    pal.setColor(m_infoLabel.backgroundRole(), Qt::white);
    m_infoLabel.setAutoFillBackground(true);
    m_infoLabel.setPalette(pal);
}


void EditableSceneWidget::setListener(SceneEventListener::SharedPtr listener)
{
    m_eventListener = listener;
}

void EditableSceneWidget::setScene(Scene::SharedPtr scene)
{
    SceneWidget::setScene(scene);
    m_nodeFactory.setScene(scene);
}

void EditableSceneWidget::onTriangleToolClicked(bool c)
{
    Q_UNUSED(c);
    m_infoLabel.setText("Triangle tool");
    m_selectedTool = ToolIndex::NewTriangle;
}

void EditableSceneWidget::onRectangleToolClicked(bool c)
{
    Q_UNUSED(c);
    m_infoLabel.setText("Rectangle tool");
    m_selectedTool = ToolIndex::NewRectangle;
}

void EditableSceneWidget::onCircleToolClicked(bool c)
{
    Q_UNUSED(c);
    m_infoLabel.setText("Circle tool");
    m_selectedTool = ToolIndex::NewCircle;
}

void EditableSceneWidget::onMoveToolClicked(bool c)
{
    Q_UNUSED(c);
    m_infoLabel.setText("Move tool");
    m_selectedTool = ToolIndex::MoveElement;
}

void EditableSceneWidget::setNewNodeSize(int value)
{
    m_newNodeSize = value;
}

void EditableSceneWidget::mouseMoveEvent(QMouseEvent *event)
{
    if( m_selectedTool == ToolIndex::MoveElement )
    {
        if( false == m_selectedNode.isNull() )
        {
            SceneNode::SharedPtr node = m_selectedNode;
            QPointF new_pos = event->pos() - QPointF(node->aabb().width() / 2, node->aabb().height() / 2);
            node->moveTo(new_pos);
            if( false == m_eventListener.isNull() )
            {
                m_eventListener->onNodeMoved(node->index(), new_pos);
            }
            repaint();
        }
    }
}

void EditableSceneWidget::mousePressEvent(QMouseEvent *event)
{
    float box_size = m_newNodeSize;

    SceneNode::IndexType idx;
    QPointF clicked_pos = event->pos() - QPointF(box_size / 2.f, box_size  / 2.f);

    switch(m_selectedTool)
    {
    case ToolIndex::NewCircle:
        idx = nextIndex();
        m_nodeFactory.newCircle(idx, clicked_pos, box_size, box_size);
        if( false == m_eventListener.isNull() )
        {
            m_eventListener->onCircleCreated(idx, clicked_pos, box_size, box_size);
        }
        repaint();
        break;
    case ToolIndex::NewRectangle:
        idx = nextIndex();
        m_nodeFactory.newRect(idx, clicked_pos, box_size, box_size);
        if( false == m_eventListener.isNull() )
        {
            m_eventListener->onRectangleCreated(idx, clicked_pos, box_size, box_size);
        }
        repaint();
        break;
    case ToolIndex::NewTriangle:
        idx = nextIndex();
        m_nodeFactory.newTriangle(idx, clicked_pos, box_size, box_size);
        if( false == m_eventListener.isNull() )
        {
            m_eventListener->onTriangleCreated(idx, clicked_pos, box_size, box_size);
        }
        repaint();
        break;
    case ToolIndex::MoveElement:
        m_selectedNode = scene()->queryNodeAt(event->pos());
        break;
    default:
        break;
    }
}

void EditableSceneWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if( m_selectedTool == ToolIndex::MoveElement )
    {
        m_selectedNode = nullptr;
    }
}

SceneNode::IndexType EditableSceneWidget::nextIndex()
{
    return m_lastIndex++;
}
