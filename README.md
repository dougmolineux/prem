prem
====

Command-Line Utility that prints the standings of the English Premier League.

Written in C. Utilizes API Provider Kimono Labs and the cJSON library to parse the JSON.

Tested on CentOS.

How to Build & Run
==================

gcc prem.c cJSON.c -o prem -lm
./prem
