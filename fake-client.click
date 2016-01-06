require(package "click-mac");

AddressInfo(client_addr 192.168.2.2/8 wlan0);

FromHost(fake, client_addr, ETHER client_addr)
-> EtherToFake()
-> q :: Queue(10)
-> to_dev :: ToDevice(wlan0);

FromDevice(wlan0, SNIFFER false)
-> cl::Classifier(12/1111, -)
-> Strip(14)
-> SetTimestamp()
-> Print(LABEL "pre", TIMESTAMP true)
-> BeaconListener(ADDR 10)
-> Print(LABEL "post", TIMESTAMP true)
-> Discard;

cl[1]
-> FakeToEther()
-> ToHost(fake)


