#include <click/config.h>
#include "faketoether.hh"
CLICK_DECLS

FakeToEther::FakeToEther() {
}

FakeToEther::~FakeToEther() {
}

void FakeToEther::push(int, Packet *p) {
  WritablePacket *q = p->uniqueify();
  memcpy(q->data() + 2*6, q->end_data() - sizeof(uint16_t), sizeof(uint16_t));
  q->take(sizeof(uint16_t));

  output(0).push(q);
}

CLICK_ENDDECLS
EXPORT_ELEMENT(FakeToEther)
