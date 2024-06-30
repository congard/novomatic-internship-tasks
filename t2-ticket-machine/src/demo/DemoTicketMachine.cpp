#include "DemoTicketMachine.h"
#include "hardware/DemoCoinAcceptor.h"
#include "hardware/DemoTicketPrinter.h"
#include "provider/DemoTicketProvider.h"
#include "algorithm/DemoChangeCalculator.h"

namespace tmc::demo {
DemoTicketMachine::DemoTicketMachine() : TicketMachine(
        std::make_unique<DemoCoinAcceptor>(),
        std::make_unique<DemoTicketPrinter>(),
        std::make_unique<DemoTicketProvider>(),
        std::make_unique<DemoChangeCalculator>()) {}

void DemoTicketMachine::insertCoin(CoinValue value) {
    m_coinAcceptor->inserted(value);
}
}