#!/bin/bash

arg=$1

if [[ $1 == "all" ]]; then
    rm -rf ./build/*
else
    rm -rf ./build/src/*
fi
