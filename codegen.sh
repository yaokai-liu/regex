#!/usr/bin/env bash

if [ -d "json/regex" ]; then
  echo ''
else
  mkdir -p json/regex
fi
if [ -d "grammar/generated/regex" ]; then
  echo ''
else
  mkdir -p grammar/generated/regex
fi
python liu-regex/generate.py json --compact
python xnf-json2C/codegen.py json template grammar/generated
