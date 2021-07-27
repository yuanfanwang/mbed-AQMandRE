#ifndef AQM_HPP
#define AQM_HPP


#include <string>


using namespace std;

class AQM
{
    I2C i2c;
    
    public:
    AQM(PinName sda, PinName scl);
    static const uint8_t lcd_slv_adr = 0x7C;
    
    void write_cmd(const uint8_t& data, const uint8_t& wu = 30);
    void write_data(const uint8_t& data, const uint8_t& wu = 30);
    void clear_disp();
    void initLCD();
    void write_line_xy(const uint8_t x, const uint8_t y, const string& s);
    void clear_line_after_xy(const uint8_t x, const uint8_t y, const uint8_t x_end);
    void write_num(char* s_num, int i);
};

AQM::AQM(PinName sda, PinName scl) : i2c(sda, scl) {}


void AQM::write_cmd(const uint8_t& data, const uint8_t& wu) {
    AQM::i2c.start();
    i2c.write(lcd_slv_adr);
    i2c.write(0x00);
    i2c.write(data);
    i2c.stop();
    wait_us(wu);
}

void AQM::write_data(const uint8_t& data, const uint8_t& wu) {
    i2c.start();
    i2c.write(lcd_slv_adr);
    i2c.write(0x40);
    i2c.write(data);
    i2c.stop();
    wait_us(wu);
}

void AQM::clear_disp() {
    i2c.start();
    i2c.write(lcd_slv_adr);
    i2c.write(0x00);
    i2c.write(0x01);
    i2c.stop();
    wait_us(30);
}

void AQM::initLCD() {
    write_cmd(0x38);
    write_cmd(0x39);
    write_cmd(0x14);
    write_cmd(0x73);
    write_cmd(0x56);
    write_cmd(0x6C);
    wait_ms(200);
    write_cmd(0x38);
    write_cmd(0x01);
    write_cmd(0x0C);
}

void AQM::write_line_xy(const uint8_t x, const uint8_t y, const string& s) {
    int address = 0x80 + 0x40 * y + x;
    for(int i = 0; i < s.size(); i++) {
        write_cmd(address + i);
        write_data(s[i]);
    }
}

void AQM::clear_line_after_xy(const uint8_t x, const uint8_t y, const uint8_t x_end) {
    int address = 0x80 + 0x40 * y + x;
    for(int i = 0; i < x_end; i++) {
        write_cmd(address + i);
        write_data(' ');
    }
}

void AQM::write_num(char* s_num, int i) {
    clear_line_after_xy(2, 1, 3);
    sprintf(s_num, "%d", i);
    write_line_xy(2, 1, s_num);
}

#endif // AQM_HPP
