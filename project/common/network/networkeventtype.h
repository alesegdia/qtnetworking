#ifndef NETWORKEVENTTYPE_H
#define NETWORKEVENTTYPE_H

#include <cstdint>
#include <QtGlobal>

/**
 * @brief The NetworkEventType enum defines the type of events which
 * can be sent throught the network from the server to the client to
 * persist the state of the scene.
 * The following events are used:
 *  - CreateTriangle:   [ index,  x,  y,  base,   height ]
 *  - CreateRectangle:  [ index,  x,  y,  width,  height ]
 *  - CreateCircle:     [ index,  x,  y,  radius         ]
 *  - MoveNode:         [ index,  x,  y                  ]
 */

typedef quint8 NetworkEventType;
enum class NetworkEvent : NetworkEventType
{
    CreateTriangle = 0,
    CreateRectangle,
    CreateCircle,
    MoveNode
};

#endif // NETWORKEVENTTYPE_H
