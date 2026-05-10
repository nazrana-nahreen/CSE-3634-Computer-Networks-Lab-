// HopNetwork.ned
// Defines the network topology: 1 Sender, 10 Routers, 1 Receiver
// connected as a mesh (each router has 2-3 neighbours).

package hopcount;

// ─────────────────────────────────────────────────────────────
//  Module definitions
// ─────────────────────────────────────────────────────────────

simple Sender
{
    parameters:
        @display("i=device/laptop");
    gates:
        output out;
}

simple Receiver
{
    parameters:
        @display("i=device/server");
    gates:
        input in;
}

// A Router has a fixed number of in/out gate pairs.
// We use a generous maximum (6) and wire only what we need.
simple Router
{
    parameters:
        @display("i=abstract/router");
    gates:
        input  in[6];
        output out[6];
}

// ─────────────────────────────────────────────────────────────
//  Network
// ─────────────────────────────────────────────────────────────

network HopNetwork
{
    submodules:
        sender   : Sender   { @display("p=50,250");  }
        receiver : Receiver { @display("p=750,250"); }

        // 10 routers laid out in a mesh
        r[10] : Router;

    connections allowunconnected:

        // ── Sender → entry routers ──────────────────────────
        sender.out   --> r[0].in[0];

        // ── Layer 1  (r0) ────────────────────────────────────
        r[0].out[0]  --> r[1].in[0];
        r[0].out[1]  --> r[2].in[0];
        r[0].out[2]  --> r[3].in[0];

        // ── Layer 2  (r1, r2, r3) ───────────────────────────
        r[1].out[0]  --> r[4].in[0];
        r[1].out[1]  --> r[5].in[0];

        r[2].out[0]  --> r[4].in[1];
        r[2].out[1]  --> r[6].in[0];

        r[3].out[0]  --> r[5].in[1];
        r[3].out[1]  --> r[6].in[1];

        // ── Layer 3  (r4, r5, r6) ───────────────────────────
        r[4].out[0]  --> r[7].in[0];
        r[4].out[1]  --> r[8].in[0];

        r[5].out[0]  --> r[7].in[1];
        r[5].out[1]  --> r[9].in[0];

        r[6].out[0]  --> r[8].in[1];
        r[6].out[1]  --> r[9].in[1];

        // ── Layer 4  (r7, r8, r9) → Receiver ────────────────
        r[7].out[0]  --> r[9].in[2];   // cross-link keeps it a mesh
        r[8].out[0]  --> r[9].in[3];

        r[9].out[0]  --> receiver.in;
}
