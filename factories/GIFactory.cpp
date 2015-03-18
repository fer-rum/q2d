
#include "../DocumentEntry.h"
#include "../Enumerations.h"
#include "../gui/ComponentGraphicsItem.h"
#include "../gui/PortGraphicsItem.h"
#include "../metamodel/ComponentDescriptor.h"
#include "../metamodel/PortDescriptor.h"
#include "GIFactory.h"

#include <QString>
#include <QtDebug>

using namespace q2d::constants;
using namespace q2d::factories;
using namespace q2d::gui;
using namespace q2d::metamodel;

unsigned int
GIFactory::TEXT_PADDING = 5;

QGraphicsItem*
GIFactory::createComponentGI(
        ComponentDescriptor *type){

    qDebug() << "Generating Graphics item for" << type->text();

    // collect all the information
    QString componentName = type->text();

    QGraphicsItemGroup* parent = new QGraphicsItemGroup();

    // create all the partial items and calculate sizes

    unsigned int inSection_minWidth = 0;
    unsigned int outSection_minWidth = 0;
    unsigned int portSection_lineHeight = 0;

    QMap<PortDescriptor*, QGraphicsTextItem*> inPorts = QMap<PortDescriptor*, QGraphicsTextItem*>();
    QMap<PortDescriptor*, QGraphicsTextItem*> outPorts = QMap<PortDescriptor*, QGraphicsTextItem*>();
    for(PortDescriptor* port : type->ports()){

        QGraphicsTextItem* textItem = new QGraphicsTextItem(port->text(), parent);
        parent->addToGroup(textItem);
        unsigned int width = textItem->boundingRect().width() + 2 * TEXT_PADDING;
        unsigned int height = textItem->boundingRect().height() + 2 * TEXT_PADDING;

        // adjust the line height, if needed
        if(height > portSection_lineHeight){
            portSection_lineHeight = height;
        }

        switch (port->direction()){
        case model::enums::PortDirection::IN : {
            inPorts.insert(port, textItem);
            if(width > inSection_minWidth){
                inSection_minWidth = width;
            }
        }
            break;

        case model::enums::PortDirection::OUT : {
            outPorts.insert(port, textItem);
            if(width > outSection_minWidth){
                outSection_minWidth = width;
            }
        }
            break;
        default: continue; // do not handle other types.
        }

    }

    unsigned int portSection_height =
            inPorts.count() > outPorts.count() ?
                inPorts.count() * portSection_lineHeight :
                outPorts.count() * portSection_lineHeight;

    QGraphicsTextItem* text_compName = new QGraphicsTextItem(componentName, parent);
    parent->addToGroup(text_compName);

    unsigned int nameSection_minWidth = text_compName->boundingRect().width() + 2 * TEXT_PADDING;
    unsigned int nameSection_height = text_compName->boundingRect().height() + 2 * TEXT_PADDING;

    // adjust the total width
    unsigned int totalWidth  = 0;
    if(nameSection_minWidth > (inSection_minWidth + outSection_minWidth)){
        totalWidth = nameSection_minWidth;
        if(inSection_minWidth > totalWidth / 2){ // extend outSection_minWidth
            outSection_minWidth = totalWidth - inSection_minWidth;
        } else if(outSection_minWidth > totalWidth / 2){ // extend inSection_minWidth
            inSection_minWidth = totalWidth - outSection_minWidth;
        } else { // stretch both to totalWidth / 2
            inSection_minWidth = totalWidth / 2;
            outSection_minWidth = totalWidth / 2;
        }
    } else { // adjust nameSection_minWidth
        totalWidth = inSection_minWidth + outSection_minWidth;
    }

    // now actually place all the stuff
    QBrush nameSectionBrush = QBrush(Qt::lightGray, Qt::SolidPattern);
    QBrush portSectionBrush = QBrush(Qt::white, Qt::SolidPattern);
    QPen pen = QPen(Qt::black, Qt::SolidLine);
    QPoint currentPos = QPoint(0,0);

    // draw the rectangles
    QGraphicsRectItem* nameSection = new QGraphicsRectItem(
                                        currentPos.x(), currentPos.y(),
                                        totalWidth, nameSection_height, parent);
    nameSection->setBrush(nameSectionBrush);
    nameSection->setPen(pen);
    nameSection->setZValue(-1);
    parent->addToGroup(nameSection);

    currentPos.ry() += nameSection_height;
    QGraphicsRectItem* inSection = new QGraphicsRectItem(
                                      currentPos.x(), currentPos.y(),
                                      inSection_minWidth, portSection_height, parent);
    inSection->setBrush(portSectionBrush);
    inSection->setPen(pen);
    inSection->setZValue(-1);
    parent->addToGroup(inSection);

    currentPos.rx() += inSection_minWidth;
    QGraphicsRectItem* outSection = new QGraphicsRectItem(
                                      currentPos.x(), currentPos.y(),
                                      outSection_minWidth, portSection_height, parent);
    outSection->setBrush(portSectionBrush);
    outSection->setPen(pen);
    outSection->setZValue(-1);
    parent->addToGroup(outSection);

    // place the texts and set the port positions in the port descriptor
    text_compName->setPos((totalWidth - text_compName->boundingRect().width())/ 2,
                         /*0 + */ TEXT_PADDING);

    currentPos.setX(0);
    currentPos.setY(nameSection_height);
    QMapIterator<PortDescriptor*, QGraphicsTextItem*> inIter(inPorts);
    while(inIter.hasNext()){
        inIter.next();
        inIter.value()->setPos(currentPos.x() + TEXT_PADDING, currentPos.y() + TEXT_PADDING);
        currentPos.ry() += portSection_lineHeight / 2;
        inIter.key()->setPosition(QPoint(
                    currentPos.x() - PORT_RADIUS,
                    currentPos.y()));
        currentPos.ry() += portSection_lineHeight /2;
    }

    currentPos.setX(totalWidth);
    currentPos.setY(nameSection_height);
   QMapIterator<PortDescriptor*, QGraphicsTextItem*> outIter(outPorts);
    while(outIter.hasNext()){
        outIter.next();
        outIter.value()->setPos(
                    currentPos.x() - TEXT_PADDING - outIter.value()->boundingRect().width(),
                    currentPos.y() + TEXT_PADDING);
        currentPos.ry() += portSection_lineHeight / 2;
        outIter.key()->setPosition(QPoint(
                                       currentPos.x() + PORT_RADIUS,
                                       currentPos.y()));
        currentPos.ry() += portSection_lineHeight /2;
    }

    parent->setVisible(true);
    return parent;
}


