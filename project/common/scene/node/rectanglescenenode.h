#ifndef RECTANGLESCENENODE_H
#define RECTANGLESCENENODE_H

#include "scenenode.h"

class RectangleSceneNode : public SceneNode
{
public:
    RectangleSceneNode(IndexType idx, QPointF position, float width, float height);

    void render(QPainter& painter) override;
    NetworkEvent creationEvent() override;

};

#endif // RECTANGLESCENENODE_H
