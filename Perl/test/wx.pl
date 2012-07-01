#!/usr/bin/perl

use strict;
use warnings;

map {printf "%08b ", $_} split /\./, shift;
