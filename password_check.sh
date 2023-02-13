#!/bin/bash

password=$1

# Check the length of the password
if [ ${#password} -lt 8 ]; then
  echo "Error: Password must be at least 8 characters long"
  exit 1
fi

# Check if the password contains at least one numeric character
if echo "$password" | grep -q '[0-9]'; then
  has_number=1
else
  echo "Error: Password must contain at least one numeric character"
  exit 1
fi

# Check if the password contains at least one of the specified non-alphabetic characters
if echo "$password" | grep -q '[@#$%&*+=-]'; then
  has_special=1
else
  echo "Error: Password must contain at least one of the following non-alphabetic characters: @, #, $, %, &, *, +, -, ="
  exit 1
fi

# If all tests pass, print success message
if [ $has_number ] && [ $has_special ]; then
  echo "Password is strong and meets the requirements."
fi
