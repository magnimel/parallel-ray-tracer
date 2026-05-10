#!/bin/bash
set -euo pipefail

SCENES=(1 2)
THREADS=(1 2 4 8)
CHUNKS=(1 4 8 16 32)
TILES=(1 8 16 32)

for scene in "${SCENES[@]}"; do
  for threads in "${THREADS[@]}"; do

    if [ "$threads" -eq 1 ]; then
      active_chunks=(1)
    else
      active_chunks=("${CHUNKS[@]}")
    fi

    for chunk in "${active_chunks[@]}"; do
      for tile in "${TILES[@]}"; do
        echo "Running scene=$scene threads=$threads chunk=$chunk tile=$tile"

        ./build/ray-tracing \
          --scene "$scene" \
          --chunk-size "$chunk" \
          --threads "$threads" \
          --tile-size "$tile"
      done
    done
  done
done