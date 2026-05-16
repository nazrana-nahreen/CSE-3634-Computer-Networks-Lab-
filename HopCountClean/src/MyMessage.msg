// MyMessage.msg
// OMNeT++ 6.x message definition - no package declaration needed here.
// The IDE auto-runs opp_msgtool to generate MyMessage_m.h and MyMessage_m.cc.

message MyMessage
{
    int hopCount = 0;       // Incremented by each router that handles the packet
    int ttl = 15;           // Time To Live: packet is dropped when this reaches 0
    int packetNumber = 0;   // Packet identifier (1-10)
}
