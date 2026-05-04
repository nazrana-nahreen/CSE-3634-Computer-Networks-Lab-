package PureAloha;

simple Host {
    parameters:
        double meanInterArrival;
        double packetDuration;
    gates:
        output out;
}