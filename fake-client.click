require(package "click-mac");

AddressInfo(client_addr 192.168.2.2/8 wlan0);

FromHost(fake, client_addr, ETHER client_addr)
-> q :: Queue(10)
-> to_dev :: ToDevice(wlan0);

FromDevice(wlan0, SNIFFER false)
-> SetTimestamp()
-> BeaconListener(ADDR 10)
-> Print(TIMESTAMP true)
-> ToHost(fake)
