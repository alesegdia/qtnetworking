#ifndef SURFACEWIDGET_H
#define SURFACEWIDGET_H

#include <QWidget>
#include <QPainter>

#include "scene.h"

/**
 * @brief The SceneWidget class is a widget that draws an external scene of nodes
 */
class SceneWidget : public QWidget
{

    Q_OBJECT

public:

    typedef QSharedPointer<SceneWidget> SharedPtr;

    SceneWidget(QWidget* parent = 0);
    ~SceneWidget();

    /**
     * @brief setScene sets the scene to render
     * @param scene the scene to render
     */
    virtual void setScene(Scene::SharedPtr scene);

public slots:
    /**
     * @brief sceneUpdated used to notify the widget that the scene
     * was changed and needs a repaint
     */
    void sceneUpdated();

protected:
    /**
     * @brief paintEvent the function overriden to render the scene
     * @param event
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief scene accessor for sublcasses
     * @return the scene
     */
    Scene::SharedPtr scene();

private:
    /**
     * @brief m_scene the external scene to render
     */
    Scene::SharedPtr m_scene;

};

#endif // SURFACEWIDGET_H
