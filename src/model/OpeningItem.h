#pragma once

#include <memory>
#include <QString>
#include <QJsonObject>

class OpeningItem {
    public:
        static std::unique_ptr<OpeningItem> fromJson(const QJsonObject &json);
        OpeningItem() = default;
        virtual ~OpeningItem() = default;

        virtual std::string type() const = 0;
        QString id() const { return id_; }
        double width() const { return width_; }
        double height() const { return height_; }
    protected:
        QString id_;
        double width_ {0.0};
        double height_ {0.0};
};