#!/bin/bash
cd script_maps
echo -e "\n\033[095mMaps devant retourner une erreur\033[0m"
./script_ko.sh
echo -e "\n\033[095mMaps devant s'executer normalement\033[0m"
./script_ok.sh
cd ..
