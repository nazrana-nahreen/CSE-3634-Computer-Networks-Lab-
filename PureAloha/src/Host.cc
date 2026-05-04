#include <omnetpp.h>
using namespace omnetpp;

class Host : public cSimpleModule {
  private:
    cMessage *sendEvent;
    double meanInterArrival;
    double packetDuration;

  protected:
    virtual void initialize() override {
        meanInterArrival = par("meanInterArrival").doubleValue();
        packetDuration   = par("packetDuration").doubleValue();
        sendEvent = new cMessage("sendEvent");

        // Pure ALOHA: transmit at a RANDOM time, NOT aligned to any slot
        scheduleAt(simTime() + exponential(meanInterArrival), sendEvent);
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg == sendEvent) {
            cMessage *pkt = new cMessage("packet");
            send(pkt, "out");

            // Next transmission: exponential random (Poisson arrivals)
            scheduleAt(simTime() + exponential(meanInterArrival), sendEvent);
        }
    }

    virtual void finish() override {
        cancelAndDelete(sendEvent);
    }
};

Define_Module(Host);
