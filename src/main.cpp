/*
 * main.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: nek
 */

#if 0


#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// This example reads the configuration file 'example.cfg' and displays
// some of its contents.

int main(int argc, char **argv)
{

	double h[3][3];

    // std::ifstream is RAII, i.e. no need to call close
    std::ifstream cFile ("translation_matrix");
    if (cFile.is_open())
    {
    	int line_count = 0;

        std::string line;

        while(getline(cFile, line))
       {

            if( line.empty() || line[0] == '#' )
            {
                continue;
            }

            //line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
            line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
            line.erase(std::remove(line.begin(), line.end(), '['), line.end());
            line.erase(std::remove(line.begin(), line.end(), ']'), line.end());
            line.erase(std::remove(line.begin(), line.end(), ';'), line.end());

            cout << "this is the line " << line << endl;

            if ( line.compare("TranslationMatrix:")) continue;

            //auto delimiterPos = line.find("=");
            //auto name = line.substr(0, delimiterPos);

            //std::string values = line.substr(delimiterPos + 1);

            //cout << name << endl;

            const char * values_c = line.c_str();

            sscanf( values_c, "%lf,%lf,%lf", &h[line_count][0], &h[line_count][1], &h[line_count][2]);

            //std::cout << h << endl;

//            [0.3708366869868933, 0.04556253204385634, 76.47641610736288;
//             -0.003012919456041024, 0.3967046517391609, -68.84539787396159;
//             1.402238816425516e-05, 5.179393883572331e-05, 1]

            line_count++;
        }

    }
    else
    {
        std::cerr << "Couldn't open config file for reading.\n";
    }

    for(int i=0; i<3; i++){
    	for(int j = 0; j<3; j++){
    		std::cout << h[i][j];
    	}
    	cout << endl;
    }


  return(EXIT_SUCCESS);
}
#endif
// eof
