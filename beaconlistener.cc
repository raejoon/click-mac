#include <click/config.h>
#include <click/args.hh>
#include "beaconlistener.hh"
CLICK_DECLS

BeaconListener::BeaconListener() : _timer(this) {
  _sync = false;
  _interval = 100;
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

int BeaconListener::initialize(ErrorHandler *) {
  _timer.initialize(this);
  return 0;
}

void BeaconListener::push(int, Packet *p) {
  Timestamp now = Timestamp::now();
  uint16_t srcaddr = *((uint16_t*)p->data());
  
  if (!_sync) {
    if (srcaddr == _apaddr) {
      //click_chatter("%{timestamp}: associated with %d", &now, srcaddr);
      _timer.schedule_after_msec(_interval - 5);
      _sync = true;
      
      output(0).push(p);
      return;
    }
  } else {
    if (srcaddr == _apaddr) {
      if (now.doubleval() - (_tbft - 0.1) <= 0.01) {
        //click_chatter("%{timestamp}: associated with %d", &now, srcaddr);
        output(0).push(p);
        return;
      }
    }
  }

  p->kill();
}

void BeaconListener::run_timer(Timer *timer) {
  assert(timer == &_timer);
  _timer.reschedule_after_msec(_interval);
  _tbft = _timer.expiry().doubleval();
}

CLICK_ENDDECLS
EXPORT_ELEMENT(BeaconListener)
