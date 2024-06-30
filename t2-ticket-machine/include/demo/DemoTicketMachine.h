#ifndef TMC_DEMO_DEMOTICKETMACHINE_H
#define TMC_DEMO_DEMOTICKETMACHINE_H

#include "TicketMachine.h"

namespace tmc::demo {
class DemoTicketMachine : public TicketMachine {
public:
    DemoTicketMachine();

    void insertCoin(CoinValue value);
};
}

#endif //TMC_DEMO_DEMOTICKETMACHINE_H
