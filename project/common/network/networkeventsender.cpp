#include "networkeventsender.h"

NetworkEventSender::NetworkEventSender(Scene::SharedPtr scene)
{
    m_tcpServer.listen(QHostAddress::Any, 12345);
    QObject::connect(&m_tcpServer, SIGNAL(newConnection()),
                     this, SLOT(newConnectionServer()));
    m_scene = scene;
}

void NetworkEventSender::onTriangleCreated(SceneNode::IndexType idx, QPointF position, float base, float height)
{
    broadcastData(onNodeCreated(NetworkEvent::CreateTriangle, idx, position, base, height));
}

void NetworkEventSender::onRectangleCreated(SceneNode::IndexType idx, QPointF position, float width, float height)
{
    broadcastData(onNodeCreated(NetworkEvent::CreateRectangle, idx, position, width, height));
}

void NetworkEventSender::onCircleCreated(SceneNode::IndexType idx, QPointF position, float xdiag, float ydiag)
{
    broadcastData(onNodeCreated(NetworkEvent::CreateCircle, idx, position, xdiag, ydiag));
}

void NetworkEventSender::onNodeMoved(SceneNode::IndexType idx, QPointF new_pos)
{
    QByteArray payload;
    QDataStream stream(&payload, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_9);
    stream.setByteOrder(QDataStream::BigEndian);
    stream << uint8_t(NetworkEvent::MoveNode) << idx << new_pos.x() << new_pos.y();
    broadcastData(payload);
}

void NetworkEventSender::newConnectionServer()
{
    while(m_tcpServer.hasPendingConnections())
    {
        qDebug() << "New client connected";
        QTcpSocket* new_client = m_tcpServer.nextPendingConnection();
        sendInitialData(new_client);
        m_clients.append(new_client);
    }
}

void NetworkEventSender::broadcastData(QByteArray data)
{
    for( QTcpSocket* client : m_clients )
    {
        client->write(data);
    }
}

void NetworkEventSender::sendInitialData(QTcpSocket *client)
{
    for(SceneNode::SharedPtr node : m_scene->nodes() )
    {
        QPointF point = node->position() - QPointF(0, node->aabb().height());
        QByteArray data = onNodeCreated(
                    node->creationEvent(),
                    node->index(),
                    point,
                    node->aabb().width(),
                    node->aabb().height());
        client->write(data);
    }
}

QByteArray NetworkEventSender::onNodeCreated(NetworkEvent evt, SceneNode::IndexType idx, QPointF pos, float p1, float p2)
{
    QByteArray payload;
    QDataStream stream(&payload, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_9);
    stream.setByteOrder(QDataStream::BigEndian);
    stream << uint8_t(evt) << idx << pos.x() << pos.y() << p1 << p2;
    return payload;
}
