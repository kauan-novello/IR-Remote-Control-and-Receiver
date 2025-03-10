#ifndef IRBUTTON_H
#define IRBUTTON_H

class IRButton {
  private:
    int pin;
    long irCode;
    bool lastState;

  public:
    IRButton(int pin, long irCode);
    void begin();
    void update();
};

#endif
