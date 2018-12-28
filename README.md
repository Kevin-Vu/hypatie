# Hypatie
### Personal password encryptor
This project aims to secure all your personal passwords in one single app, and access them with a unique password.

[![Build Status](https://travis-ci.com/Kevin-Vu/hypatie.svg?branch=master)](https://travis-ci.com/Kevin-Vu/hypatie) [![Version](https://img.shields.io/badge/hypatie-v1.0-blue.svg)

----

# Getting Started
## Installation
In order to compile this project, please install the following libraries : `openssl` , `libssl-dev`.

```bash
sudo apt install openssl libssl-dev
```

## Compile the project
```bash
make
```

# How to use
Go to the `exe` folder.
```
./hypatie.exe <args>
```
Here are the arguments you can pass through the program :
```
new simple|special <length>    # generate a random password
read                           # print a password
add                            # add a new password
rm                             # remove a password
replace                        # replace a password by a new one
passwd                         # change the master password
```
