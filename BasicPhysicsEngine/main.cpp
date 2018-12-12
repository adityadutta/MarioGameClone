#include "GameManager.h"
#include <iostream>

int main(int argc, char* args[])
{
	GameManager *ptr = new GameManager();
	bool status = ptr->OnCreate();
	if (status == true) {
		ptr->Run();
	}
	else if (status == false) {
		/// You should have learned about stderr (std::cerr) in Operating Systems 
		std::cerr << "Fatal error occured. Cannot start this program" << std::endl;
	}

	delete ptr;
	return 0;
}