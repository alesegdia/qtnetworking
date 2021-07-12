#ifndef EDITABLESCENEWIDGET_H
#define EDITABLESCENEWIDGET_H

#include <QLabel>

#include "scenewidget.h"
#include "nodefactory.h"
#include "sceneeventlistener.h"

/**
 * @brief The EditableSceneWidget class is a SceneWidget that can
 * edit the scene, adding and moving elements by using a set of tools
 */
class EditableSceneWidget : public SceneWidget
{

    Q_OBJECT

public:
    EditableSceneWidget(QWidget* parent = 0);

    /**
     * @brief setListener sets a generic listener which will be notified about creation and translation events
     * @param listener the listener to notify to
     */
    void setListener(SceneEventListener::SharedPtr listener);

    /**
     * @brief setScene sets the scene that will be modified
     * @param scene the scene
     */
    void setScene(Scene::SharedPtr scene) override;

public slots:
    /**
     * @brief onTriangleToolClicked called when triangle tool button was selected
     */
    void onTriangleToolClicked(bool c);


    /**
     * @brief onRectangleToolClicked called when rectangle tool button was selected
     */
    void onRectangleToolClicked(bool c);


    /**
     * @brief onCircleToolClicked called when circle tool button was selected
     */
    void onCircleToolClicked(bool c);

    /**
     * @brief onMoveToolClicked called when move (translation) tool button was selected
     */
    void onMoveToolClicked(bool c);

    /**
     * @brief setNewNodeSize changes the size that newly created nodes will have
     * @param value the new size
     */
    void setNewNodeSize(int value);

private:
    /**
     * @brief mouseMoveEvent is overriden to use with move tool
     * @param event
     */
    void mouseMoveEvent(QMouseEvent* event) override;

    /**
     * @brief mousePressEvent is overriden to handle the tools
     * @param event
     */
    void mousePressEvent(QMouseEvent* event) override;

    /**
     * @brief mousePressEvent is overriden to handle the tools
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent* event) override;

    SceneNode::IndexType nextIndex();

    enum class ToolIndex : uint8_t {
        NoTool,
        NewTriangle,
        NewCircle,
        NewRectangle,
        MoveElement
    };

    /**
     * @brief m_infoLabel a label to notify about the selected tool
     */
    QLabel m_infoLabel;

    /**
     * @brief m_selectedTool the selected tool
     */
    ToolIndex m_selectedTool = ToolIndex::NoTool;

    /**
     * @brief m_nodeFactory the node factory to create new elements
     */
    NodeFactory m_nodeFactory;

    /**
     * @brief m_lastIndex is used to create new unique indices
     */
    SceneNode::IndexType m_lastIndex = 0;

    /**
     * @brief m_eventListener is a generic scene event listener
     */
    SceneEventListener::SharedPtr m_eventListener = nullptr;

    /**
     * @brief m_selectedNode the selected node for the move tool
     */
    SceneNode::SharedPtr m_selectedNode = nullptr;

    /**
     * @brief m_newNodeSize the size of newly created nodes
     */
    float m_newNodeSize = 30.f;

};

#endif // EDITABLESCENEWIDGET_H
