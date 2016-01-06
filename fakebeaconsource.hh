#ifndef FAKEBEACONSOURCE_HH
#define FAKEBEACONSOURCE_HH
#include <click/element.hh>
#include <click/timer.hh>
CLICK_DECLS

class FakeBeaconSource : public Element 
{ 
  public:
    FakeBeaconSource();
    ~FakeBeaconSource();

    const char *class_name() const { return "FakeBeaconSource"; }
    const char *port_count() const { return "0/1"; }
    const char *processing() const { return "h"; }
    int configure(Vector<String> &conf, ErrorHandler* errh);
    int initialize(ErrorHandler *);
    void run_timer(Timer *timer);
  
  private:
    Timer _timer;
    uint16_t _srcaddr;
    uint16_t _interval;

    Packet* _beacon;
};

CLICK_ENDDECLS
#endif
