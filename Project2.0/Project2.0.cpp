#include "ApplicationController.hpp"

void printAppName();

int main() {
	
    AppController appController;
	printAppName();
    appController.run();
    
    return 0;
}

void printAppName() {
	std::cout << "   ___                     ______                             \n"
		<< "  |_  |                    | ___ \\                            \n"
		<< "    | | ___   ___   _ __   | |_/ /__ _  _ __  ___   ___  _ __ \n"
		<< "    | |/ __| / _ \\ | '_ \\  |  __// _` || '__|/ __| / _ \\| '__|\n"
		<< "/\\__/ /\\__ \\| (_) || | | | | |  | (_| || |   \\__ \\|  __/| |   \n"
		<< "\\____/ |___/ \\___/ |_| |_| \\_|   \\__,_||_|   |___/ \\___||_|   \n" << std::endl;
}