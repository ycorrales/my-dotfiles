#!/bin/bash
wget https://netlogin.lanl.gov/dana-na/auth/login.cgi
--post-data='tz_offset=-420&username=329869&password=age:sC0orch&realm=Visitors&btnSubmit=Sign+In' -O -| grep Welcome
