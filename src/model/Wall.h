#pragma once

#include <QPoint>
#include <QString>
#include <expected>
#include <QJsonObject>

class Wall final
{
    public:
        Wall(QString id, QPointF startPoint, QPointF endPoint);
        static std::expected<Wall, QString> fromJson(const QJsonObject &json);

        const QString& id() const { return id_; }
        QPointF startPoint() const { return startPoint_; }
        QPointF endPoint() const { return endPoint_; }
        double thickness() const { return thickness_; }
        QPolygonF areaPolygon() const;
    
    private:
        QString id_;
        QPointF startPoint_;
        QPointF endPoint_;
        double thickness_ {0.1}; // Default thickness in metres
};