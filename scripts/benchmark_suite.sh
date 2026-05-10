#!/bin/bash
set -euo pipefail

SCENES=(1 2 3 4 5 6)
THREADS=(1 2 4 8)
CHUNKS=(1 4 8 16 32 64)
TILES=(1 8 16 32 64)

for scene in "${SCENES[@]}"; do
  for threads in "${THREADS[@]}"; do
    for chunk in "${CHUNKS[@]}"; do
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