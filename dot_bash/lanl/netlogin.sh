#!/bin/bash

{
  #Ming's passwd
  USER='167255'
  PASS='l1.saKalocks'
#  USER=329869
#  PASS='nOde3s@rips'
  CMD="wget https://netlogin.lanl.gov/dana-na/auth/login.cgi --post-data='tz_offset=-420&username=${USER}&password=${PASS}&realm=Visitors&btnSubmit=Sign+In' -O -| grep Welcome"
  eval "$CMD"
}
