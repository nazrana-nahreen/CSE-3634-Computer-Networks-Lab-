
#include <omnetpp.h>
#include <cmath>
using namespace omnetpp;

class Server : public cSimpleModule {
  private:
    int packetsReceived = 0;
    int collisions = 0;
    int totalAttempts = 0;

    double slotTime;
    simtime_t lastArrival = -1;

  protected:
    virtual void initialize() override {
        slotTime = par("slotTime").doubleValue();
    }

    virtual void handleMessage(cMessage *msg) override {
        totalAttempts++;

        if (lastArrival >= 0 && simTime() == lastArrival) {

            collisions++;
        } else {

            packetsReceived++;
            lastArrival = simTime();
        }

        delete msg;
    }

    virtual void finish() override {
        double simTimeSec = simTime().dbl();

        double totalSlots = simTimeSec / slotTime;

       double G = totalAttempts / totalSlots;
        //double G = 1;
        double S = G * exp(-G);

        recordScalar("Packets Received", packetsReceived);
        recordScalar("Collisions", collisions);
        recordScalar("Total Attempts", totalAttempts);
        recordScalar("Slots", totalSlots);
        recordScalar("Offered Load (G)", G);
        recordScalar("Theoretical Throughput (S)", S);

        std::cout << "\n";
        std::cout << "===== Slotted ALOHA Results =====\n";
        std::cout << "Packets Received: " << packetsReceived << "\n";
        std::cout << "Collisions: " << collisions << "\n";
        std::cout << "Total Attempts: " << totalAttempts << "\n";
        std::cout << "Total Slots: " << totalSlots << "\n";
        std::cout << "Offered Load (G): " << G << "\n";
        std::cout << "Throughput (S = G*e^-G): " << S << "\n";
        std::cout << "=====================================\n" << std::endl;
    }
};

Define_Module(Server);

