#include "Application.h"

Application::Application()
    : m_screen(ftxui::ScreenInteractive::FitComponent()),
      m_mainPage(this) {}

tmc::demo::DemoTicketMachine& Application::ticketMachine() {
    return m_ticketMachine;
}

ftxui::ScreenInteractive& Application::screen() {
    return m_screen;
}

void Application::exec() {
    m_mainPage.show();
}
