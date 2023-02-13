#!/bin/bash

# Echo current directory to the screen
echo "Current directory: $(pwd)"

# Change to home directory
cd ~
echo "Changed to home directory: $(pwd)"

# Change to a child directory within the home directory
cd ~/child_directory
echo "Changed to child directory: $(pwd)"

# List all files ending with .c in the child directory
echo "Files with '.c' extension:"
ls -1 *.c

# Navigate back to home directory
cd ~
echo "Back to home directory: $(pwd)"
