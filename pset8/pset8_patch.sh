#!/bin/bash
find -name *.php | xargs chmod 640
find -type d | xargs chmod 711
find -not -type d -and -not -name *.php | xargs chmod 644
chmod 711 bin
chmod 711 bin/import
chmod 711 includes
chmod 711 vendor
chmod 711 pset8_patch.sh