# Serial Data Logger

it allows saving the data arriving on any serial port. Only available for linux. In order to use it, first, compile it:

```bash
$ make
```

The current version doesn't support setting the baudrate by itself so there's a bash script that calls the logger. Anyway, to run:

```bash
octoumbrella /dev/ttyUSB0 115200 outfile.dat
```
