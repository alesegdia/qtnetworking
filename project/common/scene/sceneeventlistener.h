#ifndef SCENEEVENTLISTENER_H
#define SCENEEVENTLISTENER_H

#include <QSharedPointer>

#include "node/scenenode.h"

/**
 * @brief The SceneEventListener interface represents an object that should be
 * notified about events in a scene
 */
class SceneEventListener
{
public:

    typedef QSharedPointer<SceneEventListener> SharedPtr;

    virtual ~SceneEventListener() = 0;

    /**
     * @brief onTriangleCreated a new triangle was created event
     */
    virtual void onTriangleCreated(SceneNode::IndexType idx, QPointF position, float base, float height) = 0;

    /**
     * @brief onRectangleCreated a new rectangle was created event
     */
    virtual void onRectangleCreated(SceneNode::IndexType idx, QPointF position, float width, float height) = 0;

    /**
     * @brief onCircleCreated a new circle was created event
     */
    virtual void onCircleCreated(SceneNode::IndexType idx, QPointF position, float xdiag, float ydiag) = 0;

    /**
     * @brief onNodeMoved node was moved to a new position
     */
    virtual void onNodeMoved(SceneNode::IndexType idx, QPointF new_pos) = 0;

};

#endif // SCENEEVENTLISTENER_H
