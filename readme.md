This Seatalk library converts between parameters of a c-language struct and the corresponding Seatalk sentences.  The struct is defined as:

struct kvp { // Key/value pair.
  uint8_t key;
  double value;
};

key values are 0 .. 4.  The corresponding values are: nul, boat speed, compass heading, apparent wind speed and apparent wind angle.

Details of the Seatalk protocol are due to Thomas Knauf.  See:

     http://www.thomasknauf.de/seatalk.htm

The library exposes two methods:

kvp_from_sentence(sentence datagram, kvp* datum) and
sentence_from_kvp(kvp datum, sentence datagram);

The library has only been tested on an Arduino Uno R3 with a 16 MHz system clock.
