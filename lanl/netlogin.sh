#!/bin/bash
wget https://netlogin.lanl.gov/dana-na/auth/login.cgi --post-data='tz_offset=-420&username=329869&password=tE0rr)pains&realm=Visitors&btnSubmit=Sign+In' -O -| grep Welcome
