#include "Receiver.h"

Define_Module(Receiver);

void Receiver::initialize()
{
    finalHopCountSignal = registerSignal("finalHopCount");
    packetsReceived = 0;
    totalHops       = 0;
}

void Receiver::handleMessage(cMessage *msg)
{
    MyMessage *pkt = check_and_cast<MyMessage *>(msg);

    int hops = pkt->getHopCount();
    int ttl  = pkt->getTtl();

    EV << "[Receiver] Packet arrived! hopCount=" << hops
       << "  remaining ttl=" << ttl << "\n";

    // Record for OMNeT++ result files (.vec / .sca)
    emit(finalHopCountSignal, (long)hops);

    packetsReceived++;
    totalHops += hops;

    delete pkt;
}

void Receiver::finish()
{
    if (packetsReceived > 0) {
        double avg = (double)totalHops / packetsReceived;
        EV << "=== RECEIVER SUMMARY ===\n";
        EV << "Packets received : " << packetsReceived << "\n";
        EV << "Total hops       : " << totalHops << "\n";
        EV << "Average hop count: " << avg << "\n";

        // Also record as a scalar so it appears in the Analysis tool
        recordScalar("packetsReceived", packetsReceived);
        recordScalar("averageHopCount", avg);
    } else {
        EV << "[Receiver] No packets arrived (all dropped?).\n";
    }
}
