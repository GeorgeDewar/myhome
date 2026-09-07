#pragma once

#include "OpeningItem.h"
#include <expected>
#include <memory>
#include <vector>
#include <QString>
#include <QJsonObject>

class Opening final
{
    public:
        Opening(QString id, double distanceAlongWall, double distanceFromFloor, double width, double height)
            : id_(std::move(id)), distanceAlongWall_(distanceAlongWall), distanceFromFloor_(distanceFromFloor), width_(width), height_(height) {}
        static std::expected<Opening, QString> fromJson(const QJsonObject &json);

        const QString& id() const { return id_; }
        double distanceAlongWall() const { return distanceAlongWall_; }
        double distanceFromFloor() const { return distanceFromFloor_; }
        double width() const { return width_; }
        double height() const { return height_; }
        double edgeDistanceFromWall() const { return distanceAlongWall_ - (width_ / 2.0); }
        const std::vector<std::unique_ptr<OpeningItem>>& contents() const { return contents_; }
    private:
        QString id_;
        double distanceAlongWall_;
        double distanceFromFloor_;
        double width_;
        double height_;
        std::vector<std::unique_ptr<OpeningItem>> contents_;
};