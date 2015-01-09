#include "ComponentType.h"

#include "ComponentCategory.h"

#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QtDebug>
#include <qt5/QtSvg/QtSvg>

using namespace q2d;

// TODO outsouce some of the calls
/**
 * @brief ComponentType::ComponentType
 * If the symbol is not found, no icon will be set.
 * The actual name is set from the file.
 *
 * @param descriptionFile
 * @param symbol ; May be null
 *
 * Assumption: name is not empty
 */
ComponentType::ComponentType(QString descriptionFileName, ComponentCategory* parent) :
    ComponentDescriptor("unnamed component", parent) {

    Q_ASSERT(!descriptionFileName.isEmpty());

    QFile* descriptionFile = new QFile(descriptionFileName);
    // make sure the file exists and can be read
    Q_ASSERT(descriptionFile->exists());

    QJsonDocument jsonDocument;

    // read the description file
    bool ok = descriptionFile->open(QIODevice::ReadOnly | QIODevice::Text);
    if(!ok){
        qWarning() << "On instantiating component type: Could not open file "
                   << descriptionFile->fileName();
    } else {
        QByteArray binaryData = descriptionFile->readAll();
        jsonDocument = QJsonDocument::fromJson(binaryData);
        descriptionFile->close();
    }

    Q_ASSERT(!jsonDocument.isNull());

    // set the name appropriately
    QJsonObject jsonObject = jsonDocument.object();
    QJsonValue nameValue = jsonObject.value("name");
    if(nameValue != QJsonValue::Undefined && nameValue.isString()){
        this->setText(nameValue.toString());
    }

    // TODO read all the other stuff that might come in handy

    // load the symbol file
    QJsonValue symbolPathValue = jsonObject.value("symbolFile");
    if(symbolPathValue != QJsonValue::Undefined && symbolPathValue.isString()){
        QFileInfo descriptionFileInfo = QFileInfo(*descriptionFile);
        QString symbolFilePath = descriptionFileInfo.absolutePath() + "/" + symbolPathValue.toString();

        this->loadCircuitSymbol(symbolFilePath);
    }
}

/**
 * @brief ComponentType::setCircuitSymbol sets the circuit symbol from a given svg file
 * and derives an icon from it
 * @param symbolFilePath
 */
void
ComponentType::loadCircuitSymbol(QString symbolFilePath){

    if(symbolFilePath == nullptr){
        // TODO error message
        return;
    }

    QGraphicsSvgItem* symbol = new QGraphicsSvgItem(symbolFilePath);
    if(symbol == nullptr){
        // TODO error message
        return;
    }

    this->setSymbolPath(symbolFilePath);

    // Create Icon for UI from Svg
    // TODO support seperate Icon files as determined by json
    QIcon* icon = new QIcon(symbolFilePath);
    this->setIcon(*icon);
    // TODO possible memory leak
    // find all above objects that are no longer referenced after setting the icon
//    }
}

void
ComponentType::setSymbolPath(QString symbolPath){
    // TODO instead of setting the pointer (evil segfault)
    // one should set either the SVG source or the file path
    this->setData(QVariant::fromValue(symbolPath), ComponentDescriptorRole::CIRCUIT_SYMBOL_FILE);
}
