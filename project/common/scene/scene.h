#ifndef SCENE_H
#define SCENE_H

#include <QVector2D>
#include <QSharedPointer>

#include "node/scenenode.h"


/**
 * @brief The Scene class represents a set of nodes of varied shape
 */
class Scene
{
public:

    typedef QSharedPointer<Scene> SharedPtr;

    Scene();
    ~Scene();

    /**
     * @brief queryNodeAt queries a node at a specified point
     * @param position the point where trying to fetch a node from
     * @return a pointer to the found node or nullptr if no node was found
     */
    SceneNode::SharedPtr queryNodeAt(const QPointF &position);

    /**
     * @brief push adds a node to the scene
     * @param new_node the node to add to the scene
     */
    void push(QSharedPointer<SceneNode> new_node);

    /**
     * @brief render renders the scene using a specified QPainter
     * @param painter the painter associated to the surface where to draw the scene
     */
    void render(QPainter& painter);

    /**
     * @brief nodes const list of nodes
     * @return the const list of nodes
     */
    const QList<SceneNode::SharedPtr> nodes() const;

    /**
     * @brief getNodeByIdx fetches a node by its unique index
     * @param idx the index of the node to search
     * @return the node found or nullptr if no node was found with the specified index
     */
    SceneNode::SharedPtr getNodeByIdx(SceneNode::IndexType idx);

private:
    /**
     * @brief m_nodes the list of nodes
     */
    QList<SceneNode::SharedPtr> m_nodes;

};

#endif // SCENE_H
