# Hypatie
## Personal password encryptor
This project aims to secure all your personal passwords in one single app, and access them with a unique password.

[![Build Status](https://travis-ci.com/Kevin-Vu/hypatie.svg?branch=master)](https://travis-ci.com/Kevin-Vu/hypatie) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/0dc6388459214bddbd4b39dd3b103d90)](https://www.codacy.com/app/Kevin-Vu/hypatie?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Kevin-Vu/hypatie&amp;utm_campaign=Badge_Grade) ![Version](https://img.shields.io/badge/hypatie-v1.0-blue.svg)

----

## Getting Started
### Installation
In order to compile this project, please install the following libraries : **openssl** , **libssl-dev**.
```bash
sudo apt install openssl libssl-dev
```

## Compile the project
```bash
make
```

### How to use
Go to the `exe` folder.
```txt
./hypatie.exe <args>
```
Here are the arguments you can pass through the program :
```txt
new simple|special <length>    # generate a random password : alphanum with or without special characters
read                           # print a password
add                            # add a new password
rm                             # remove a password
replace                        # replace a password by a new one
passwd                         # change the master password
```

## Memory leak verification
Actually there is no memory leak found.   
Tool used : **Valgrind**.

## Sources
Here are the source used in this project :  
**kulkarniamit** : [link](https://github.com/kulkarniamit/openssl-evp-demo/blob/master/openssl_evp_demo.c) - openssl part  
**Yoann Sculo** : [link](http://www.yoannsculo.fr/faire-un-hash-md5-dun-string-en-c/) - md5sum part  
**alk** : [link](https://stackoverflow.com/questions/17984628/switch-statement-using-string-on-an-array) - switch statement part  
**Lionel Lacassagne** : [link](https://www.lip6.fr/actualite/personnes-fiche.php?ident=P1046) - Makefile
