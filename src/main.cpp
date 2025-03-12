#include <cstdlib>
#include "app.hpp"

int main(int argc, char* argv[])
{
	App app{ "ImCtrl", argc, argv };
	app.run();
	
	return EXIT_SUCCESS;
}