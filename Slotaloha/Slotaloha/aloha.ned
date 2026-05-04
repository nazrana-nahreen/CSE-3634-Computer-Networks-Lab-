package Slotaloha;

network AlohaNetwork {
    submodules:
        server: Server;
        host[5]: Host;
    connections:
        for i=0..4 {
            host[i].out --> server.in[i];
        }
}