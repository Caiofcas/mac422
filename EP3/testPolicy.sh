#!/bin/sh

./make_holes &
memorymap > holes1.txt
./change_policy 1
./tester &
memorymap > holes_wf.txt
./make_holes &
memorymap > holes2.txt
./change_policy 0
./tester &
memorymap > holes_ff.txt