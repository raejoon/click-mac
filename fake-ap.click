require(package "click-mac");

AddressInfo(ap_bssid 192.168.2.1/8 wlan0);

FromHost(fake, ap_bssid, ETHER ap_bssid)
-> Queue(10)
-> cuq :: ControlledUnqueue()
-> EtherToFake()
-> q :: Queue(10)
-> to_dev :: ToDevice(wlan0);

bs :: FakeBeaconSource(ADDR 10) 
-> EtherEncap(0x1111, ap_bssid, ff:ff:ff:ff:ff:ff)
-> q;

bs[1] -> [1]cuq;
cuq[1] -> bs;

TimedSource(INTERVAL 10s, DATA \<01>, LIMIT 2)
-> [1]cuq; 

FromDevice(wlan0, SNIFFER false)
-> FakeToEther()
-> ToHost(fake)
