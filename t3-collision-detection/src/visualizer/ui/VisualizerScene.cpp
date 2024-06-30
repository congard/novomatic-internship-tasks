#include "VisualizerScene.h"
#include "VisualizerLayer.h"

namespace UI {
VisualizerScene::VisualizerScene(Object *parent)
    : Widgets::Scene(parent)
{
    auto layer = new VisualizerLayer(this);
    layer->show();
}
}
