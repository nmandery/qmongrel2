#!/bin/sh

set -e

[ -d run ] || mkdir run
[ -d logs ] || mkdir logs

m2sh load -config mongrel2.conf
