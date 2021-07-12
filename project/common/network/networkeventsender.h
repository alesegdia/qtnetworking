#ifndef NETSCENEEVENTDISPATCHER_H
#define NETSCENEEVENTDISPATCHER_H

#include <QVector2D>
#include <QByteArray>
#include <QDataStream>
#include <QTcpSocket>
#include <QTcpServer>
#include <QList>

#include "../scene/scene.h"
#include "../scene/node/scenenode.h"
#include "../scene/sceneeventlistener.h"
#include "networkeventtype.h"

/**
 * @brief The NetworkEventSender class is responsible for handling newly connected
 * clients, emiting new events to them and persisting initial data on new connections
 */
class NetworkEventSender : public QObject, public SceneEventListener
{
    Q_OBJECT
public:
    NetworkEventSender(Scene::SharedPtr);

    /**
     * @brief onTriangleCreated emits the creation of a triangle to all the clients
     */
    void onTriangleCreated(SceneNode::IndexType idx, QPointF position, float base, float height) override;

    /**
     * @brief onRectangleCreated emits the creation of a rectangle to all the clients
     */
    void onRectangleCreated(SceneNode::IndexType idx, QPointF position, float width, float height) override;

    /**
     * @brief onCircleCreated emits the creation of a circle to all the clients
     */
    void onCircleCreated(SceneNode::IndexType idx, QPointF position, float xdiag, float ydiag) override;

    /**
     * @brief onNodeMoved emits the translation of a node to all the clients
     */
    void onNodeMoved(SceneNode::IndexType idx, QPointF new_pos);

public slots:
    /**
     * @brief newConnectionServer slot is launched when a new connection has arrived and it is needed to
     * persist initial data and add the new client to the client list
     */
    void newConnectionServer();

private:
    /**
     * @brief broadcastData sends data to all the clients
     * @param data the data to be sent
     */
    void broadcastData(QByteArray data);

    /**
     * @brief onNodeCreated helps on the creation of the payload for creation events
     * @param evt the event to set in the payload
     * @param idx the index of the node to be created
     * @param pos the position of the node
     * @param p1 the first generic parameter
     * @param p2 the second generic parameter
     * @return a buffer with the payload
     */
    QByteArray onNodeCreated(NetworkEvent evt, SceneNode::IndexType idx, QPointF pos, float p1, float p2);

    /**
     * @brief sendInitialData sends the currently created scene nodes to a newly connected client
     * @param client the client to send the data to
     */
    void sendInitialData(QTcpSocket* client);

    /**
     * @brief m_tcpServer is the responsible for handling new connections
     */
    QTcpServer m_tcpServer;

    /**
     * @brief m_clients the list of clients
     */
    QList<QTcpSocket*> m_clients;

    /**
     * @brief m_scene the scene is needed to send initial data to newly connected clients
     */
    Scene::SharedPtr m_scene;

};

#endif // NETSCENEEVENTDISPATCHER_H
