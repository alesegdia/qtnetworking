#include "nodefactory.h"


NodeFactory::NodeFactory()
{

}

void NodeFactory::setScene(Scene::SharedPtr scene)
{
    m_scene = scene;
}

void NodeFactory::newTriangle(uint8_t idx, QPointF position, float base, float height)
{
    m_scene->push(SceneNode::SharedPtr(new TriangleSceneNode(idx, position, base, height)));
}

void NodeFactory::newCircle(uint8_t idx, QPointF position, float xdiag, float ydiag)
{
    m_scene->push(SceneNode::SharedPtr(new CircleSceneNode(idx, position, xdiag, ydiag)));
}

void NodeFactory::newRect(uint8_t idx, QPointF position, float width, float height)
{
    m_scene->push(SceneNode::SharedPtr(new RectangleSceneNode(idx, position, width, height)));
}
