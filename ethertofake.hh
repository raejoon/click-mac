#ifndef ETHERTOFAKE_HH
#define ETHERTOFAKE_HH
#include <click/element.hh>

CLICK_DECLS

class EtherToFake : public Element
{
  public:
    EtherToFake();
    ~EtherToFake();
    
    const char *class_name() const { return "EtherToFake"; }
    const char *port_count() const { return "1/1"; }
    const char *processing() const { return "h/h"; }
    void push(int, Packet *p);
};

CLICK_ENDDECLS
#endif
