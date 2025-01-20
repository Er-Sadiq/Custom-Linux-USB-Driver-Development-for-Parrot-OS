# Custom Linux USB Driver for Parrot OS

This project involves the development of a custom USB driver for Parrot OS, designed to enable seamless communication between the kernel and USB devices. The driver facilitates device detection, connection management, and debugging using real-time logging.

## Features

- **USB Device Interaction**: Enables interaction with USB devices via the kernel.
- **Device Probe & Disconnect**: Manages device connection and removal events using USB protocols.
- **Kernel Module Integration**: Implements initialization and cleanup routines for a robust driver structure.
- **Real-Time Logging**: Integrates logging mechanisms for effective debugging of USB device interactions.

## Requirements

- **Parrot OS** or compatible Linux-based systems.
- **Kernel headers** for your specific Linux version.
- **C Programming** knowledge for driver compilation.

## Installation

1. Clone or download the project repository.
2. Ensure that the necessary kernel headers are installed on your system.
   [deb ker 6.11.5 in the case]
4. Compile the driver using the following command:

   ```
   make
   ```

5. Load the driver into the kernel:

   ```
   sudo insmod usb_driver.ko
   ```

6. To unload the driver:

   ```
   sudo rmmod usb_driver
   ```

## Usage

Once the driver is loaded, it automatically detects connected USB devices and logs events related to device probing and removal. You can check the logs for details:

```
dmesg | tail -n 20
```

## Contributing

Feel free to fork this project, submit issues, or contribute improvements via pull requests.

## License

This project is licensed under the GPL-2.0 License.
