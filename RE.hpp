#ifndef RE_HPP
#define RE_HPP

#include "AQM.hpp"

class RE
{
    InterruptIn portA;
    DigitalIn portB;
    AQM aqm;
    int pulse;
    char* str_pulse;
    int statusB;
    
    public:
    RE(PinName a, PinName b, PinName sda, PinName scl);
    AQM& get_aqm() { return aqm; }
    InterruptIn& get_portA() { return portA; }
    void re_a_up(void);
    void re_a_down(void);
    void is_correct();
};


RE::RE(PinName a, PinName b, PinName sda, PinName scl)
                     : portA(a), portB(b), aqm(sda, scl)
{
    pulse = 0;
    str_pulse = new char[4];
    statusB = -1;
    
    portA.mode(PullUp);
    portB.mode(PullUp);
    
}

void RE::is_correct() {
    if (pulse == 101) {
        pulse = 100;
    }
    if (pulse == -1) {
        pulse = 0;
    }
}

void RE::re_a_down() {
    statusB = portB.read();
}

void RE::re_a_up(){
    if (statusB == -1) {
        printf("abc\n");
        return;
    }
    if (statusB == portB.read()) {
        return;
    }
    if (portB.read()) {
        pulse--;
    } else {
        pulse++;
    }
    is_correct();
    aqm.write_num(str_pulse, pulse);
}

#endif // RE_HPP