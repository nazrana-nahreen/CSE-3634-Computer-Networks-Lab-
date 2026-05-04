#include <omnetpp.h>
#include <cmath>
using namespace omnetpp;

class Server : public cSimpleModule {
  private:
    int packetsReceived = 0;
    int collisions      = 0;
    int totalAttempts   = 0;

    double packetDuration;

    simtime_t lastStart = -1;
    bool lastCollided   = false;

  protected:
    virtual void initialize() override {
        packetDuration = par("packetDuration").doubleValue();
    }

    virtual void handleMessage(cMessage *msg) override {
        totalAttempts++;

        simtime_t now = simTime();

        // Pure ALOHA collision rule:
        // Packets collide if their transmission windows OVERLAP
        // Packet A: [lastStart, lastStart + packetDuration)
        // Packet B: [now,       now + packetDuration)
        // Overlap if: now < lastStart + packetDuration

        if (lastStart >= 0 && now < lastStart + packetDuration) {
            // Current packet collides
            collisions++;

            // If previous packet was already counted as received, fix it
            if (!lastCollided) {
                packetsReceived--;
                collisions++;
                lastCollided = true;
            }
        } else {
            // No overlap — successful
            packetsReceived++;
            lastCollided = false;
        }

        lastStart = now;
        delete msg;
    }

    virtual void finish() override {
        double simTimeSec = simTime().dbl();
        double totalSlots = simTimeSec / packetDuration;

        double G = (double)totalAttempts / totalSlots;

        // Pure ALOHA: vulnerable period = 2 * packetDuration
        // So S = G * e^(-2G)   (vs Slotted: S = G * e^(-G))
        double S = G * exp(-2.0 * G);

        recordScalar("Packets Received", packetsReceived);
        recordScalar("Collisions",       collisions);
        recordScalar("Total Attempts",   totalAttempts);
        recordScalar("Slots",            totalSlots);
        recordScalar("Offered Load (G)", G);
        recordScalar("Theoretical Throughput (S)", S);

        std::cout << "\n";
        std::cout << "===== Pure ALOHA Results =====\n";
        std::cout << "Packets Received: " << packetsReceived  << "\n";
        std::cout << "Collisions:       " << collisions       << "\n";
        std::cout << "Total Attempts:   " << totalAttempts    << "\n";
        std::cout << "Total Slots:      " << totalSlots       << "\n";
        std::cout << "Offered Load (G): " << G                << "\n";
        std::cout << "Throughput (S = G*e^-2G): " << S        << "\n";
        std::cout << "==============================\n" << std::endl;
    }
};

Define_Module(Server);
