#!/bin/bash

.././lem-in -g < $1 2>graph 1>/dev/null
dot -T png -o graph.png graph -Gnodesep=0.3 -Granksep=0.1
rm graph
