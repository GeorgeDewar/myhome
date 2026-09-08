#include "OpeningItem.h"
#include "StandardDoor.h"
#include "StandardWindow.h"

std::unique_ptr<OpeningItem> OpeningItem::fromJson(const QJsonObject &json)
{
    const auto type = json.value("type").toString().toStdString();
    if (type == "StandardDoor") {
        auto standardDoor = std::make_unique<StandardDoor>();
        StandardDoor::from_json(json, *standardDoor);
        return standardDoor;
    } else if (type == "StandardWindow") {
        auto standardWindow = std::make_unique<StandardWindow>();
        StandardWindow::from_json(json, *standardWindow);
        return standardWindow;
    }

    qDebug() << "Unknown opening item type: " << QString::fromStdString(type);
    return nullptr;
}