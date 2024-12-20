#!/bin/bash

arg=$1

if [ $arg == ""]; then
    arg=`printf "client\nsprites_viewer" | fzf`
fi

if [[ $arg == "client" ]]; then
    cd ./build/src/client
    ./application_tibia
elif [[ $arg == "sprites_viewer" ]]; then
    cd ./build/src/sprites_viewer
    ./sprites_viewer
fi

