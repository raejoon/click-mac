#include <click/config.h>
#include <click/args.hh>
#include "beaconlistener.hh"
CLICK_DECLS

BeaconListener::BeaconListener() {
  _sync = false;
}

BeaconListener::~BeaconListener() {
}

int BeaconListener::configure(Vector<String> &conf, ErrorHandler* errh) {
  if (Args(conf, this, errh)
      .read_mp("ADDR", _apaddr)
      .complete() < 0)
    return -1;

  return 0;
}

void BeaconListener::push(int, Packet *p) {
  Timestamp now = Timestamp::now();
  uint16_t srcaddr = *((uint16_t*)p->data());
  
  if (!_sync) {
    if (srcaddr == _apaddr) {
      click_chatter("%{timestamp}: associated with %d", &now, srcaddr);
      _sync = true;
    }
  } 
  else {
    if (srcaddr == _apaddr) {
      click_chatter("%{timestamp}: associated with %d", &now, srcaddr);
    }
  }

  output(0).push(p);
}

CLICK_ENDDECLS
EXPORT_ELEMENT(BeaconListener)
