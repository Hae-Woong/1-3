#!/bin/bash
_fixed="${@/\@/--option-file=}"
external/tasking_linux+/bin/cctc "${_fixed}"
