# LiteweightOS

LiteweightOS is a simple, lightweight, monolithic kernel for the x86-32 architecture. The goal 
of LiteweightOS is to provide basic kernel functionalities in a transparent and simple manner. 
Current LiteweightOS support includes VGA support, memory management, and process handling.
The kernel is currently under development and supports integration with the GRUB Bootloader.

## Model

The LiteweightOS kernel follows a very basic operational model:

* `VGA Support`: An intuitive, scrolling text interface that is user-friendly. 
* `Fully Paged & Secure Memory Model`: A basic memory system that uses secure address translation, yet remains transparent to developers in its operation.
* `Core Libraries`: A set of core Ring 0 libraries that are securely accessible all the way through userspace. 

The goal with this framework is to create a hardware-software interface that is fully transparent to users, and makes 
programming at the lowest level and communicating with hardware easy and intuitive.

## Development

LiteweightOS is currently under development, meaning new features and supports are being added. Currently, the 
package includes just the kernel and basic hardware utilities, but the goal is to eventually expand to full OS support. 

##Ports
LiteweightOS only supports the x86-32 architecture at this stage. Future goals include expanding support to include x86-64
and eventually RISC-V architectures.
