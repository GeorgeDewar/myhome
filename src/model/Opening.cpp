#include "Opening.h"
#include <expected>
#include <QJsonObject>
#include <QJsonArray>

std::expected<Opening, QString> Opening::fromJson(const QJsonObject &json) {
    QString id = json.value("id").toString();
    double distanceAlongWall = json.value("distanceAlongWall").toDouble() / 1000.0; // Convert from mm to m
    double distanceFromFloor = json.value("distanceFromFloor").toDouble() / 1000.0; // Convert from mm to m
    double width = json.value("width").toDouble() / 1000.0; // Convert from mm to m
    double height = json.value("height").toDouble() / 1000.0; // Convert from mm to m
    double thickness = json.value("thickness").toDouble(35.0) / 1000.0; // Convert from mm to m
    HingeSide hingeSide = json.value("hingeSide").toString() == "right" ? HingeSide::Right : HingeSide::Left;
    SwingDirection swingDirection = json.value("swingDirection").toString() == "out" ? SwingDirection::Outward : SwingDirection::Inward;
    return Opening(std::move(id), distanceAlongWall, distanceFromFloor, width, height, thickness, hingeSide, swingDirection);
}

// QPolygonF Opening::areaPolygon() const {
//     const QVector2D direction(endPoint_ - startPoint_);
//     if (direction.isNull()) {
//         return {};
//     }

//     const QVector2D unitDirection = direction.normalized();
//     const QVector2D halfThickness(-unitDirection.y() * thickness_ / 2.0,
//                                   unitDirection.x() * thickness_ / 2.0);
//     const QPointF start = startPoint_ - unitDirection.toPointF() * (thickness_ / 2.0);
//     const QPointF end = endPoint_ + unitDirection.toPointF() * (thickness_ / 2.0);
//     return {
//         start + halfThickness.toPointF(),
//         end + halfThickness.toPointF(),
//         end - halfThickness.toPointF(),
//         start - halfThickness.toPointF(),
//     };
// }