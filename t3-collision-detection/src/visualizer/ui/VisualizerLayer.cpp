#include "VisualizerLayer.h"
#include "VisualizerWidget.h"

#include <algine/core/widgets/Container.h>
#include <algine/core/widgets/Label.h>

namespace UI {
VisualizerLayer::VisualizerLayer(Widgets::Scene *parent)
    : Widgets::Layer(parent)
{
    auto container = Widget::constructFromXMLFile<Container*>("Visualizer.xml", this);
    setContainer(container);

    auto status = container->findChild<Label*>("status");

    auto visualizer = container->findChild<VisualizerWidget*>();
    visualizer->addOnModeChangedListener([status](VisualizerWidget::Mode mode) {
        switch (mode) {
            using enum VisualizerWidget::Mode;

            case None:
                status->setText("Click add to add a new triangle!");
                break;
            case Add:
                status->setText("Feel free to add new points!");
                break;
            case Remove:
                status->setText("Click on a triangle to remove it");
                break;
        }
    });

    container->findChild<Widget*>("btnAdd")->setEventListener(Event::Click, [=](Widget*, const Event &event) {
        if (visualizer->getMode() == VisualizerWidget::Mode::None) {
            visualizer->enterAddMode();
        }
    });

    container->findChild<Widget*>("btnRemove")->setEventListener(Event::Click, [=](Widget*, const Event &event) {
        if (visualizer->getMode() == VisualizerWidget::Mode::None) {
            visualizer->enterRemoveMode();
        }
    });
}
}// namespace ui