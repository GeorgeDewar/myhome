#include "WallRenderer.h"
#include "DoorRenderer.h"
#include "WindowRenderer.h"
#include "model/Plan.h"
#include "model/OpeningItem.h"
#include "model/StandardDoor.h"
#include <QPen>
#include <QPainterPath>

void WallRenderer::renderWalls(const Plan &plan, int currentLevel) {
    DoorRenderer doorRenderer(painter_);
    WindowRenderer windowRenderer(painter_);
    plan.forCurrentLevelOfEachBuilding(currentLevel, [this, &doorRenderer, &windowRenderer](const Building &, const Level &level) {
        const auto &walls = level.getWalls();
        QPainterPath wallArea;
        for (const auto &wall : walls) {
            const QPolygonF polygon = wall.areaPolygon();
            if (polygon.isEmpty()) {
                qWarning() << "Wall has zero length, skipping.";
                continue;
            }

            QPainterPath wallFramingPath;
            wallFramingPath.addPolygon(polygon);
            wallFramingPath.closeSubpath();
            
            for (const auto &opening : wall.openings()) {
                const QPolygonF openingPolygon = wall.openingPolygon(opening);
                if (!openingPolygon.isEmpty()) {
                    QPainterPath openingPath;
                    openingPath.addPolygon(openingPolygon);
                    openingPath.closeSubpath();
                    wallFramingPath = wallFramingPath.subtracted(openingPath);
                }
            }

            wallArea = wallArea.united(wallFramingPath);
        }

        // Fill in the wall area, representing the framing, in solid yellow
        painter_->setPen(Qt::NoPen);
        painter_->setBrush(QColor(255, 215, 0));
        painter_->drawPath(wallArea);

        // Draw the wall outlines in black
        QPen liningPen(Qt::black);
        liningPen.setWidth(0); // Cosmetic: always one physical screen pixel.
        painter_->setPen(liningPen);
        painter_->setBrush(Qt::NoBrush);
        painter_->drawPath(wallArea);

        for (const auto &wall : walls) {
            for (const auto &opening : wall.openings()) {
                for (const auto &item : opening.contents()) {
                    if (item->type() == "StandardDoor") {
                        doorRenderer.renderDoor(wall, opening, static_cast<const StandardDoor&>(*item));
                    } else if (item->type() == "StandardWindow") {
                        windowRenderer.renderWindow(wall, opening);
                    } else {
                        qDebug() << "Unknown opening item type: " << QString::fromStdString(item->type());
                    }
                }
            }
        }
    });
}
