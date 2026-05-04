simple NAZRANA
{
    gates:
        input in;
        output out;
}
//
// Five instances (tower1, tower2, tower3, tower4, tower5) of NAZRANA connected both ways.
// They will pass messages to one another.
//
network five_nodeproblem
{
    @display("bgb=613,290");
    submodules:
        tower1: NAZRANA {
            @display("p=342,221");
        }
        tower2: NAZRANA {
            @display("p=180,221");
        }
        tower3: NAZRANA {
            @display("p=126,119");
        }
        tower4: NAZRANA {
            @display("p=257,34");
        }
        tower5: NAZRANA {

            @display("p=414,101");
        }
    connections:
        tower1.out --> {  delay = 100ms; } --> tower2.in;
        //        tower1.in <-- {  delay = 100ms; } <-- tower2.out;
        tower2.out --> {  delay = 100ms; } --> tower3.in;
        //        tower2.in <-- {  delay = 100ms; } <-- tower3.out;
        tower3.out --> {  delay = 100ms; } --> tower4.in;
        //        tower3.in <-- {  delay = 100ms; } <-- tower4.out;
        tower4.out --> {  delay = 100ms; } --> tower5.in;
        //        tower4.in <-- {  delay = 100ms; } <-- tower5.out;
        tower5.out --> {  delay = 100ms; } --> tower1.in;
//        tower5.in <-- {  delay = 100ms; } <-- tower1.out;

}
