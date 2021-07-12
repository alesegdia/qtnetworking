#ifndef TRIANGLESCENENODE_H
#define TRIANGLESCENENODE_H

#include <QSharedPointer>
#include <QVector2D>

#include "scenenode.h"

class TriangleSceneNode : public SceneNode
{
public:
    TriangleSceneNode(SceneNode::IndexType idx, QPointF position, float base, float height);
    ~TriangleSceneNode();

    void render(QPainter& painter);

    NetworkEvent creationEvent() override;


};

#endif // TRIANGLESCENENODE_H
