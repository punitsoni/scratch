#!/bin/sh

echo "provision: user configuration"

echo "HOME=$HOME"

cd $HOME
ln -s /vagrant $HOME/v

echo "installing dotfiles"
wget https://github.com/punitsoni/dotfiles/archive/master.zip -P /tmp/ > /dev/null 2>&1
unzip /tmp/master.zip > /dev/null
mv dotfiles-master dotfiles
rm -f /tmp/master.zip
cd dotfiles
echo "y\ny\ny\n" | ./setup.sh
echo "DONE."
