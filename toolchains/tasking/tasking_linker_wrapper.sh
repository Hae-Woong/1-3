#!/bin/bash
_fixed="${@/\@/-f }"
#echo "########$_fixed"
external/tasking_linux+/bin/ltc ${_fixed}
