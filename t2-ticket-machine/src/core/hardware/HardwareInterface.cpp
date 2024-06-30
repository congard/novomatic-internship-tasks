#include "hardware/HardwareInterface.h"

namespace tmc {
HardwareInterface::ErrorSubject::Subscription_t HardwareInterface::addOnErrorListener(
    const ErrorSubject::Observer_t &listener
) {
    return m_onError.subscribe(listener);
}

void HardwareInterface::error(const HardwareError &error) {
    m_onError.notify(error);
}
} // tmc