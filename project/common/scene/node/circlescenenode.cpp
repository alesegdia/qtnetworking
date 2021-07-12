#include "circlescenenode.h"


CircleSceneNode::CircleSceneNode(IndexType idx, QPointF position, float xdiag, float ydiag)
    : SceneNode(idx, QRectF(position, QSizeF(xdiag, ydiag)))
{

}

CircleSceneNode::~CircleSceneNode() {

}

void CircleSceneNode::render(QPainter& painter)
{
    painter.drawEllipse(aabb());
}

NetworkEvent CircleSceneNode::creationEvent()
{
    return NetworkEvent::CreateCircle;
}
