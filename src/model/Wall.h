#pragma once

#include <QPoint>
#include <expected>
#include <QJsonObject>

class Wall final
{
    public:
        Wall(QPointF startPoint, QPointF endPoint);
        static std::expected<Wall, QString> fromJson(const QJsonObject &json);

        QPointF startPoint() const { return startPoint_; }
        QPointF endPoint() const { return endPoint_; }
        double thickness() const { return thickness_; }
    
    private:
        QPointF startPoint_;
        QPointF endPoint_;
        double thickness_ {0.1}; // Default thickness in metres
};