#!/bin/sh
# This script is run as root user when vagrant machine first comes up
# or when provision is initiated using "vagrant provision" command

if [ $(id -u) != "0" ]; then
    echo "ERROR: this script must be run as root." >&2
    exit 1
fi

echo "[provision] system configuration"

install() {
    echo "installing $1"
    apt-get install -y $1 > /dev/null
}

echo "updating package database..."
apt-get update > /dev/null
echo "upgrading packages..."
apt-get -y upgrade > /dev/null
apt-get -y autoremove > /dev/null
install git vim
install tmux
install unzip tree
echo "DONE."
