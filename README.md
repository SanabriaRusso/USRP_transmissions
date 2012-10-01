USRP Transmissions
------------------

This repository contains the files used to achieve successful PHY and file transmission using the USRP and GNURadio.

For our setup, we used benchmark_tx_mod.py for the transmistter and benchmark_rx_mod.py for the receiver.

To correctly execute them, or just to replicate our attempt, the following parameters must be passed:

At the transmistter example:
----------------------------
Before reading the code, it is important to highlight that the values inside the gt and lt signs (<>) are parameters unique to each device configuration. So you must have them with you.

If you don't know the sub-spec or antenna, try issuing the uhd_usrp_probe command from anywhere inside the USRP.

./benchmark_tx_mod.py -m gmsk -p 4 -r 0.2e6 --tx-amplitude=0.25 -f <frequency> --spec=<your sub-device> -A <antenna> --tx-gain=16 --from-file=<your binary file> 

You can always use the --help flag to call the help dialog for each command.

At the receiver example:
------------------------

./benchmark_rx_mod.py -m gmsk -p 4 -r 0.2e6 --spec=<your sub-spec> --antenna=<antenna> -f <frequency> --rx-gain=16 --omega-relative-limit=0.005 --gain-mu=0.175 --mu=0.5 

The binaryComparison.cc file:
-----------------------------
This little script is intended to check in which octect an image differs from other. 

It does not work for all purposes. And no warranty is given under any circumstances.

For our work, an image is sent over TV White Spaces with no security measures (upper layers, etc.). At arrival, the image is compared with the one that was sent. This script just points out in which octect the connection failed, producing a corrupted image.

Feel free to modify it.

Luis Sanabria-Russo
luis.sanabria@upf.edu
