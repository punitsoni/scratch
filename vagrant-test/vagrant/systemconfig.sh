#!/bin/sh

if [ $(id -u) != "0" ]; then
    echo "ERROR: this script must be run as root." >&2
    exit 1
fi

echo "provision: system configuration"

install() {
    echo "installing $1"
    apt-get install -y $1 > /dev/null
}

echo "updating package database"
apt-get update > /dev/null

install git vim
install tmux
install unzip tree
echo "DONE."
