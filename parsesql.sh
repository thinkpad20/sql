#!/bin/bash

echo "Attempting to parse $1..."
cat $1 | bin/sql_parser
echo -e "parsed successfully.\n"