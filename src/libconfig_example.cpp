/*
 * libconfig_example.cpp
 *
 *  Created on: Oct 12, 2021
 *      Author: nek
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <list>
#include <libconfig.h++>

using namespace std;
using namespace libconfig;


//g++ `pkg-config --cflags libconfig++` libconfig_example.cpp -o main `pkg-config --libs libconfig++`
//g++ libconfig_example.cpp -lconfig++




// This example reads the configuration file 'example.cfg' and displays
// some of its contents.

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;

  Config cfg;

  // Read the file. If there is an error, report it and exit.
  try
  {
    cfg.readFile("example.cfg");
  }
  catch(const FileIOException &fioex)
  {
    std::cerr << "I/O error while reading file." << std::endl;
    return(EXIT_FAILURE);
  }
  catch(const ParseException &pex)
  {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
    return(EXIT_FAILURE);
  }

  const Setting& root = cfg.getRoot();

  try
  {
    string name = cfg.lookup("cameraID");
    cout << "ID: " << name << endl << endl;

    //Setting &info = root["cameraID"];

    Setting &attr = root["connected_devices"]["attributes"];
    string model;
    attr[0].lookupValue("ID", model);
    cout << "mdel: " << model << endl << endl;
  }
  catch(const SettingNotFoundException &nfex)
  {
    cerr << "No 'name' setting in configuration file." << endl;
  }


  try{

	  Setting &matrices = root["translation_matrices"];
	  Setting &CameraL_trans = root["translation_matrices"]["CameraL"];

	  double left[3][3], right[3][3];

	  int count = matrices[0].getLength();

	  for(int i=0; i<count; i++ ){

		  const Setting &row = CameraL_trans[i];

		  int inside_count = row.getLength();

		  for(int j=0; j<inside_count; j++){

			Setting &values = row[j];

			  double my_value = values;

			  left[i][j] = my_value;
		  }
	  }

	  if (matrices.getLength() == 2){
		  Setting &CameraR_trans = root["translation_matrices"]["CameraR"];
		  //there are two cameras redo everything once again
		  int count = matrices[1].getLength();

		  for(int i=0; i<count; i++ ){

			  const Setting &row = CameraR_trans[i];

			  int inside_count = row.getLength();

			  for(int j=0; j<inside_count; j++){

				Setting &values = row[j];

				  double my_value = values;

				  right[i][j] = my_value;
			  }
		  }

	  }

	  cout << setprecision(20);

	  for (int i=0;i<3;i++){
		  for(int j=0;j<3;j++){
			  cout << left[i][j] << " ";
		  }
		  cout << endl;
	  }
	  if (matrices.getLength() == 2){
		  for (int i=0;i<3;i++){
			  for(int j=0;j<3;j++){
				  cout << right[i][j] << " ";
			  }
			  cout << endl;
		  }
	  }

		cout << "CameraL: " << matrices.lookup("CameraL").getType() << endl;

		cout << "CameraL: " << matrices.lookup("CameraL").isList() << endl;

		cout << "CameraL: " << matrices.lookup("CameraL").isArray() << endl;

		cout << "CameraL: " << matrices.lookup("CameraL").getIndex() << endl;
		cout << "CameraR: " << matrices.lookup("CameraR").getIndex() << endl;

		//cv::Mat TransL(3, 3, CV_8UC1, left);
		//cv::Mat TransR(3, 3, CV_8UC1, right);


  }catch(const SettingNotFoundException &nfex){
	  //something for not found here
	  cerr << nfex.what() << endl;
  }

//  // Output a list of all books in the inventory.
//  try
//  {
//    const Setting &books = root["inventory"]["books"];
//    int count = books.getLength();
//
//    cout << setw(30) << left << "TITLE" << "  "
//         << setw(30) << left << "AUTHOR" << "   "
//         << setw(6) << left << "PRICE" << "  "
//         << "QTY"
//         << endl;
//
//    for(int i = 0; i < count; ++i)
//    {
//      const Setting &book = books[i];
//
//      // Only output the record if all of the expected fields are present.
//      string title, author;
//      double price;
//      int qty;
//
//      if(!(book.lookupValue("title", title)
//           && book.lookupValue("author", author)
//           && book.lookupValue("price", price)
//           && book.lookupValue("qty", qty)))
//        continue;
//
//      cout << setw(30) << left << title << "  "
//           << setw(30) << left << author << "  "
//           << '$' << setw(6) << right << price << "  "
//           << qty
//           << endl;
//    }
//    cout << endl;
//  }
//  catch(const SettingNotFoundException &nfex)
//  {
//    // Ignore.
//  }
//
//   //Output a list of all books in the inventory.
//  try
//  {
//    const Setting &movies = root["inventory"]["movies"];
//    int count = movies.getLength();
//
//    cout << setw(30) << left << "TITLE" << "  "
//         << setw(10) << left << "MEDIA" << "   "
//         << setw(6) << left << "PRICE" << "  "
//         << "QTY"
//         << endl;
//
//    for(int i = 0; i < count; ++i)
//    {
//      const Setting &movie = movies[i];
//
//      // Only output the record if all of the expected fields are present.
//      string title, media;
//      double price;
//      int qty;
//
//      if(!(movie.lookupValue("title", title)
//           && movie.lookupValue("media", media)
//           && movie.lookupValue("price", price)
//           && movie.lookupValue("qty", qty)))
//        continue;
//
//      cout << setw(30) << left << title << "  "
//           << setw(10) << left << media << "  "
//           << '$' << setw(6) << right << price << "  "
//           << qty
//           << endl;
//    }
//    cout << endl;
//  }
//  catch(const SettingNotFoundException &nfex)
//  {
//    // Ignore.
//  }

  //            [0.3708366869868933, 0.04556253204385634, 76.47641610736288;
  //             -0.003012919456041024, 0.3967046517391609, -68.84539787396159;
  //             1.402238816425516e-05, 5.179393883572331e-05, 1]

  return(EXIT_SUCCESS);
}

// eof


