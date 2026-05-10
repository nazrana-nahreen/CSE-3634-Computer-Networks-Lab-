#ifndef ROUTER_H_
#define ROUTER_H_

#include <omnetpp.h>
#include "MyMessage_m.h"

using namespace omnetpp;

/**
 * Router module.
 *
 * On every received MyMessage:
 *   1. Increment hopCount.
 *   2. Decrement ttl.
 *   3. If ttl == 0  → drop the packet (delete it) and record the drop.
 *   4. Otherwise    → pick a random connected output gate and forward.
 *
 * Only gates that are actually connected are candidates for forwarding.
 */
class Router : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

  private:
    // Statistics
    int totalForwarded;
    int totalDropped;

    // Signals for OMNeT++ result recording
    simsignal_t hopCountSignal;
    simsignal_t droppedSignal;
};

#endif
