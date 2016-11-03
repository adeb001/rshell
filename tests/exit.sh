#!/bin/bash


cd ..

bin/rshell << EOF
echo hello && exit
EOF

bin/rshell << EOF
exit
EOF

bin/rshell << EOF
echo hey && exit
EOF

bin/rshell << EOF
ls -a && exit
EOF


EOF