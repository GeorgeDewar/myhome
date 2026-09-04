#pragma once

class Opening;
class QPainter;
class Wall;

class WindowRenderer final {
public:
    explicit WindowRenderer(QPainter *painter) : painter_(painter) {}

    void renderWindow(const Wall &wall, const Opening &window);

private:
    QPainter *painter_;
};