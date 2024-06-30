#include "VisualizerContent.h"
#include "ui/VisualizerScene.h"

#include <algine/core/Framebuffer.h>
#include <algine/core/Window.h>
#include <algine/core/font/FontLibrary.h>

VisualizerContent::VisualizerContent(Object *parent)
    : Content(parent)
{
    FontLibrary::setDefault(Font("BreezeSans-Medium.ttf"));

    m_scene = new UI::VisualizerScene(this);
    m_scene->listen(this);
}

void VisualizerContent::onShow() {
    getWindow()->setEventHandler(this);
    m_scene->setSize(width(), height());
    m_scene->show();
}

void VisualizerContent::render() {
    Framebuffer::getDefault()->bind();
    Framebuffer::getDefault()->clear(Framebuffer::ColorBuffer | Framebuffer::DepthBuffer);
    Engine::setViewport(width(), height());
    m_scene->render();
}
