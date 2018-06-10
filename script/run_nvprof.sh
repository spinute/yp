#!/bin/bash
nvprof --metrics `nvprof --query-metrics | egrep : | tail -n +3 | cut -d ':' -f 1 | tr -d ' ' | tr '\n' ','` $@
