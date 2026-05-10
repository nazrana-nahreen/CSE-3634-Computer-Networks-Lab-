#include "Sender.h"

Define_Module(Sender);

void Sender::initialize()
{
    // Create the message; default field values are hopCount=0, ttl=15
    // (defined in MyMessage.msg)
    MyMessage *msg = new MyMessage("packet");

    EV << "[Sender] Sending packet with hopCount=" << msg->getHopCount()
       << "  ttl=" << msg->getTtl() << "\n";

    // Send immediately at t=0 on the single output gate
    send(msg, "out");
}

void Sender::handleMessage(cMessage *msg)
{
    // Sender never receives messages in this design – ignore
    delete msg;
}
