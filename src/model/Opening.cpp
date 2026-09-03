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
    return Opening(std::move(id), distanceAlongWall, distanceFromFloor, width, height);
}