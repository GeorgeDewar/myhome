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
    if (opening.contents_.size() == 1) {
        // If there's only one item, set its width and height to match the opening's dimensions
        opening.contents_[0]->setId(opening.id()); // Set the door's ID to match the opening's ID
        opening.contents_[0]->setWidth(opening.width());
        opening.contents_[0]->setHeight(opening.height());
    }
    return opening;
}
