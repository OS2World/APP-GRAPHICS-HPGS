#!/bin/sh
#
# $Id: eps2png.sh 49 2005-02-03 14:16:51Z softadm $
#
# Convert an eps image to png.
#

sz_arg=$(awk '/^%%BoundingBox:/ { printf("-dDEVICEWIDTHPOINTS=%d -dDEVICEHEIGHTPOINTS=%d",$4,$5); }' < $1)

gs -sDEVICE=pngalpha $sz_arg -r144x144 -dEPSCrop -dBATCH -dNOPAUSE -q -sOutputFile=$2 - $1 <<EOF
1 setgray
0 0 moveto 600 0 lineto 600 800 lineto 0 800 lineto closepath fill
EOF
