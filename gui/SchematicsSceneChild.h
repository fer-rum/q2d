#ifndef SCHEMATICSSCENECHILD_H
#define SCHEMATICSSCENECHILD_H

#include <QGraphicsItem>

namespace q2d {
namespace gui {

class SchematicsScene;

/**
 * @brief The SchematicsSceneChild class encapsules all functionality
 * shared by all items that might be used in SchematicsScene-instances.
 * This is mainly to reduce coding work and code duplication.
 */
class SchematicsSceneChild {

protected:
    SchematicsScene* m_scene;
public:
    SchematicsSceneChild(SchematicsScene* scene);

    SchematicsScene* scene() const;
};

} // namespace gui
} // namespace q2d

#endif // SCHEMATICSSCENECHILD_H
