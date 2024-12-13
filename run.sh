#!/bin/bash

arg=$1

if [ $arg == ""]; then
    arg=`printf "client\nsprites viewer" | fzf`
fi

if [[ $arg == "client" ]]; then
    cd ./build/src/client
    ./application_tibia
elif [[ $arg == "sprites view" ]]; then
    cd ./build/src/sprites_viewer
    ./sprites_viewer
fi

