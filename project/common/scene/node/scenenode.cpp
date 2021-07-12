#include "scenenode.h"

SceneNode::~SceneNode()
{

}

SceneNode::SceneNode(IndexType idx, const QRectF &aabb)
{
    m_aabb = aabb;
    m_idx = idx;
}

bool SceneNode::contains(QPointF point) const
{
    return m_aabb.contains(point);
}

const QPointF SceneNode::position() const
{
    return m_aabb.bottomLeft();
}

void SceneNode::moveTo(const QPointF &new_position)
{
    m_aabb.moveTo(new_position);
}

SceneNode::IndexType SceneNode::index()
{
    return m_idx;
}

QRectF SceneNode::aabb()
{
    return m_aabb;
}
