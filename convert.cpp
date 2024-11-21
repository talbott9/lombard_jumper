#include <fstream>
#include <cstdlib>

//This is a tool for creating tilemaps
int row = 64;
int column = 128;
int TOTAL_TILES = row*column;
int rowcount = 1;

int main() {
	//Open the map
    	std::ofstream newmap("resources/tiles/newlevel.map" );
	for( int i = 1; i < TOTAL_TILES + 1; i++ )
	{
		newmap << "00 ";
		if( i % column == 0) {
			newmap << "\n";
			rowcount++;
		}
		/*if( i == column / 2 ) {
			newmap << "æ";
			printf("%i ", column / 2);
		}
		if( rowcount == row / 2 ) {
			newmap << "ø";
			printf("%i ", row / 2);
			rowcount = -999;
			}*/
	}
}

