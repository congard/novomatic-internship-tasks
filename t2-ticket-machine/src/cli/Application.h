#ifndef T2_TICKET_MACHINE_APPLICATION_H
#define T2_TICKET_MACHINE_APPLICATION_H

#include "ftxui/component/screen_interactive.hpp"

#include "DemoTicketMachine.h"
#include "Page.h"
#include "MainPage.h"

class Application {
public:
    Application();

    tmc::demo::DemoTicketMachine& ticketMachine();
    ftxui::ScreenInteractive& screen();

    void exec();

private:
    ftxui::ScreenInteractive m_screen;

private:
    tmc::demo::DemoTicketMachine m_ticketMachine;

private:
    MainPage m_mainPage;
};

#endif //T2_TICKET_MACHINE_APPLICATION_H
