#!/bin/bash

echo "echo Hello World #echo Goodbye"
echo "hello ## hey"
echo "echo hello && echo # hey"
echo "echo yes && #"
echo "ls -a #echo hello world"
echo "history; echo hello world; #comment"
echo "echo hello"

cd ..
bin/rshell << EOF

echo Hello World #echo Goodbye
hello ## hey
echo hello && echo # hey
echo yes && #
ls -a #echo hello world
history; echo hello world; #comment
ls -a; #hello there
echo #hello

exit
EOF

