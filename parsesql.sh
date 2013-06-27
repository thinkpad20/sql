#!/bin/bash
echo "Attempting to parse $1..."
cat $1 | ./sql_parser
echo -e "parsed successfully.\n"