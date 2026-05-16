#ifndef RECEIVER_H_
#define RECEIVER_H_

#include <omnetpp.h>
#include "MyMessage_m.h"

using namespace omnetpp;

/**
 * Receiver module.
 * Records the final hopCount of every arriving packet.
 * Emits the hopCount as a statistic signal for the OMNeT++ result framework.
 */
class Receiver : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

  private:
    simsignal_t finalHopCountSignal;
    simsignal_t droppedPacketsSignal;
    int packetsReceived;
    long totalHops;
};

#endif
