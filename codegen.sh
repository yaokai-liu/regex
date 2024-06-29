#!/usr/bin/env bash

python liu-regex/generate.py grammar/json --compact
python script/codegen.py
