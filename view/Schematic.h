#ifndef SCHEMATIC_H
#define SCHEMATIC_H

#include <QGraphicsScene>

namespace q2d {
namespace view {

class Schematic : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Schematic(QObject *parent = 0);

signals:

public slots:

};

} // namespace view
} // namespace q2d

#endif // SCHEMATIC_H
