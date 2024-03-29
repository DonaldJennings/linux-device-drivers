#!/bin/sh
module="scullc"
device="scullc"

# invoke rmmod with all arguments we got
rmmod $module $* || exit 1

# remove nodes
rm -f /dev/${device}[0-3] /dev/${device}

exit 0