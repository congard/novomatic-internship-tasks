#ifndef T2_TICKET_MACHINE_COINACCEPTOR_H
#define T2_TICKET_MACHINE_COINACCEPTOR_H

#include <tulz/observer/Subject.h>

#include "model/CoinDesc.h"
#include "HardwareInterface.h"

namespace tmc {
class CoinAcceptor : public HardwareInterface {
public:
    using CoinSubject = tulz::Subject<CoinValue>;
    using ErrorSubject = tulz::Subject<const HardwareError&>;

    using Coins = std::vector<CoinDesc>;

public:
    CoinSubject::Subscription_t addOnCoinAcceptedListener(const CoinSubject::Observer_t &listener);
    CoinSubject::Subscription_t addOnCoinReturnedListener(const CoinSubject::Observer_t &listener);

    virtual size_t getCoinCount(CoinValue value) const = 0;
    virtual Coins getCoins() const = 0;

    virtual void inserted(CoinValue value) = 0;
    virtual void returnCoin(CoinValue value) = 0;

protected:
    void coinAccepted(CoinValue value);
    void coinReturned(CoinValue value);

private:
    CoinSubject m_onCoinAccepted;
    CoinSubject m_onCoinReturned;
};
} // tmc

#endif //T2_TICKET_MACHINE_COINACCEPTOR_H
