# Serial Data Logger

it allows saving the data arriving on any serial port. Only available for linux. In order to use it, first, compile it:

```bash
make
```

The current version doesn't support setting the baudrate by itself so the data loggerthe data logger is called through a bash scripto run:

```bash
octoumbrella /dev/ttyUSB0 115200 outfile.dat
```

Later this data can be plot gnuplot or python matplotlib
