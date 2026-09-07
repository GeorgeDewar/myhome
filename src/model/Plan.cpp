#include "Plan.h"
#include "Building.h"
#include <QJsonArray>
#include <utility>

std::expected<Plan, QString> Plan::fromJson(const QJsonObject &json)
{
    Plan plan = Plan();
    QJsonArray buildingsArray = json.value("buildings").toArray();
    for(int i = 0; i < buildingsArray.size(); ++i) {
        qDebug() << "Parsing building " << i;
        QJsonObject buildingObj = buildingsArray[i].toObject();
        Building building = Building::fromJson(buildingObj).value();
        plan.buildings_.push_back(std::move(building));
    }
    return plan;
}