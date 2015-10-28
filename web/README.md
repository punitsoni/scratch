## Install node.js on ubuntu

### NVM based install

- node version manager [https://github.com/creationix/nvm]

```
curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.29.0/install.sh | bash

source ~/.bashrc

nvm install stable
```

### Manual Install
```
sudo apt-get install curl
curl --silent --location https://deb.nodesource.com/setup_4.x | sudo bash -
sudo apt-get install nodejs
```

update alternatives to provide node using nodejs
```
sudo update-alternatives --remove-all node
sudo update-alternatives --install /usr/bin/node node /usr/bin/nodejs 10
```

# Important links


