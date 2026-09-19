#!/bin/bash
if [ ! -d "build" ]; then
    mkdir build
fi

cmake -DENV_PATH_JWT_SECRET="../.upcordJwtSecret" \
      -DENV_DOMAIN="upcord.org" -G Ninja -B build/ .

cmake --build build/
