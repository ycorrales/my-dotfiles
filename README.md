How Configure a fwknop server
=============================

## Configuration

 * config files:  
 /etc/fwknop/  
 └─ access.conf  
 └─ fwknopd.conf

### fwknop.conf:
__change the TCP port__
```
  #PCAP_FILTER             udp port 62201;
  PCAP_FILTER             udp port 30722;
```
### access.conf:
```
  # REQUIRE_SOURCE_ADDRESS   <Y/N>
  REQUIRE_SOURCE_ADDRESS     N

  SOURCE                     ANY
  KEY_BASE64                 0gkz0R2x6iq4HixFqG1NyQq8HH5bRPqD8WBDcwnRIp0=
  HMAC_KEY_BASE64            xWo7FNLLq3INxE5JFC8rdCbKZ6n3A92KElhF/cEQFhqHh3oeJyYs1I+7/SJOEGYG1+fdb2LpBAYLgh1buRjVGA==
  USE_HMAC                   Y
```

## Load fwknop daemon
```bash
# systemctl status (start, restart, stop ...) fwknopd.service
● fwknopd.service - The FireWall KNock OPerator (fwknop)
   Loaded: loaded (/usr/lib/systemd/system/fwknopd.service; enabled; vendor preset: disabled)
   Active: active (running) since Thu 2020-03-26 16:28:25 MDT; 4h 53min ago
     Docs: man:fwknop(8)
 Main PID: 9831 (fwknopd)
    Tasks: 1
   CGroup: /system.slice/fwknopd.service
           └─9831 /usr/sbin/fwknopd
```

## SPA firewall setup

ssh ports: 22 (Local) and 37023 (World, through router port forwarding)
@Home Router, do port forwarding to the server (e.g. 192.168.1.14, fixed IP):
```
UDP 30722
TCP 37023
```

## Access
one can ssh/login to this FELIX-2 server through private/public keys only;.
ssh maps@darkphoton.ddns.net or maps@192.168.1.14 on local network


### Disabled password login in

`/etc/ssh/sshd_config`


## @End users

1. install fwknop app
1. get a copy of the .fwknoprc.
1. create add function in bashrc

```bash
ming-fwknop () {
	local cmd="$@"
	fwknop -s -n ming_felix || return 1
	sleep 2
	$cmd
}
```

## Notes
Sometime the felix server's system time gets drifted off from the local time zone (/etc/localtime), and causes problems for the fwknopd remote login:

Solution:
* reset the system time by hand:
```bash
$ timedatectl set-time '16:37:50'
```
