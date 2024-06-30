#ifndef T2_TICKET_MACHINE_HARDWAREINTERFACE_H
#define T2_TICKET_MACHINE_HARDWAREINTERFACE_H

#include <tulz/observer/Subject.h>

#include "HardwareError.h"

namespace tmc {
class HardwareInterface {
private:
    using ErrorSubject = tulz::Subject<const HardwareError&>;

public:
    virtual ~HardwareInterface() = default;

    ErrorSubject::Subscription_t addOnErrorListener(const ErrorSubject::Observer_t &listener);

    virtual void error(const HardwareError &error);

private:
    ErrorSubject m_onError;
};
} // tmc

#endif //T2_TICKET_MACHINE_HARDWAREINTERFACE_H
