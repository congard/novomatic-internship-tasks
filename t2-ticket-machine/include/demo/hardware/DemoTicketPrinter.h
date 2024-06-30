#ifndef TMC_DEMO_DEMOTICKETPRINTER_H
#define TMC_DEMO_DEMOTICKETPRINTER_H

#include <tulz/threading/ThreadPool.h>

#include "hardware/TicketPrinter.h"

namespace tmc::demo {
class DemoTicketPrinter : public TicketPrinter {
public:
    DemoTicketPrinter();

    void print(const IssuedTicket &ticket, const Callback &callback) override;

private:
    tulz::ThreadPool m_pool;
};
}

#endif //TMC_DEMO_DEMOTICKETPRINTER_H
