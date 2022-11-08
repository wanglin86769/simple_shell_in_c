# Simple Shell in C

The shell utility is very useful for register access testing of hardware devices like PCI, Modbus and so on. For demonstration purposes, hardware registers are simulated by a buffer in memory. Therefore, if the shell utility is intended to be able to access real hardware, the hardware access functions need to be re-implemented.

## Development environment

* Ubuntu 20.04 LTS
* Linux 5.15.0
* gcc 9.4.0

## Compile and Execute
```
gcc shell.c -o shell.out
./shell.out
```

## Command usage

### **help**

![Alt text](docs/screenshots/help.png?raw=true "Title")

### **mread**

![Alt text](docs/screenshots/mread.png?raw=true "Title")

### **mwrite**

![Alt text](docs/screenshots/mwrite.png?raw=true "Title")

### **read**

![Alt text](docs/screenshots/read.png?raw=true "Title")

### **write**

![Alt text](docs/screenshots/write.png?raw=true "Title")

### **read8**

![Alt text](docs/screenshots/read8.png?raw=true "Title")

### **write8**

![Alt text](docs/screenshots/write8.png?raw=true "Title")

### **read16**

![Alt text](docs/screenshots/read16.png?raw=true "Title")

### **write16**

![Alt text](docs/screenshots/write16.png?raw=true "Title")

### **read32**

![Alt text](docs/screenshots/read32.png?raw=true "Title")

### **write32**

![Alt text](docs/screenshots/write32.png?raw=true "Title")

### **exit**

![Alt text](docs/screenshots/exit.png?raw=true "Title")