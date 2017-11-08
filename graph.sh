#!/bin/bash

make clean
make GRAPH=yes
./lem-in < $1 2>graph 1>-
dot -T png -o graph.png graph -Gnodesep=0.3 -Granksep=0.1
rm graph
