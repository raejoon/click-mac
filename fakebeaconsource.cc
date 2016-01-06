#include <click/config.h>
#include <click/args.hh>
#include "fakebeaconsource.hh"
CLICK_DECLS

static uint16_t broadcastaddr = 99;
FakeBeaconSource::FakeBeaconSource() 
  : _timer(this)
{
  _seqnum = 0;
  _exist = false;
}

FakeBeaconSource::~FakeBeaconSource()
{
  _beacon -> kill();
}

int FakeBeaconSource::configure(Vector<String> &conf, ErrorHandler* errh)
{
  if (Args(conf, this, errh)
      .read_mp("ADDR", _srcaddr)
      .read_or_set("INTERVAL", _interval, 100)
      .complete() < 0)
      return -1;

  size_t length = 5*sizeof(uint16_t);
  char payload[length];

  memcpy(payload, &_srcaddr, sizeof(uint16_t));
  memcpy(payload + sizeof(uint16_t), &broadcastaddr, sizeof(uint16_t));
  memcpy(payload + 2*sizeof(uint16_t), &_seqnum, sizeof(uint16_t));
  memcpy(payload + 3*sizeof(uint16_t), &_interval, sizeof(uint16_t));

  uint16_t tim = (_exist)? 1 : 0;
  memcpy(payload + 4*sizeof(uint16_t), &tim, sizeof(uint16_t));

  _beacon = Packet::make(payload, length);
  return 0;
}

int FakeBeaconSource::initialize(ErrorHandler *) {
  _timer.initialize(this);
  _timer.schedule_after_msec(_interval);
  return 0;
}

void FakeBeaconSource::push(int, Packet *p) {
  unsigned char signal = *(p->data());
  p->kill();
  
  if (signal == 1) _exist = true;
  else if (signal == 0) _exist = false;
  _check = true;
}

void FakeBeaconSource::check_queue() {
  unsigned char data = 3;
  Packet *p = Packet::make(&data, sizeof(unsigned char));
  output(1).push(p);
}

void FakeBeaconSource::run_timer(Timer *timer) {
  assert(timer == &_timer);

  _check = false;
  check_queue();
  while (!_check) int i = 1;
  
  WritablePacket* p = (_beacon->clone()) -> uniqueify();
  memcpy(p->data() + 2*sizeof(uint16_t), &_seqnum, sizeof(uint16_t));

  uint16_t tim = (_exist)? 1 : 0;
  memcpy(p->data() + 4*sizeof(uint16_t), &tim, sizeof(uint16_t)); 
  _seqnum++;

  output(0).push(p);
  _timer.reschedule_after_msec(_interval);
}

CLICK_ENDDECLS
EXPORT_ELEMENT(FakeBeaconSource)
