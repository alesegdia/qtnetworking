#include "scene.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

SceneNode::SharedPtr Scene::queryNodeAt(const QPointF &position)
{
    SceneNode::SharedPtr queried_node = nullptr;
    for( auto node : m_nodes )
    {
        if( node->contains(position) )
        {
            queried_node = node;
            break;
        }
    }
    return queried_node;
}

void Scene::push(QSharedPointer<SceneNode> new_node)
{
    m_nodes.append(new_node);
}

void Scene::render(QPainter &painter)
{
    for( auto node : m_nodes )
    {
        node->render(painter);
    }
}

const QList<SceneNode::SharedPtr> Scene::nodes() const
{
    return m_nodes;
}

SceneNode::SharedPtr Scene::getNodeByIdx(SceneNode::IndexType idx)
{
    for( SceneNode::SharedPtr node : m_nodes )
    {
        if( node->index() == idx )
        {
            return node;
        }
    }
    return nullptr;
}
