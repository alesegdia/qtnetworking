#ifndef CIRCLESCENENODE_H
#define CIRCLESCENENODE_H

#include "scenenode.h"

class CircleSceneNode : public SceneNode
{
public:
    CircleSceneNode(IndexType idx, QPointF position, float xdiag, float ydiag);
    ~CircleSceneNode();

    void render(QPainter& painter) override;
    NetworkEvent creationEvent() override;
};

#endif // CIRCLESCENENODE_H
