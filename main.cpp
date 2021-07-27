#include "mbed.h"
#include "RE.hpp"


RE re(A0, A1, D4, D5);

int main() {
    // aqm ready
    AQM& aqm = re.get_aqm();
    aqm.initLCD();
    aqm.clear_disp();
    aqm.write_line_xy(0, 0, "Hello STM32");
    aqm.write_line_xy(0, 1, "N=0");
    // re re ready
    InterruptIn& re_port_a = re.get_portA();
    re_port_a.rise(&re, &RE::re_a_up);
    re_port_a.fall(&re, &RE::re_a_down);
}
