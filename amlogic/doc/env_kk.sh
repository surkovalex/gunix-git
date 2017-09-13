#!/bin/sh

export JAVA_HOME=/opt/jdk1.6.0_32/
export JRE_HOME=${JAVA_HOME}/jre
export CLASSPATH=.:${JAVA_HOME}/lib:${JRE_HOME}/lib
export PATH=${JAVA_HOME}/bin:$PATH
export PATH=/opt/gcc-linaro-arm-linux-gnueabihf/bin:$PATH
