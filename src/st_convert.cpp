#include "st_convert.h"

#define NUL 0 // Null.
#define BSP 1 // Boat speed in knots.
#define HDG 2 // Boat heading right of north in degrees.
#define AWS 3 // Apparent wind speed in knots.
#define AWA 4 // Apparent wind angle right of the bow in degrees.

st_convert::st_convert() {}

st_convert::kvp_from_sentence(sentence datagram, kvp* datum) {
/*
 * Convert a Seatalk sentence into the corresponding key/value pair.
 */
  switch (datagram[0]) {

    case 0x0120:
      datum->key = BSP;
      datum->value = (double(datagram[2]) * 256.0 + double(datagram[3])) / 10.0;
      break;
    case 0x019C:
      uint8_t two_MSBs_of_U;
      datum->key = HDG;
      if (datagram[1] & 0b11000000 == 0) two_MSBs_of_U = 0;
      else
        if ((datagram[1] & 0b11000000) == 0b11000000) two_MSBs_of_U = 2;
        else two_MSBs_of_U = 1; 
      datum->value =  double((datagram[1] & 0x30) >> 4) * 90 + double(datagram[2] & 0x3F) * 2.0 + double(two_MSBs_of_U);
      break;
    case 0x0111:
      datum->key = AWS;
      datum->value = double(datagram[2] & 0x7F) + double(datagram[3] / 10.0);
      break;
    case 0x0110:
      datum->key = AWA;
      datum->value = (double(datagram[2]) * 256.0 + double(datagram[3])) / 2.0;
      break;
    default: 
      datum->key = NUL;
      datum->value = 0;
  }
}

st_convert::sentence_from_kvp(kvp datum, sentence datagram) {
/*
 * Convert a key/value pair into the corresponding Seatalk sentence.
 */

  switch (datum.key) {

    case BSP:
      datagram[0] = 0x0120;
      datagram[1] = 0x0001;
      datagram[2] = uint16_t(10.0 * datum.value) >> 8;
      datagram[3] = uint16_t(10.0 * datum.value) & 0x00FF;
      datagram[4] = 0xFFFF;
      break;
    case HDG:
      datagram[0] = 0x019C;
      datagram[1] = ((uint8_t(uint16_t(datum.value) / 90) & 0x03) << 4) | (uint8_t(uint16_t(datum.value) & 0x0001) << 6) | 0x01;
      datagram[2] = (uint16_t(datum.value) % 90 >> 1) & 0x003F;
      datagram[3] = 0x0000;
      datagram[4] = 0xFFFF;
      break;
    case AWS:
      datagram[0] = 0x0111;
      datagram[1] = 0x0001;
      datagram[2] = uint16_t(datum.value) & 0x007F;
      datagram[3] = uint16_t(10.0 * datum.value) % 10;
      datagram[4] = 0xFFFF;
      break;
    case AWA:
      datagram[0] = 0x0110;
      datagram[1] = 0x0001;
      datagram[2] = uint16_t(2.0 * datum.value) >> 8;
      datagram[3] = uint16_t(2.0 * datum.value) & 0x00FF;
      datagram[4] = 0xFFFF;
      break;
    default: datagram[0] = 0xFFFF;
  }
  return datagram;
}
