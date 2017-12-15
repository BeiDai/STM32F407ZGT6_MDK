STLink firmware upgrade applications

1. In folder Windows:

   Contains the application in its "historical" form: executable dedicated to Windows + dll.
   With all most recent firmwares (V1J13S3 for ST-Link/V1 boards, V2J24S4 for ST-Link/V2 boards,
   and V2J24M11 for ST-Link/V2-1 boards)

2. In folder AllPlatforms:

   Contains a new GUI based on Java, with native ST-Link libraries for running on Windows 32 bits,
   Windows 64bits, Linux 32bits, Linux 64bits and MacOS 64bits.
   
   The application requires the Java Runtime Environment 7u51 (or more recent) being installed.
   In platforms without .jar file extension association, the application can be launch by the command
   "java -jar STLinkUpgrade.jar".

   On Linux, the application relies on libusb-1.0, which must be installed separately. For
   instance on Ubuntu, through the command "sudo apt-get install libusb-1.0".

   On Linux, users must be granted with rights for accessing the ST-Link USB devices. To do
   that, it might be necessary to add rules into /etc/udev/rules.d. For instance on Ubuntu,
   through the command "sudo cp 49-stlinkv2-1.rules /etc/udev/rules.d".
   
   Tested on:
   - Windows7 64bits
   - Linux Fedora (32 and 64bits)
   - Linux Ubuntu (64 bits)
   - MacOS 10.9.3