# User Space (/dev/mem) Example for Embedded Linux
## Abstract
*It may not work in every Som. You can edit these pins by looking at the pins used by the kernel from your manufacturer's information sheet.*<br/>
Manufacturers may not have given access to some registration addresses when developing kernels. <br/>
In this case, error messages appear and you realize that access is not given. <br/>
Good luck to everyone.  <br/>
Wash your hands abundantly during these times of virus and code them clean :blush:
## Installation
You will learn the registration addresses in detail by clicking the [i.MX 6ULL Applications Processor Reference Manual
](https://www.nxp.com/products/processors-and-microcontrollers/arm-processors/i-mx-applications-processors/i-mx-6-processors/i-mx-6ull-single-core-processor-with-arm-cortex-a7-core:i.MX6ULL)link. <br/>


```bash
git clone https://github.com/gzbykyasin/User-Space-dev-mem-Example-for-Embedded-Linux.git
```

## Usage
```
gcc main.c -o main
./main
```
