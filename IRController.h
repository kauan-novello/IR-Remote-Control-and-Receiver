#ifndef IRCONTROLLER_H
#define IRCONTROLLER_H

#include <IRremote.h>

class IRController {
  private:
    IRrecv irrecv;
    decode_results results;

  public:
    IRController(int recvPin);
    void begin();
    void checkReceiver();
};

#endif
