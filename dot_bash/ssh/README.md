## How to encrypt and decrypt ssh key

### Encrypt ssh key
`bzip2 -c id_rsa | openssl enc -aes-256-cbc -md sha256 -pbkdf2 -iter 10000 -e > id_rsa.bz2.enc`
### Decrypt ssh key
`openssl enc -aes-256-cbc -md sha256 -pbkdf2 -iter 10000 -d -in id_rsa.bz2.enc | bzip2 -d > id_rsa`
