#include "StandardDoor.h"
#include "Opening.h"
#include <expected>
#include <QJsonObject>

void StandardDoor::from_json(const QJsonObject &json, StandardDoor &standardDoor) {
    QString id = json.value("id").toString();
    double thickness = json.value("thickness").toDouble(35.0) / 1000.0; // Convert from mm to m
    HingeSide hingeSide = json.value("hingeSide").toString() == "right" ? HingeSide::Right : HingeSide::Left;
    SwingDirection swingDirection = json.value("swingDirection").toString() == "out" ? SwingDirection::Outward : SwingDirection::Inward;
    standardDoor.thickness = thickness;
    standardDoor.hingeSide = hingeSide;
    standardDoor.swingDirection = swingDirection;
}