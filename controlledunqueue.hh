#ifndef CLICK_CONTROLLEDUNQUEUE_HH 
#define CLICK_CONTROLEEDUNQUEUE_HH
#include <click/element.hh>
#include <click/task.hh>
#include <click/notifier.hh>
CLICK_DECLS

/*
=c

ControlledUnqueue([I<keywords> ACTIVE, LIMIT, BURST])

=s shaping

pull-to-push converter

=d

Pulls packets whenever they are available, then pushes them out
its single output. Pulls a maximum of BURST packets every time
it is scheduled. Default BURST is 1. If BURST
is less than 0, pull until nothing comes back.

Keyword arguments are:

=over 4

=item ACTIVE

If false, does nothing (doesn't pull packets). One possible use
is to set ACTIVE to false in the configuration, and later
change it to true with a handler from DriverManager element.
The default value is true.

=item LIMIT

If positive, then at most LIMIT packets are pulled.  The default is -1, which
means there is no limit.

=back

=h count read-only

Returns the count of packets that have passed through ControlledUnqueue.

=h reset write-only

Resets the count to 0.  This may reschedule the ControlledUnqueue to pull LIMIT more
packets.

=h active read/write

Same as the ACTIVE keyword.

=h limit read/write

Same as the LIMIT keyword.

=h burst read/write

Same as the BURST keyword.

=a RatedControlledUnqueue, BandwidthRatedUnqueue
*/

class ControlledUnqueue : public Element { public:

    ControlledUnqueue() CLICK_COLD;

    const char *class_name() const		{ return "ControlledUnqueue"; }
    const char *port_count() const		{ return "2/2"; }
    const char *processing() const		{ return "lh/hh"; }

    int configure(Vector<String> &, ErrorHandler *) CLICK_COLD;
    int initialize(ErrorHandler *) CLICK_COLD;
    void add_handlers() CLICK_COLD;

    bool run_task(Task *);

    void push(int, Packet *p);

  private:

    bool _isAwake;
    bool _active;
    int32_t _burst;
    int32_t _limit;
    uint32_t _count;
    Task _task;
    NotifierSignal _signal;

    enum {
	h_active, h_reset, h_burst, h_limit
    };
    static int write_param(const String &, Element *, void *, ErrorHandler *) CLICK_COLD;

};

CLICK_ENDDECLS
#endif
