#include "VisualizerWidget.h"

#include "CollisionDetector/CollisionDetector.h"

#include <algine/core/TypeRegistry.h>
#include <algine/core/painter/Painter.h>

namespace UI {
STATIC_INITIALIZER_IMPL(VisualizerWidget) {
    alRegisterType(VisualizerWidget);
}

inline static std::vector<Color> colors() {
    return {
        {255, 0, 0},
        {0, 255, 0},
        {0, 0, 255},
        {255, 255, 0},
        {255, 0, 255},
        {0, 255, 255},
        {255, 0, 255}
    };
}

VisualizerWidget::VisualizerWidget()
    : m_mode(Mode::None),
      m_colors(colors()),
      m_colorIndex(),
      m_pressedTriangleIndex(-1)
{
    setEventListener(Event::Click, [this](Widget*, const Event &event) {
        auto &inf = event.getPointerInfo();
        cd::vec2 p {inf.getX(), inf.getY()};

        switch (getMode()) {
            case Mode::Add:
                addPoint(p);
                break;
            case Mode::Remove:
                removeTriangle(p);
                break;
            case Mode::None:
                break;
        }
    });

    setEventListener(Event::Press, [this](Widget*, const Event &event) {
        if (getMode() != Mode::None)
            return;

        auto &info = event.getPointerInfo();
        m_prevCoords = {info.getX(), info.getY()};

        if (auto it = findTriangleAt(m_prevCoords); it != m_triangles.end()) {
            m_pressedTriangleIndex = static_cast<int>(std::distance(m_triangles.begin(), it));
        }
    });

    setEventListener(Event::Release, [this](Widget*, const Event &event) {
        if (getMode() != Mode::None)
            return;
        m_pressedTriangleIndex = -1;
    });

    setEventListener(Event::Move, [this](Widget*, const Event &event) {
        if (m_pressedTriangleIndex != -1) {
            auto &info = event.getPointerInfo();
            cd::vec2 newCoords = {info.getX(), info.getY()};
            cd::vec2 delta = newCoords - m_prevCoords;

            auto &t = m_triangles[m_pressedTriangleIndex];
            t.first[0] += delta;
            t.first[1] += delta;
            t.first[2] += delta;

            calcCollisions();
            invalidate();

            m_prevCoords = {info.getX(), info.getY()};
        }
    });
}

void VisualizerWidget::enterAddMode() {
    setMode(Mode::Add);
}

void VisualizerWidget::enterRemoveMode() {
    setMode(Mode::Remove);
}

VisualizerWidget::Mode VisualizerWidget::getMode() const {
    return m_mode;
}

VisualizerWidget::ModeSubject::Subscription_t VisualizerWidget::addOnModeChangedListener(
    const ModeSubject::Observer_t &listener
) {
    return m_onModeChanged.subscribe(listener);
}

void VisualizerWidget::onDraw(Painter &painter) {
    auto toPointF = [](const cd::vec2 &v) {
        return PointF {v.x, v.y};
    };

    constexpr float pointRadius = 4;

    auto drawPoint = [&](const cd::vec2 &v) {
        painter.drawCircle(toPointF(v), pointRadius);
    };

    // draw triangles
    for (auto & [triangle, color] : m_triangles) {
        painter.setPaint(Paint(color));
        painter.setOpacity(0.75f);

        for (int i = 0; i < 3; ++i)
            drawPoint(triangle[i]);

        painter.setOpacity(0.25f);

        painter.drawTriangle(
            toPointF(triangle[0]),
            toPointF(triangle[1]),
            toPointF(triangle[2]));
    }

    // draw points
    painter.setPaint(Paint(m_colors[m_colorIndex]));
    painter.setOpacity(0.75f);

    for (auto &p : m_tmpPoints) {
        drawPoint(p);
    }

    // draw collision bounding boxes
    painter.setPaint(Paint(Color(255, 0, 0)));
    painter.setOpacity(0.1f);

    for (const auto &rect : m_collisions) {
        auto rectScaled = rect;
        rectScaled.translate(-pointRadius, -pointRadius);
        rectScaled.setWidth(rect.getWidth() + 2 * pointRadius);
        rectScaled.setHeight(rect.getHeight() + 2 * pointRadius);
        painter.drawRect(rectScaled);
    }
}

void VisualizerWidget::setMode(Mode mode) {
    m_mode = mode;
    m_onModeChanged.notify(m_mode);
}

void VisualizerWidget::addPoint(const cd::vec2 &p) {
    m_tmpPoints.emplace_back(p);

    if (m_tmpPoints.size() != 3) {
        invalidate();
    } else {
        cd::triangle t;
        std::copy(m_tmpPoints.begin(), m_tmpPoints.end(), t.points.begin());
        m_triangles.emplace_back(t, m_colors[m_colorIndex]);

        ++m_colorIndex;
        m_colorIndex %= static_cast<int>(m_colors.size());

        m_tmpPoints = {};
        setMode(Mode::None);

        calcCollisions();
        invalidate();
    }
}

void VisualizerWidget::removeTriangle(const cd::vec2 &p) {
    if (auto it = findTriangleAt(p); it != m_triangles.end()) {
        m_triangles.erase(it);
        setMode(Mode::None);
        calcCollisions();
        invalidate();
    }
}

// definitely not the best way to REcalculate the collisions,
// but for a small number of triangles it will work just fine
void VisualizerWidget::calcCollisions() {
    m_collisions.clear();

    for (int i = 0; i < m_triangles.size(); ++i) {
        cd::triangle &t1 = m_triangles[i].first;

        for (int j = i + 1; j < m_triangles.size(); ++j) {
            cd::triangle &t2 = m_triangles[j].first;

            if (cd::isColliding(t1, t2)) {
                // calc bounding box
                auto [minX, maxX] = std::minmax({t1[0].x, t1[1].x, t1[2].x, t2[0].x, t2[1].x, t2[2].x});
                auto [minY, maxY] = std::minmax({t1[0].y, t1[1].y, t1[2].y, t2[0].y, t2[1].y, t2[2].y});
                m_collisions.emplace_back(PointF {minX, minY}, PointF {maxX, maxY});
            }
        }
    }
}

decltype(VisualizerWidget::m_triangles)::iterator VisualizerWidget::findTriangleAt(const cd::vec2 &p) {
    return std::ranges::find_if(m_triangles, [&](const std::pair<cd::triangle, Color> &pair) {
        return cd::isInside(p, pair.first);
    });
}
} // UI