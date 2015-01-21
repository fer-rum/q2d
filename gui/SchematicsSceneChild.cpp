#include "SchematicsSceneChild.h"
#include "SchematicsScene.h"

using namespace q2d::gui;

SchematicsSceneChild::SchematicsSceneChild(SchematicsScene *scene){
    Q_CHECK_PTR(scene);
    m_scene = scene;
}

SchematicsScene*
SchematicsSceneChild::scene() const {
    return m_scene;
}
