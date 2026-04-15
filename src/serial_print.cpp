#include "../include/killerqueen.hpp"

/*
[0]      ID? (0x07)
[1]      Stick gauche X  (0x80 = centre)
[2]      Stick gauche Y  (0x80 = centre)
[3]      Stick droit X   (0x80 = centre)
[4]      Stick droit Y   (0x80 = centre)
[5]      D-pad (0x0F = neutre, 0x06 = gauche, 0x02 = droite, 0x04 = bas)
[6]      Boutons : A(0x01) B(0x02) X(0x08) Y(0x10) LB(0x40) RB(0x80)
[7]      Flags : LT(0x01) RT(0x02) Stick gauche pressed(0x20) Stick droit pressed(0x40)
[8]      RT analog (0x00 –> 0xFF)
[9]      LT analog (0x00 –> 0xFF)
[10]     Inconnu (0x00)
*/

void print_hex_data(uint8_t *data, uint16_t data_len)
{
    for (uint16_t len = 0; len < data_len; len++)
        printf("%02X ", data[len]);
    printf("\n");
}

void print_dpad_datas(uint8_t data)
{
    switch (data)
    {
        case DPAD_NEUTRAL:
            printf("dpad_neutral\n");
        break;

        case DPAD_UP:
            printf("dpad_up\n");
        break;

        case DPAD_DOWN:
            printf("dpad_down\n");
        break;

        case DPAD_LEFT:
            printf("dpad_left\n");
        break;

        case DPAD_RIGHT:
            printf("dpad_right\n");
        break;

        case DPAD_UP_LEFT:
            printf("dpad_up_left\n");
        break;

        case DPAD_UP_RIGHT:
            printf("dpad_up_right\n");
        break;

        case DPAD_DOWN_LEFT:
            printf("dpad_down_left\n");
        break;

        case DPAD_DOWN_RIGHT:
            printf("dpad_down_right\n");
        break;
    }
}
