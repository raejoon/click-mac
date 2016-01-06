require(package "click-mac");

AddressInfo(ap_bssid 192.168.2.1/8 wlan0);

FromHost(fake, ap_bssid, ETHER ap_bssid)
-> q :: Queue(10)
-> to_dev :: ToDevice(wlan0);

FakeBeaconSource(ADDR 10) 
-> Print()
-> EtherEncap(0x1111, ap_bssid, ff:ff:ff:ff:ff:ff)
-> Print()
-> q;

FromDevice(wlan0, SNIFFER false)
-> ToHost(fake)
