#include "networkeventreceiver.h"
#include "networkeventtype.h"
#include "networkconstants.h"

NetworkEventReceiver::NetworkEventReceiver(Scene::SharedPtr scene, QSharedPointer<QTcpSocket> tcpsocket)
{
    QObject::connect(&m_readDataTimer, SIGNAL(timeout()),
                     this, SLOT(checkIncomingData()));
    m_readDataTimer.start(NetworkConstants::ClientFetchNetworkDataInterval);
    m_socket = tcpsocket;
    m_nodeFactory.setScene(scene);
    m_scene = scene;
}

void NetworkEventReceiver::launchConnection(QString ip)
{
    if( false == m_socket->isOpen() )
    {
        qDebug() << "Connecting";
        m_socket->connectToHost(ip, NetworkConstants::DefaultPort);
    }
}

void NetworkEventReceiver::checkIncomingData()
{
    if( 0 != m_socket->bytesAvailable() )
    {
        SceneNode::IndexType idx;
        float x, y, p1, p2;
        QDataStream stream(m_socket.data());
        stream.setVersion(QDataStream::Qt_5_9);
        stream.setByteOrder(QDataStream::BigEndian);
        NetworkEventType event_type;
        stream >> event_type;
        NetworkEvent evt = (NetworkEvent)event_type;
        switch(evt)
        {
        case NetworkEvent::CreateCircle:
            stream >> idx;
            stream >> x;
            stream >> y;
            stream >> p1; // xdiag
            stream >> p2; // ydiag
            m_nodeFactory.newCircle(idx, QPointF(x, y), p1, p2);
            emit sceneUpdated();
            break;
        case NetworkEvent::CreateTriangle:
            stream >> idx;
            stream >> x;
            stream >> y;
            stream >> p1; // base
            stream >> p2; // height
            m_nodeFactory.newTriangle(idx, QPointF(x, y), p1, p2);
            emit sceneUpdated();
            break;
        case NetworkEvent::CreateRectangle:
            stream >> idx;
            stream >> x;
            stream >> y;
            stream >> p1; // width
            stream >> p2; // height
            m_nodeFactory.newRect(idx, QPointF(x, y), p1, p2);
            emit sceneUpdated();
            break;
        case NetworkEvent::MoveNode:
            stream >> idx;
            stream >> x;
            stream >> y;
            SceneNode::SharedPtr node = m_scene->getNodeByIdx(idx);
            if( node != nullptr )
            {
                node->moveTo(QPointF(x, y));
            }
            emit sceneUpdated();
            break;
        }
    }
}

