#ifndef BEACONLISTENER_HH
#define BEACONLISTENER_HH
#include <click/element.hh>
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
    void push(int, Packet *p);
  
  private:
    uint16_t _interval;
    uint16_t _apaddr;
    bool     _sync;
};

CLICK_ENDDECLS
#endif
