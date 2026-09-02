#include "Wall.h"
#include <QJsonObject>
#include <expected>
#include <QJsonArray>
#include <QPen>
#include <QVector2D>

Wall::Wall(QPointF startPoint, QPointF endPoint) : startPoint_(startPoint), endPoint_(endPoint) {}

std::expected<Wall, QString> Wall::fromJson(const QJsonObject &json) {
    auto start = json.value("start").toArray();
    auto end = json.value("end").toArray();
    QPointF startPoint(start[0].toDouble() / 1000.0, start[1].toDouble() / 1000.0); // Convert from mm to m
    QPointF endPoint(end[0].toDouble() / 1000.0, end[1].toDouble() / 1000.0); // Convert from mm to m
    return Wall(startPoint, endPoint);
}

QPolygonF Wall::areaPolygon() const {
    const QVector2D direction(endPoint_ - startPoint_);
    if (direction.isNull()) {
        return {};
    }

    const QVector2D unitDirection = direction.normalized();
    const QVector2D halfThickness(-unitDirection.y() * thickness_ / 2.0,
                                  unitDirection.x() * thickness_ / 2.0);
    const QPointF start = startPoint_ - unitDirection.toPointF() * (thickness_ / 2.0);
    const QPointF end = endPoint_ + unitDirection.toPointF() * (thickness_ / 2.0);
    return {
        start + halfThickness.toPointF(),
        end + halfThickness.toPointF(),
        end - halfThickness.toPointF(),
        start - halfThickness.toPointF(),
    };
}