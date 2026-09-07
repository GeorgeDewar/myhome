#include "Opening.h"
#include "OpeningItem.h"
#include <expected>
#include <QJsonObject>
#include <QJsonArray>

std::expected<Opening, QString> Opening::fromJson(const QJsonObject &json) {
    QString id = json.value("id").toString();
    double distanceAlongWall = json.value("distanceAlongWall").toDouble() / 1000.0; // Convert from mm to m
    double distanceFromFloor = json.value("distanceFromFloor").toDouble() / 1000.0; // Convert from mm to m
    double width = json.value("width").toDouble() / 1000.0; // Convert from mm to m
    double height = json.value("height").toDouble() / 1000.0; // Convert from mm to m
    auto opening = Opening(std::move(id), distanceAlongWall, distanceFromFloor, width, height);
    QJsonArray contents = json.value("contents").toArray();
    for(int i = 0; i < contents.size(); ++i) {
        qDebug() << "Parsing opening item " << i;
        QJsonObject openingItemObj = contents[i].toObject();
        if (auto openingItem = OpeningItem::fromJson(openingItemObj)) {
            opening.contents_.push_back(std::move(openingItem));
        }
    }
    return opening;
}
