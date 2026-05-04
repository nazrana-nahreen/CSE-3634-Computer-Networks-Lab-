/*
 * five_nodeproblem.cc
 *
 *  Created on: May 4, 2026
 *      Author: User
 */

#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class NAZRANA : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(NAZRANA);

void NAZRANA::initialize()
{
    if (strcmp("tower1", getName()) == 0) {
        cMessage *msg = new cMessage("kosto hocche");
        send(msg, "out");
    }
}

void NAZRANA::handleMessage(cMessage *msg)
{
    send(msg, "out");
}


