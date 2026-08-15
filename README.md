# ffind - fast find

ffind is an alternative to plocate (and also mlocate) due to them being so bloated. It focues on minimalism, speed and efficiency.

## Installation

You can compile the ffind.c file manually or either run the Makefile provided in the repo.
For the Makefile you will have to make sure gcc or similar is installed on your system.

```
xz3k@gentoo ffind $ make install
```

you can also make just the binary by doing `make` alone

**Note** : You may edit the CFLAGS, CC or SYSBIN in the Makefile to fit your system.
