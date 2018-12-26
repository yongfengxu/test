#!/bin/sh

python $MOBILEGW_TOOLS/scripts/esc/esc2dot.py $@
DOT=`echo "$@" | sed -r 's/\.esc/.dot/g'`
PNG=`echo "$@" | sed -r 's/\.esc/.png/g'`
dot -Tpng $DOT > $PNG
eog $PNG
