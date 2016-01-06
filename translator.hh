#ifndef TRANSLATOR_HH
#define TRANSLATOR_HH
#include <click/element.hh>

CLICK_DECLS

class Translator : public Element
{
  public:
    Translator();
    ~Translator();
    
    const char *class_name() const { return "Translator"; }
    const char *port_count() const { return "1/1"; }
    const char *processing() const { return "h/h"; }
    void push(int, Packet *p);
};

CLICK_ENDDECLS
#endif
