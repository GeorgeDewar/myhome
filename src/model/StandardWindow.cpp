#include "StandardWindow.h"
#include "Opening.h"
#include <expected>
#include <QJsonObject>

void StandardWindow::from_json(const QJsonObject &json, StandardWindow &standardWindow) {
    QString id = json.value("id").toString();
}