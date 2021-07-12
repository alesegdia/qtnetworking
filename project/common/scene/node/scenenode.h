#ifndef ISCENENODE_H
#define ISCENENODE_H

#include <QVector2D>
#include <QSharedPointer>
#include <QPainter>

#include "../../network/networkeventtype.h"

/**
 * @brief The ISceneNode class represents a renderable entity in the scene
 */
class SceneNode
{
public:

    typedef QSharedPointer<SceneNode> SharedPtr;
    typedef uint8_t IndexType;

    SceneNode(IndexType idx, const QRectF& aabb);
    virtual ~SceneNode() = 0 ;

    /**
     * @brief contains checks if a point in space is contained by the node
     * @param point to test containment inside the scene node
     * @return true if the point is contained in the scene node, false otherwise
     */
    bool contains(QPointF point) const;

    /**
     * @brief render renders the scene node in the surface passed as parameter
     * @param surface where the scene node should be rendered
     */
    virtual void render(QPainter&) = 0 ;

    /**
     * @brief position returns node position
     * @return the node position
     */
    const QPointF position() const;

    /**
     * @brief moveTo sets the position to a new one
     * @param new_position the new position to set the node to
     */
    void moveTo(const QPointF& new_position);

    /**
     * @brief index returns the node index
     * @return the node index
     */
    IndexType index();

    /**
     * @brief aabb returns the aabb of the node
     * @return the aabb of the node
     */
    QRectF aabb();

    /**
     * @brief creationEvent returns the network event that creates this node through the network
     * @return the network event
     */
    virtual NetworkEvent creationEvent() = 0 ;

private:

    /**
     * @brief m_aabb contains the bounding box of the node in the space
     */
    QRectF m_aabb;

    /**
     * @brief m_idx is a unique index to identify the node
     */
    IndexType m_idx;

};

#endif // ISCENENODE_H
