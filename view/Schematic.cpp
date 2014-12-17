#include "Schematic.h"

using namespace q2d::view;

Schematic::Schematic(QObject *parent) :
    QGraphicsScene(parent) {
    this->setBackgroundBrush(QColor(255, 245, 200)); // TOPDO later: get from settings
    this->update();
}

Schematic::~Schematic(){}
