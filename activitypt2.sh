#!/bin/bash

# Change to home directory
cd ~
echo "Current directory: $(pwd)"
# Create child directory called mycode
mkdir mycode
cp *.c mycode/
# Change to the mycode directory
cd mycode
echo "Current directory: $(pwd)"
echo "Files with '.c' extension:"
# Navigate up a directory
cd ..
echo "Current directory: $(pwd)"
# Create a new child directory called mycode2
mkdir mycode2

# Copy all files from the mycode directory to the mycode2 directory
cp -r mycode/* mycode2/
# Rename the mycode directory to deadcode
mv mycode deadcode

# Remove the deadcode directory and all its files
rm -rf deadcode
