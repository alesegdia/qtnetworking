#include "trianglescenenode.h"

TriangleSceneNode::TriangleSceneNode(IndexType idx, QPointF position, float base, float height)
    : SceneNode(idx, QRectF(position, QSizeF(base, height)))
{

}

TriangleSceneNode::~TriangleSceneNode()
{

}

void TriangleSceneNode::render(QPainter &painter)
{
    float half_width = aabb().width() / 2.f;
    QPointF p1, p2, p3;
    p1 = position();
    p2 = position() + QPointF(half_width, -aabb().height());
    p3 = position() + QPointF(aabb().width(), 0);
    painter.drawLine(p1, p2);
    painter.drawLine(p1, p3);
    painter.drawLine(p2, p3);
}

NetworkEvent TriangleSceneNode::creationEvent()
{
    return NetworkEvent::CreateTriangle;
}
