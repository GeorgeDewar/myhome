#pragma once

#include "OpeningItem.h"
#include "Opening.h"
#include <QString>
#include <QJsonObject>
#include <expected>

class StandardWindow final : public OpeningItem
{
    public:
        StandardWindow() : OpeningItem() { }
        std::string type() const override { return "StandardWindow"; }

        static void from_json(const QJsonObject &json, StandardWindow &standardWindow);
    private:
        
};