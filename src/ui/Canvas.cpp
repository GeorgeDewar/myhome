#include "Canvas.h"

#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include "model/Plan.h"
#include "model/Building.h"
#include "model/Level.h"
#include "renderer/WallRenderer.h"

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(400, 300);
    setMouseTracking(true);
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(rect(), QColor("#f8fafc"));
    painter.save();

    paintGrid(painter);
    painter.scale(scale_, scale_);
    painter.translate(-offset_);
    paintPlan(painter);
    painter.restore();
    paintOriginMarker(painter);
}

void Canvas::paintGrid(QPainter &painter) {
    painter.setPen(QColor("#d9e2ec"));
    int gridSpacing = static_cast<int>(std::round(1.0 * scale_)); // 1 metre
    for (int x = 0; x < width(); x += gridSpacing) {
        int offsetX = -offset_.x() * scale_;
        painter.drawLine(x + (offsetX % gridSpacing), 0, x + (offsetX % gridSpacing), height());
    }
    for (int y = 0; y < height(); y += gridSpacing) {
        int offsetY = -offset_.y() * scale_;
        painter.drawLine(0, y + (offsetY % gridSpacing), width(), y + (offsetY % gridSpacing));
    }
}

void Canvas::paintOriginMarker(QPainter &painter) {
    painter.setPen(QColor("#ff0000"));
    QPointF origin = toCanvasCoordinates(QPointF(0.0, 0.0));
    painter.drawLine(origin.x() - 10, origin.y(), origin.x() + 10, origin.y());
    painter.drawLine(origin.x(), origin.y() - 10, origin.x(), origin.y() + 10);
}

void Canvas::paintPlan(QPainter &painter) {
    if (!plan_) {
        return;
    }
    WallRenderer wallRenderer(&painter, this);
    wallRenderer.renderWalls(*plan_, currentLevel_);
}

QPointF Canvas::toCanvasCoordinates(const QPointF &point) {
    return QPointF(
        (point.x() - offset_.x()) * scale_,
        (point.y() - offset_.y()) * scale_
    );
}

QPointF Canvas::toRealCoordinates(const QPointF &point) {
    return QPointF(
        point.x() / scale_ + offset_.x(),
        point.y() / scale_ + offset_.y()
    );
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::MiddleButton) {
        lastMousePosition_ = event->pos(); // Save start position
        setCursor(Qt::ClosedHandCursor); // Change cursor to closed hand
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    emit cursorPositionChanged(toRealCoordinates(event->position()));
    if (event->buttons() & Qt::MiddleButton) {
        QPoint delta = event->pos() - lastMousePosition_;
        offset_ -= QPointF(delta.x() / scale_, delta.y() / scale_);
        emit offsetChanged(offset_);
        lastMousePosition_ = event->pos();
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    unsetCursor(); // Change cursor back to default
    if (event->button() == Qt::LeftButton) {
        plan_->forCurrentLevelOfEachBuilding(currentLevel_, [this, event](const Building &, const Level &level) {
            const auto &walls = level.getWalls();
            for (const auto &wall : walls) {
                const auto polygon = wall.areaPolygon();
                if (polygon.containsPoint(toRealCoordinates(event->position()), Qt::OddEvenFill)) {
                    // Handle wall selection or interaction here
                    qInfo() << "Wall selected: " << wall.id();
                    emit wallSelected(wall);
                }
            }
        });
    }
}

double Canvas::scale() const
{
    return scale_;
}

QPointF Canvas::offset() const
{
    return offset_;
}

void Canvas::wheelEvent(QWheelEvent *event)
{
    if (event->buttons() & Qt::MiddleButton) {
        // ignore, as we are panning with the middle mouse button
        return;
    }

    const QPointF mousePosition = event->position();
    const QPointF realPosition = toRealCoordinates(mousePosition);

    // Three zooms will double the scale
    double scaleFactor = std::pow(2, 1.0 / 8.0);
    if (event->angleDelta().y() > 0) {
        // Zoom in
        scale_ *= scaleFactor;
    } else {
        // Zoom out
        scale_ /= scaleFactor;
    }
    if (scale_ < minimumScale_) {
        scale_ = minimumScale_;
    } else if (scale_ > maximumScale_) {
        scale_ = maximumScale_;
    }

    offset_ = realPosition - mousePosition / scale_;

    emit scaleChanged(scale_);
    emit offsetChanged(offset_);
    update();
}

void Canvas::setPlan(const Plan *plan) {
    plan_ = plan;
    update();
}

void Canvas::setCurrentLevel(int level) {
    currentLevel_ = level;
    update();
}