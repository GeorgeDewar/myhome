#include "Wall.h"
#include "Opening.h"
#include <QJsonObject>
#include <expected>
#include <QJsonArray>
#include <QPen>
#include <QVector2D>

Wall::Wall(QString id, QPointF startPoint, QPointF endPoint, double thickness)
    : id_(std::move(id)), startPoint_(startPoint), endPoint_(endPoint), thickness_(thickness) {}

std::expected<Wall, QString> Wall::fromJson(const QJsonObject &json) {
    QString id = json.value("id").toString();
    auto start = json.value("start").toArray();
    auto end = json.value("end").toArray();
    QPointF startPoint(start[0].toDouble() / 1000.0, start[1].toDouble() / 1000.0); // Convert from mm to m
    QPointF endPoint(end[0].toDouble() / 1000.0, end[1].toDouble() / 1000.0); // Convert from mm to m
    double thickness = json.value("thickness").toDouble(0.1); // Default thickness in metres

    // Parse openings
    std::vector<Opening> openings;
    auto openingsArray = json.value("openings").toArray();
    for (const auto &openingValue : openingsArray) {
        if (auto opening = Opening::fromJson(openingValue.toObject()); opening) {
            openings.push_back(std::move(*opening));
        }
    }

    Wall wall(std::move(id), startPoint, endPoint, thickness);
    wall.openings_ = std::move(openings);
    return wall;
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

QPolygonF Wall::openingPolygon(const Opening& opening) const {
    const QVector2D direction(endPoint_ - startPoint_);
    if (direction.isNull()) {
        return {};
    }

    const QVector2D unitDirection = direction.normalized();
    const QVector2D halfThickness(-unitDirection.y() * thickness_ / 2.0,
                                  unitDirection.x() * thickness_ / 2.0);
    const QPointF start = startPoint_ + unitDirection.toPointF() * (opening.edgeDistanceFromWall());
    const QPointF end = start + unitDirection.toPointF() * (opening.width());
    return {
        start + halfThickness.toPointF(),
        end + halfThickness.toPointF(),
        end - halfThickness.toPointF(),
        start - halfThickness.toPointF(),
    };
}