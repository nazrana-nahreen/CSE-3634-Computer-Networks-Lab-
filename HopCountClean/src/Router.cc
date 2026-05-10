#include "Router.h"

Define_Module(Router);

void Router::initialize()
{
    totalForwarded = 0;
    totalDropped   = 0;

    // Register signals so the IDE's result recorder can pick them up
    hopCountSignal = registerSignal("hopCount");
    droppedSignal  = registerSignal("dropped");
}

void Router::handleMessage(cMessage *msg)
{
    MyMessage *pkt = check_and_cast<MyMessage *>(msg);

    // ── Step 1: count this hop ──────────────────────────────
    pkt->setHopCount(pkt->getHopCount() + 1);

    // ── Step 2: decrement TTL ───────────────────────────────
    pkt->setTtl(pkt->getTtl() - 1);

    EV << "[" << getFullName() << "] hopCount=" << pkt->getHopCount()
       << "  ttl=" << pkt->getTtl() << "\n";

    // ── Step 3: TTL check ───────────────────────────────────
    if (pkt->getTtl() <= 0) {
        EV << "[" << getFullName() << "] TTL exhausted – dropping packet.\n";
        emit(droppedSignal, 1);
        totalDropped++;
        delete pkt;
        return;
    }

    // ── Step 4: collect connected output gates ──────────────
    std::vector<int> connectedGates;
    int numOut = gateSize("out");
    for (int i = 0; i < numOut; i++) {
        cGate *g = gate("out", i);
        if (g->isConnected())
            connectedGates.push_back(i);
    }

    if (connectedGates.empty()) {
        // Dead end – should not happen in a well-wired network
        EV << "[" << getFullName() << "] No connected output gates – dropping.\n";
        emit(droppedSignal, 1);
        totalDropped++;
        delete pkt;
        return;
    }

    // ── Step 5: pick a random gate and forward ──────────────
    // intrand(N) uses the module's RNG (seed controlled by omnetpp.ini)
    int chosen = connectedGates[intrand(connectedGates.size())];

    emit(hopCountSignal, (long)pkt->getHopCount());
    totalForwarded++;

    send(pkt, "out", chosen);
}
