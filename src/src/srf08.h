 #ifndef _SRF08_H
 #define _SRF08_H       1

#define CMD_INCH 0x50
#define CMD_CM 0x51
#define CMD_MS 0x52

#define REG_CMD 0x00
#define REG_LIGH 0x01

#define SRF08_ADDRESS 0x70

void set_measurment(byte unit);
int get_distance();

#endif