#include <cstdlib>
#include "app.hpp"

int main(int argc, char* args[])
{
	App app{ "ImCtrl" };
	app.run();
	
	return EXIT_SUCCESS;
}