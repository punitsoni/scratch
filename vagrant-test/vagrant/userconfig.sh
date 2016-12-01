#!/bin/sh
# This script is run as default user when vagrant machine first comes up
# or when provision is initiated using "vagrant provision" command
# This always runs after system configuration is finished

echo "[provision] user configuration"

echo "installing dotfiles..."
rm -rf /tmp/dotfiles
git clone https://github.com/punitsoni/dotfiles.git /tmp/dotfiles \
  2> /dev/null
/tmp/dotfiles/setup.sh -f > /dev/null
rm -rf /tmp/dotfiles

# TODO: move this to a separate file
# current-user specific settings
git config --global user.name "Punit Soni"
git config --global user.email "punitxsmart@gmail.com"

echo "DONE."
