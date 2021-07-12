#include "rectanglescenenode.h"


RectangleSceneNode::RectangleSceneNode(IndexType idx, QPointF position, float width, float height)
    : SceneNode(idx, QRectF(position, QSizeF(width, height)))
{

}

void RectangleSceneNode::render(QPainter& painter)
{
    painter.drawRect(aabb());
}

NetworkEvent RectangleSceneNode::creationEvent()
{
    return NetworkEvent::CreateRectangle;
}
