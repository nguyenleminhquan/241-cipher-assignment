#!/usr/bin/env bash

out_file=${1:-main}

if [[ "$out_file" == "main" ]]; then
  args="-fopenmp -I Inc Src/*.cpp -o $out_file"
else
  args="-fopenmp .local/${out_file}.cpp -o $out_file"
fi

# echo "g++ -std=c++11 $args"
eval "g++ –std=c++11 $args"
