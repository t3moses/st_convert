
#ifndef SEATALK_CONVERT
  #define SEATALK_CONVERT

  #if (ARDUINO >=100)
    #include "Arduino.h"
  #else
    #include "WProgram.h"
  #endif

  #define MAX_SENTENCE_SIZE 12

  typedef uint16_t sentence[MAX_SENTENCE_SIZE];

  struct kvp { // Key/value pair.
    uint8_t key;
    double value;
  };

  class st_convert {
    
    public:

      st_convert();
      kvp_from_sentence(sentence datagram, kvp* datum);
      sentence_from_kvp(kvp datum, sentence datagram);

  };
#endif
