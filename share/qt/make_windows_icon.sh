#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/mokacoin.ico

convert ../../src/qt/res/icons/mokacoin-16.png ../../src/qt/res/icons/mokacoin-32.png ../../src/qt/res/icons/mokacoin-48.png ${ICON_DST}
