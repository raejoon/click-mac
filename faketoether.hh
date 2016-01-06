#ifndef FAKETOETHER_HH
#define FAKETOETHER_HH
#include <click/element.hh>
CLICK_DECLS
class FakeToEther : public Element
{
  public:
    FakeToEther();
    ~FakeToEther();

    const char *class_name() const { return "FakeToEther"; }
    const char *port_count() const { return "1/1"; }
    const char *processing() const { return "h/h"; }
    void push(int, Packet *p);
};
CLICK_ENDDECLS
#endif
