#!/bin/bash
set -euo pipefail

./build/ray-tracing \
  --scene 4 \
  --chunk-size 1 \
  --threads 8 \
  --tile-size 1