#include <omnetpp.h>
#include <cmath>
using namespace omnetpp;

class Host : public cSimpleModule {
  private:
    cMessage *sendEvent;
    double slotTime;

  protected:
    virtual void initialize() override {
        slotTime = par("slotTime").doubleValue();
        sendEvent = new cMessage("sendEvent");

        scheduleAt(ceil(simTime().dbl() / slotTime) * slotTime, sendEvent);
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg == sendEvent) {

            cMessage *pkt = new cMessage("packet");
            send(pkt, "out");


            int k = intuniform(4, 6);
            scheduleAt(simTime() + k * slotTime, sendEvent);
        }
    }

    virtual void finish() override {
        cancelAndDelete(sendEvent);
    }
};

Define_Module(Host);
