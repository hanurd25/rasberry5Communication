#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main() {
    const char* port = "/dev/ttyUSB0"; // Example serial port path
    int serial_port = open(port, O_RDWR);

    if (serial_port < 0) {
        std::cerr << "Failed to open serial port: " << port << std::endl;
        return 1;
    }

    struct termios tty;
    if (tcgetattr(serial_port, &tty) != 0) {
        std::cerr << "Error configuring serial port" << std::endl;
        return 1;
    }

    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; 
    tty.c_cflag |= CLOCAL | CREAD; 
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); 
    tty.c_lflag = 0; 
    tty.c_oflag = 0; 

    tcsetattr(serial_port, TCSANOW, &tty);

    std::cout << "Serial communication started with Teensy!" << std::endl;

    while (true) { // Communication while loop
        
        // Reading a String from Teensy
        char buffer[256] = {0}; 
        int bytesRead = read(serial_port, buffer, sizeof(buffer) - 1); // Leave space for null-terminator
        
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0'; 
            std::cout << "Received string from Teensy: " << buffer << std::endl;
        }

        //Sending a string 
        std::string command = "Hello\n"; 
        write(serial_port, command.c_str(), command.size());

        usleep(100000); 
    }

    close(serial_port);
    return 0;
}
