#!/usr/bin/env bash

if [ -d "grammar/json" ]; then
  echo ''
else
  mkdir grammar/json
fi
python liu-regex/generate.py grammar/json --compact
python script/codegen.py
