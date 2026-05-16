#include "Receiver.h"

Define_Module(Receiver);

void Receiver::initialize()
{
    finalHopCountSignal = registerSignal("finalHopCount");
    droppedPacketsSignal = registerSignal("droppedPackets");
    packetsReceived = 0;
    totalHops       = 0;
}

void Receiver::handleMessage(cMessage *msg)
{
    MyMessage *pkt = check_and_cast<MyMessage *>(msg);

    int hops = pkt->getHopCount();
    int ttl  = pkt->getTtl();
    int pktNum = pkt->getPacketNumber();

    EV << "[Receiver] Packet #" << pktNum << " arrived! hopCount=" << hops
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
        EV << "\n";
        EV << "==================================================\n";
        EV << "=== RECEIVER SUMMARY ===\n";
        EV << "==================================================\n";
        EV << "Packets received : " << packetsReceived << "\n";
        EV << "Total hops       : " << totalHops << "\n";
        EV << "Average hop count: " << avg << "\n";
        EV << "==================================================\n";
        EV << "\n";

        // Also record as scalars so they appear in the Analysis tool
        recordScalar("packetsReceived", packetsReceived);
        recordScalar("averageHopCount", avg);
        recordScalar("totalHops", (long)totalHops);
    } else {
        EV << "[Receiver] No packets arrived (all dropped?).\n";
        recordScalar("packetsReceived", 0);
        recordScalar("averageHopCount", 0);
    }
}
