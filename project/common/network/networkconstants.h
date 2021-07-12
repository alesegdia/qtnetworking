#pragma once

#include <QtGlobal>

class NetworkConstants
{
public:
    /**
     * @brief DefaultPort is the port the app uses to connect in client and server
     */
    static constexpr quint16 DefaultPort = 12345;

    /**
     * @brief ClientFetchNetworkDataInterval is the interval of time passing
     * between network receiver checks on incoming data through the socket
     */
    static constexpr int ClientFetchNetworkDataInterval = 10;
};
