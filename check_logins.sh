#!/bin/bash

# loop through all users in the system
for username in $(cut -d: -f1 /etc/passwd); do
  # get the last login time for the user
  last_login=$(last -w $username | head -n 1 | awk '{print $4, $5, $6}')

  # check if the last login was during non-office hours (before 8am or after 5pm)
  if [[ $last_login < "08:00" || $last_login > "17:00" ]]; then
    echo "$username logged in at $last_login"
  fi
done