QAbstractGraphicsShapeItem*
GIFactory::createPortAdapterGI(){
    // cast here otherwise -PORT_RADIUS will be about 4 billion and something
    // since PORT_RADIUS is unsigned
    const qreal r = (qreal)PORT_RADIUS;
    QPainterPath path;
    path.moveTo(0, -r);
    path.lineTo(r, -r);
    path.lineTo(r, r);
    path.lineTo(0, r);
    // and now back to close it
    path.lineTo(r, r);
    path.lineTo(r, -r);
    path.closeSubpath();

    QGraphicsPathItem* adapter = new QGraphicsPathItem(path);
    adapter->setVisible(true);
    return adapter;
}

QAbstractGraphicsShapeItem* GIFactory::createPortAdapteeGI(){
    // cast here otherwise -PORT_RADIUS will be about 4 billion and something
    // since PORT_RADIUS is unsigned
    const qreal r = (qreal)PORT_RADIUS;
    QGraphicsRectItem* adaptee = new QGraphicsRectItem(-r/2, -r/2, r, r);
    adaptee->setVisible(true);
    return adaptee;
}

QAbstractGraphicsShapeItem*
GIFactory::createPortInvalidGI(){
    // cast here otherwise -PORT_RADIUS will be about 4 billion and something
    // since PORT_RADIUS is unsigned
    const qreal r = (qreal)PORT_RADIUS;
    QPainterPath path;
    path.moveTo(-r, -r);
    path.lineTo(r, r);
    path.moveTo(r, -r);
    path.lineTo(-r, r);
    return new QGraphicsPathItem(path);
}
