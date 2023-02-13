#!/bin/bash

# Check if the number of arguments is correct
if [ $# -ne 3 ]; then
  echo "Error: Incorrect number of arguments."
  echo "Usage: $0 input_file group_name operation_flag"
  exit 1
fi

# Check if the operation flag is valid
if [ "$3" != "-a" ] && [ "$3" != "-r" ]; then
  echo "Error: Invalid operation flag. Use -a to add users or -r to remove users."
  exit 1
fi

# Assign the arguments to variables
input_file=$1
group_name=$2
operation_flag=$3

# Check if the group already exists
if ! grep -q "$group_name" /etc/group; then
  if [ "$operation_flag" == "-a" ]; then
    echo "Creating group $group_name..."
    groupadd "$group_name"
  else
    echo "Error: Group $group_name does not exist."
    exit 1
  fi
fi

# Loop through the input file
while read line; do
  # Skip empty and blank lines
  if [ -z "$line" ]; then
    continue
  fi

  # Split the line into user ID and password
  user_id=$(echo "$line" | cut -d' ' -f1)
  password=$(echo "$line" | cut -d' ' -f2)

  if [ "$operation_flag" == "-a" ]; then
    # Check if the user already exists
    if id "$user_id" > /dev/null 2>&1; then
      echo "User $user_id already exists. Skipping..."
      continue
    fi

    echo "Adding user $user_id..."
    useradd -m -p "$password" "$user_id"
    usermod -a -G "$group_name" "$user_id"
  else
    # Check if the user exists
    if ! id "$user_id" > /dev/null 2>&1; then
      echo "Error: User $user_id does not exist."
      continue
    fi

    echo "Removing user $user_id..."
    userdel -r "$user_id"
  fi
done < "$input_file"
