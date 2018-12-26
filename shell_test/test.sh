#!/usr/bin/env bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
echo $SCRIPT_DIR

WORK_DIR=$SCRIPT_DIR

# Workspace where to find the git repository, build and run tests
WORKSPACE="$( cd "$( dirname "$WORK_DIR/../../.." )" && pwd )"
echo $WORKSPACE

TEST_LOG_DIR=$WORKSPACE/logs
STORE_LOGS="/proj/epg/sgw_dt/massive_logs"



