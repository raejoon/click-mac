#include <click/config.h>
#include "translator.hh"
CLICK_DECLS

Translator::Translator() {
}

Translator::~Translator() {
}

void Translator::push(int, Packet *p) {
  WritablePacket *q = p->uniqueify();

  WritablePacket *r = q->put(sizeof(uint16_t));
  memcpy(r->end_data() - sizeof(uint16_t), q->data() + 2*6, sizeof(uint16_t));

  uint16_t newtype = 0x1111;
  memcpy(r->data() + 2*6, &newtype, sizeof(uint16_t));

  output(0).push(r);
}

CLICK_ENDDECLS
EXPORT_ELEMENT(Translator)
