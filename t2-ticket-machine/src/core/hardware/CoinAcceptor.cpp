#include "hardware/CoinAcceptor.h"

namespace tmc {
CoinAcceptor::CoinSubject::Subscription_t CoinAcceptor::addOnCoinAcceptedListener(
    const CoinSubject::Observer_t &listener
) {
    return m_onCoinAccepted.subscribe(listener);
}

CoinAcceptor::CoinSubject::Subscription_t CoinAcceptor::addOnCoinReturnedListener(
    const CoinSubject::Observer_t &listener
) {
    return m_onCoinReturned.subscribe(listener);
}

void CoinAcceptor::coinAccepted(CoinValue value) {
    m_onCoinAccepted.notify(value);
}

void CoinAcceptor::coinReturned(CoinValue value) {
    m_onCoinReturned.notify(value);
}
} // tmc