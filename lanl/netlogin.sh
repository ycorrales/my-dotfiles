#!/bin/bash
#Ming's passwd
#passwd='l1.saKalocks'
passwd='nOde3s@rips'
wget https://netlogin.lanl.gov/dana-na/auth/login.cgi --post-data='tz_offset=-420&username=329869&password=${passwd}&realm=Visitors&btnSubmit=Sign+In' -O -| grep Welcome
