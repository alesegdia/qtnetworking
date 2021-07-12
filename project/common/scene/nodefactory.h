#ifndef NODEFACTORY_H
#define NODEFACTORY_H

#include <QSharedPointer>

#include "scene.h"
#include "node/trianglescenenode.h"
#include "node/circlescenenode.h"
#include "node/rectanglescenenode.h"
#include "scenewidget.h"


/**
 * @brief The NodeFactory class creates derived node instances
 * given a predefined index and push them to the scene
 */
class NodeFactory
{
public:

    typedef QSharedPointer<NodeFactory> SharedPtr;

    /**
     * @brief NodeFactory constructor assigns the scene where to push new nodes
     * @param scene the scene to push new items to
     */
    NodeFactory();

    void setScene(Scene::SharedPtr scene);

    /**
     * @brief newTriangle creates a new triangle into the scene
     * @param idx the index to assign to the node
     * @param position the starting position where to create the node
     * @param base the base of the new triangle
     * @param height the height of the new triangle
     */
    void newTriangle(uint8_t idx, QPointF position, float base, float height);

    /**
     * @brief newCircle creates a new circle into the scene
     * @param idx the index to assign to the node
     * @param position the starting position where to create the node
     * @param radius the radius of the new circle
     */
    void newCircle(uint8_t idx, QPointF position, float xdiag, float ydiag);

    /**
     * @brief newRect creates a new rectangle into the scene
     * @param idx the index to assign to the node
     * @param position the starting position where to create the node
     * @param width the base of the new rectangle
     * @param height the height of the new rectangle
     */
    void newRect(uint8_t idx, QPointF position, float width, float height);

private:
    /**
     * @brief m_scene the scene where the new nodes will be pushed to
     */
    Scene::SharedPtr m_scene;

};

#endif // NODEFACTORY_H
