#!/bin/bash

./merge lena.inr.gz -s $1 -m $2 merge$1$2
xvis -nu merge$1$2 &
