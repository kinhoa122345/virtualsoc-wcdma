//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <libsimsoc/network/socket-inet4.hpp>
#include <libsimsoc/network/poll.hpp>

#include <libsimsoc/network/ethernet/ether-transport.hpp>
#include <libsimsoc/network/ethernet/ether-address.hpp>
#include <libsimsoc/network/ethernet/ether-buffer.hpp>

#include <cassert>
#include <cstring>
#include <set>
#include <memory>

// --------------------------------------------------------------------
namespace simsoc {
#define ETHER_MCAST_PORT 8805u
#define ETHER_LENGTH     1522u

  void sns_start(const char *injdevice) {
    MCast_EtherTransport           mcast;
    std::auto_ptr<IEtherTransport> inj;

    mcast.setnonblocking(true);

    inj.reset(IEtherTransport::create(injdevice));
    inj->setnonblocking(true);

    EtherBuffer buffer(ETHER_LENGTH);
    std::set<EtherAddress> locals;

    // Start bridging
    Poll       poll;
    PollResult pollr;

    poll.record(mcast.handle(), Poll::D_IN);
    poll.record(inj->handle(), Poll::D_IN);

    while (true) {
      poll.wait(pollr);

      if (pollr.readable(mcast.handle()) && mcast.recv(buffer)) {
	assert(buffer.length() >= 12);

	const EtherAddress destination(buffer.at(0));
	const EtherAddress source     (buffer.at(6));

	if (source.is_unicast())
	  locals.insert(source);

	const bool bridge
	  =  destination.is_broadcast()
	  || (destination.is_unicast()
	      && locals.find(destination) == locals.end());

	if (bridge)
	  (void) inj->send(buffer);
      }

      if (pollr.readable(inj->handle()) && inj->recv(buffer)) {
	assert(buffer.length() >= 12);

	const EtherAddress destination(buffer.at(0));

	const bool bridge
	  =  destination.is_broadcast()
	  || (destination.is_unicast()
	      && locals.find(destination) != locals.end());

          if (bridge)
            (void) mcast.send(buffer);
      }
    }
  }
}

// --------------------------------------------------------------------
int main(int argc, char *argv[]) {
  if ((argc-1) != 1) {
    std::clog << "Usage: " << argv[0] << " [INJ-DEVICE]" << std::endl;
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "mcast") == 0) {
    std::clog << "Cannot use the [mcast] transport" << std::endl;
    return EXIT_FAILURE;
  }

  simsoc::sns_start(argv[1]);

  return EXIT_SUCCESS;
}
