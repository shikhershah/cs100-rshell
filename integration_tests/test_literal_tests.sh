#!/bin/bash

../rshell < test_literal_tests.sh


test -d unit_tests

test -e names.txt
test -e rshell

test -d integration_tests

test -e abd             
