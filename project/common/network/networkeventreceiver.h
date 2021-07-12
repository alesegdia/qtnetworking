#ifndef NETWORKEVENTRECEIVER_H
#define NETWORKEVENTRECEIVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QSharedPointer>

#include "../scene/scene.h"
#include "../scene/nodefactory.h"

/**
 * @brief The NetworkEventReceiver class is responsible for checking incoming scene events
 * through the socket and pushing new items to the scene
 */
class NetworkEventReceiver : public QObject
{
    Q_OBJECT
public:

    typedef QSharedPointer<NetworkEventReceiver> SharedPtr;

    /**
     * @brief NetworkEventReceiver constructor
     * @param scene the scene where it will be pushing incoming events
     * @param tcpsocket the socket where it will be fetching data from
     */
    NetworkEventReceiver(Scene::SharedPtr scene, QSharedPointer<QTcpSocket> tcpsocket);

public slots:
    /**
     * @brief launchConnection slot is fired when the user tries to connect to a new ip
     * @param ip the ip to connect to
     */
    void launchConnection(QString ip);

    /**
     * @brief checkIncomingData slot is fired in a fixed interval so that it can check
     * for incoming data through the socket
     */
    void checkIncomingData();

signals:
    /**
     * @brief sceneUpdated signal purpose is to notify the widget about changes
     */
    void sceneUpdated();

private:
    /**
     * @brief m_socket the socket receiving incoming events
     */
    QSharedPointer<QTcpSocket> m_socket;

    /**
     * @brief m_readDataTimer the timer to fire reads on socket
     */
    QTimer m_readDataTimer;

    /**
     * @brief m_nodeFactory the node factory to create elements in the scene
     */
    NodeFactory m_nodeFactory;

    /**
     * @brief m_scene the scene that will be acted upon
     */
    Scene::SharedPtr m_scene;

};

#endif // NETWORKEVENTRECEIVER_H
