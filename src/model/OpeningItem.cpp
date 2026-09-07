#include "OpeningItem.h"
#include "StandardDoor.h"

std::unique_ptr<OpeningItem> OpeningItem::fromJson(const QJsonObject &json)
{
    const auto type = json.value("type").toString().toStdString();
    if (type == "StandardDoor") {
        auto standardDoor = std::make_unique<StandardDoor>();
        StandardDoor::from_json(json, *standardDoor);
        return standardDoor;
    }

    qDebug() << "Unknown opening item type: " << QString::fromStdString(type);
    return nullptr;
}