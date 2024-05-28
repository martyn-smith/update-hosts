Hosts Updater
===

A quick and dirty means of updating your `/etc/hosts` file, principally for Hack The Box challenges.

Rationale
---

If you're cycling through HTB (other CTFs are available..) boxes frequently and you don't want to memorise IPs, or are doing webapp stuff and need the virtual host to be correct, you need to edit your `/etc/hosts` file often. If you're like me, you may not trust that there are no IP collisions, so you may also want all older box hostnames to be removed. Hence this little ditty.

It's written in C, for two reason:
  1. that bit of you that says "keep you skills in this archaic language at least moderately honed"
  2. I wanted something guaranteed to build on the simplest possible box. So just gcc. A reference implementation in Rust is present, but I don't expect to use it.

Installation & Usage
---

It's pretty easy to build. To use:

```
./update-hosts [-a] HOSTNAME IP
```

Where HOSTNAME is a Fully-Qualified Domain Name, IP is IP (this is not sanity checked!), and `-a` is an optional parameter to switch on append-only mode, i.e. do *not* remove previous entries.

TODO
---

  - binary releases and packaging
  - Makefile with test and prod targets
