#!/usr/bin/env bash

python grammar/xnf/generate.py grammar/json --compact
python script/codegen.py
