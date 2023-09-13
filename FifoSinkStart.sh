#!/usr/bin/bash
mkfifo FifoSink
while true
do
	echo "Sink Start"
	cat FifoSink
	echo "Sink Finish"
done
