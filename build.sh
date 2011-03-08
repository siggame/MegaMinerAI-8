#!/bin/bash

logfilename=build.log # name of log
rootdir=$PWD # where this script is located
logfilepath=$rootdir/$logfilename

# Give build info
echo -n "Build started by " | tee $logfilepath # -n flag drops ending newline
whoami | tr -d "\n" | tee -a $logfilepath # truncates newline char from whoami
echo -n " at " | tee -a $logfilepath
date | tee -a $logfilepath
echo "" | tee -a $logfilepath # Throw a newline on the end...

# Start building!

# Build the codegen
echo "Starting codegen build..." | tee -a $logfilepath
cd ./codegen
python main.py |& tee -a $logfilepath # |& pipes sterr AND stout to tee
echo "" | tee -a $logfilepath # Throw a newline on the end...
cd $rootdir

# Build the clients made by the codegen
# c client

echo "Copying in new parser to c client..." | tee -a $logfilepath
rm -f ./codegen/output/c/sexp/*
cp -fv ./sexp/lex/* ./codegen/output/c/sexp/
echo "Starting c client build..." | tee -a $logfilepath
cd ./codegen/output/c
make |& tee -a $logfilepath
echo "" | tee -a $logfilepath
cd $rootdir

# java client
echo "Starting java client build..." | tee -a $logfilepath
cd ./codegen/output/java
make |& tee -a $logfilepath
echo "" | tee -a $logfilepath
cd $rootdir

# python client
echo "Starting python client build..." | tee -a $logfilepath
cd ./codegen/output/python
make |& tee -a $logfilepath
echo "" | tee -a $logfilepath
cd $rootdir

# Build sexp
echo "Copying in new parser to visualizer..." | tee -a $logfilepath
rm -f ./codegen/output/visualizer/sexp/*
cp -fv ./sexp/lex/* ./codegen/output/visualizer/sexp/
echo "Starting sexp build..." | tee -a $logfilepath
cd ./codegen/output/visualizer/sexp
make |& tee -a $logfilepath # |& pipes sterr AND stout to tee
cd $rootdir

# Build visualizer
echo "Starting visualizer build..." | tee -a $logfilepath
cd ./codegen/output/visualizer
make |& tee -a $logfilepath # |& pipes sterr AND stout to tee
cd $rootdir


exit 0

