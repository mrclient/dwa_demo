#!/bin/bash
HERE="$(dirname "$(readlink -f "${0}")")"
LD_LIBRARY_PATH="${HERE}:${LD_LIBRARY_PATH}"
export LD_LIBRARY_PATH
EXEC="${HERE}/dwa_demo"
exec "${EXEC}"
