#include "Wall.h"
#include <QJsonObject>
#include <expected>
#include <QJsonArray>
#include <QPen>

Wall::Wall(QPointF startPoint, QPointF endPoint) : startPoint_(startPoint), endPoint_(endPoint) {}

std::expected<Wall, QString> Wall::fromJson(const QJsonObject &json) {
    auto start = json.value("start").toArray();
    auto end = json.value("end").toArray();
    QPointF startPoint(start[0].toDouble() / 1000.0, start[1].toDouble() / 1000.0); // Convert from mm to m
    QPointF endPoint(end[0].toDouble() / 1000.0, end[1].toDouble() / 1000.0); // Convert from mm to m
    return Wall(startPoint, endPoint);
}
