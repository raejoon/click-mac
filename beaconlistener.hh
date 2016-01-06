#ifndef BEACONLISTENER_HH
#define BEACONLISTENER_HH
#include <click/element.hh>
#include <click/timer.hh>
CLICK_DECLS

class BeaconListener : public Element
{
  public:
    BeaconListener();
    ~BeaconListener();

    const char *class_name() const { return "BeaconListener"; }
    const char *port_count() const { return "1/1"; }
    const char *processing() const { return "h"; }
    int configure(Vector<String> &conf, ErrorHandler* errh);
    int initialize(ErrorHandler *);
    void push(int, Packet *p);
    void run_timer(Timer *timer);
  
  private:
    Timer    _timer;
    double   _tbft;
    uint16_t _interval;
    uint16_t _apaddr;
    bool     _sync;
};

CLICK_ENDDECLS
#endif
