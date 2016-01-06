#ifndef FAKEBEACONSOURCE_HH
#define FAKEBEACONSOURCE_HH
#include <click/element.hh>
CLICK_DECLS

class FakeBeaconSource : public Element 
{ 
  public:
    FakeBeaconSource();
    ~FakeBeaconSource();

    const char *class_name() const { return "FakeBeaconSource"; }
    const char *port_count() const { return "0/1"; }
    const char *processing() const { return "PUSH"; }
};

CLICK_ENDDECLS
#endif
