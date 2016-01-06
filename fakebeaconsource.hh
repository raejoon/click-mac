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
    const char *port_count() const { return "1/2"; }
    const char *processing() const { return "h"; }
    int configure(Vector<String> &conf, ErrorHandler* errh);
    int initialize(ErrorHandler *);
    void push(int, Packet *p);
    void run_timer(Timer *timer);
  
  private:
    void check_queue();

    Timer _timer;
    uint16_t _srcaddr;
    uint16_t _interval;
    uint16_t _seqnum;
    bool     _check;
    bool     _exist;

    Packet* _beacon;
};

CLICK_ENDDECLS
#endif
