#ifndef SENDER_H_
#define SENDER_H_

#include <omnetpp.h>
#include "MyMessage_m.h"   // auto-generated from MyMessage.msg

using namespace omnetpp;

/**
 * Sender module.
 * At simulation start it creates one MyMessage (hopCount=0, ttl=15)
 * and sends it out through its single output gate.
 */
class Sender : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
