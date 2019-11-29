#!/bin/bash

../rshell < test_literal_tests.sh


(echo hi && echo b) || (echo c && echo d)

(echo a || ls -a) || (echo c && echo d)


