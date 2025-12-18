#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <climits>
#include <cmath>
#include<sstream>
#include "tr-functions.h"

using std::vector, std::string;
using std::cout, std::cin;

// Part 1 Functions

void getUserInput(std::string& filename, unsigned int& rows, unsigned int& cols) {
    // update to guarantee filename is not an empty string and rows and cols are values from 1 to 4000
    bool goodfile = false;
    bool goodrow = false;
    bool goodcol = false;
    while(!goodfile || !goodrow || !goodcol) {
    if (!goodfile) {
        cout << "Enter filename: ";
        cin >> filename;
        if (filename.empty()) {
            cout << "Error: Filename cannot be empty" << std::endl;
        }
        else {
            goodfile = true;
        }
    }
    if (!goodrow && goodfile) {
        cout << "Enter number of rows (1-4000): ";
        if(!(cin >> rows)||rows<1||rows>4000) {
            cout << "Error: Invalid number of rows." << std::endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            goodrow = true;
        }
    }
    if (goodfile && goodrow && !goodcol) {
        cout << "Enter number of columns (1 - 4000): ";
        if (!(cin >> cols)|| cols < 1 || cols > 4000) {
            cout << "Error: invalid number of columns." << std::endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            goodcol = true;
        }
    }
}
}

vector<vector<unsigned int> > loadElevations(string filename, unsigned int rows, unsigned int cols) {
    std::fstream file(filename);
    if(!file) {
        throw std::invalid_argument("loadElevations: Failed to open " + filename);
    }
    
    std::vector<std::vector<unsigned int> > numbers;
    for (unsigned int i = 0; i < rows; i++) {
        std::vector<unsigned int> row;
        for (unsigned int j = 0; j < cols; j++) {
            unsigned int num = 0;
            file >> num;
            if (file.fail()) {
                if (file.eof()) {
                throw std::runtime_error("loadElevations: Not enough values");
            }
           
                else {
                throw std::runtime_error("loadElevations: Invalid elevation value");
            }

            }
            else {
                row.push_back(num);
            }
 
        }
        numbers.push_back(row);
    }
    file >> std::ws;
    if(!file.eof()) {
        throw std::runtime_error("loadElevations: Too many values");
    }
    
    return numbers;
}

void findMinMax(const vector<vector<unsigned int> >& elevations, unsigned int& min, unsigned int& max) {
    min = UINT_MAX;
    max = 0;
    if (elevations.empty()) {
        throw std::invalid_argument("findMinMax: Invalid elevations vector");
    }
    if (elevations.size() == 1) {
        throw std::invalid_argument("findMinMax: Invalid elevations vector");
    }
    for (unsigned int i=0;i < elevations.size();i++) {
        vector<unsigned int> row = elevations.at(i);
        if(row.empty()) {
            throw std::invalid_argument("findMinMax: Invalid elevations vector");
        }
        for (unsigned int j = 0; j < row.size(); j++) {
            if(row.at(j) > max) {
                max = row.at(j);
            }
            if(row.at(j) < min) {
                min = row.at(j);
            }
        }
    }

}

unsigned short scaleValue(unsigned int value, unsigned int min, unsigned int max) {
    if (min >= max) {
        throw std::out_of_range("scaleValue: min must be less than max");
    }
    if (value < min || value > max) {
        throw std::out_of_range("scaleValue: value must be in the range min <= value <= max");
    }

    double value_float = value;
    double min_float = min;
    double max_float = max;

    unsigned short num = round(((value_float-min_float)/(max_float-min_float))*255);


    return num;
}

vector<vector<Pixel> > createImage(const vector<vector<unsigned int> >& elevations) {
    if(elevations.empty()) {
        throw std::invalid_argument("createImage: Invalid elevations vector");
    }
    if (elevations.size() == 1) {
        throw std::invalid_argument("createImage: Invalid elevations vector");
    }
    size_t column = elevations.at(0).size();
    unsigned int min = 0;
    unsigned int max = 0;
    unsigned int &refmin = min;
    unsigned int &refmax = max;
     for(unsigned int k = 0; k < elevations.size(); k++) {
        if (elevations.at(k).size() != column) {
            throw std::invalid_argument("createImage: Invalid elevations vector");
        }
     }
    findMinMax(elevations,refmin,refmax);
    Pixel initialize = {0,0,0};
    vector<vector<Pixel> >image(column, vector<Pixel>(elevations.size(),initialize));

    for(unsigned int i = 0; i < elevations.size(); i++) {
        
        if (elevations.at(i).size() != column) {
            throw std::invalid_argument("createImage: Invalid elevations vector");
        }
        for (unsigned int j = 0; j < elevations.at(i).size(); j++) {
            unsigned short grey_value = scaleValue(elevations.at(i).at(j), refmin, refmax);
            Pixel p = {grey_value, grey_value, grey_value};
            image.at(j).at(i) = p;
        }
        
    }
    return image;
    
}

void saveImage(string filename, const vector<vector<Pixel> >& image) {
     if(image.empty()||image.at(0).empty()) {
        throw std::invalid_argument("saveImage: Invalid image vector");
    }
    if (image.size() == 1) {
        throw std::invalid_argument("saveImage: Invalid image vector");
    }
    size_t column = image.at(0).size();
    for(unsigned int i = 0; i < image.size(); i++) {
        if (image.at(i).size() != column) {
            throw std::invalid_argument("saveImage: Invalid image vector");
        }
     }
     if (filename.empty()) {
        throw std::invalid_argument("saveImage: Failed to open " + filename);
     }

     string new_file = filename+ ".ppm";

     std::ofstream file(new_file);
     if(!file) {
        throw std::invalid_argument("saveImage: Failed to open " + new_file);
     }

     string preamble = "P3";
     size_t width = image.size();
     size_t height = image.at(0).size();
     int max_color = 255;
     file << preamble << std::endl;
     file << width << " " << height << std::endl;
     file << max_color << std::endl;
     for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            const Pixel& pixel = image.at(j).at(i);
            file << static_cast<int>(pixel.r) << " " << static_cast<int>(pixel.g) << " " << static_cast<int>(pixel.b);
            if(j < width - 1) {
                file << " ";
            }
        }
        file << "\n";
     }

     file.flush();
     file.close();
     if(file.fail()) {
        throw std::runtime_error("saveImage: Failed to write to " + new_file);
     }




}



void processRoutes(vector<vector<Pixel> >& image, const vector<vector<unsigned int> >& elevations, Pixel colorAll, Pixel colorMin) {
    if(elevations.empty()) {
        throw std::invalid_argument("processRoutes: Invalid elevations vector");
    }
    if (elevations.size() == 1) {
        throw std::invalid_argument("processRoutes: Invalid elevations vector");
    }
    
     for(unsigned int k = 0; k < elevations.size(); k++) {
        if (elevations.at(k).size() != elevations.at(0).size()) {
            throw std::invalid_argument("processRoutes: Invalid elevations vector");
        }
     }

     if(image.empty()||image.at(0).empty()) {
        throw std::invalid_argument("processRoutes: Invalid image vector");
    }
    if (image.size() == 1) {
        throw std::invalid_argument("processRoutes: Invalid image vector");
    }
    for(unsigned int i = 0; i < image.size(); i++) {
        if (image.at(i).size() != image.at(0).size()) {
            throw std::invalid_argument("processRoutes: Invalid image vector");
        }
     }

     if(colorAll.r < 0 || colorAll.r > 255 || colorAll.g < 0 || colorAll.g > 255 || colorAll.b < 0 || colorAll.b > 255 || colorMin.r < 0 || colorMin.r > 255 || colorMin.g < 0 || colorMin.g > 255 || colorMin.b < 0 || colorMin.b > 255) {
        throw std::invalid_argument("processRoutes: Invalid Pixel");
     }

     size_t rows = image.at(0).size();
     size_t cols = image.size();
     vector<int> distances;
     int distance = 0;
     for (int i=0; i < rows; i++) {
        distance = colorRoute(image, elevations, colorAll, i);
        distances.push_back(distance);
     }
    int shortestDistance = INT_MAX;
    int shortestDistanceRow = 0;
     for(int j=0; j < distances.size(); j++) {
        if (distances.at(j) < shortestDistance) {
            shortestDistance = distances.at(j);
            shortestDistanceRow = j;
        }
     }

     colorRoute(image, elevations, colorMin, shortestDistanceRow);


}

int colorRoute(vector<vector<Pixel> >& image, const vector<vector<unsigned int> >& elevations, Pixel color, int startRow) {
        if(elevations.empty()) {
        throw std::invalid_argument("colorRoute: Invalid elevations vector");
    }
    if (elevations.size() == 1) {
        throw std::invalid_argument("colorRoute: Invalid elevations vector");
    }
    
     for(unsigned int k = 0; k < elevations.size(); k++) {
        if (elevations.at(k).size() != elevations.at(0).size()) {
            throw std::invalid_argument("colorRoute: Invalid elevations vector");
        }
     }

     if(image.empty()||image.at(0).empty()) {
        throw std::invalid_argument("colorRoute: Invalid image vector");
    }
    if (image.size() == 1) {
        throw std::invalid_argument("colorRoute: Invalid image vector");
    }
    for(unsigned int i = 0; i < image.size(); i++) {
        if (image.at(i).size() != image.at(0).size()) {
            throw std::invalid_argument("colorRoute: Invalid image vector");
        }
     }

     if(color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255 || color.b < 0 || color.b > 255) {
        throw std::invalid_argument("colorRoute: Invalid Pixel");
     }

    Pixel initialize = {0,0,0};
    vector<vector<Pixel> > reverseImage(image.at(0).size(), vector<Pixel>(image.size(),initialize));
    for (int i = 0; i < image.size(); i++) {
        vector<Pixel> row;
        for(int j = 0; j < image.at(i).size(); j++) {
            reverseImage.at(j).at(i) = image.at(i).at(j);
        }
    }
    image = reverseImage;

    size_t rows = elevations.size();
    size_t cols = elevations.at(0).size();


    unsigned int totalDistance = 0;
    size_t currentRow = startRow;

   
    image.at(currentRow).at(0) = color;

    for (size_t c = 0; c < cols - 1; ++c) {
        int nextRow = currentRow;
        int minChange = INT_MAX;  

    
        int straightChange = std::abs(static_cast<int>(elevations.at(currentRow).at(c + 1)) - static_cast<int>(elevations.at(currentRow).at(c)));

        int upChange;
        if (currentRow > 0) {
            upChange = std::abs(static_cast<int>(elevations.at(currentRow - 1).at(c + 1)) - static_cast<int>(elevations.at(currentRow).at(c)));
        } else {
            upChange = INT_MAX;
        }

        int downChange;
        if (currentRow < rows - 1) {
            downChange = std::abs(static_cast<int>(elevations.at(currentRow + 1).at(c + 1)) - static_cast<int>(elevations.at(currentRow).at(c)));
        } else {
            downChange = INT_MAX;
        }

    
        if ((upChange < downChange) && (upChange < straightChange)) {
            minChange = upChange;
            nextRow = currentRow - 1;
        }
    
        else if ((downChange < upChange) && (downChange < straightChange)) {
            minChange = downChange;
            nextRow = currentRow + 1;
        }
 
        else if ((straightChange < upChange) && (straightChange < downChange)) {
            minChange = straightChange;
            nextRow = currentRow;
        }

        else if (straightChange ==  upChange && straightChange == downChange) {
            minChange = downChange;
            nextRow = currentRow + 1;
        }
        else if (upChange == downChange && upChange < straightChange) {
            minChange = downChange;
            nextRow = currentRow + 1;
        }
        else if (straightChange == downChange && straightChange < upChange) {
            minChange = downChange;
            nextRow = currentRow +1;
        }

        else if (upChange == straightChange && straightChange < downChange) {
            minChange = straightChange;
            nextRow = currentRow;
        }

        else {
            minChange = straightChange;
            nextRow =  currentRow;
        }

   
        totalDistance += minChange;


        currentRow = nextRow;


        image.at(currentRow).at(c + 1) = color;
    }

    Pixel initialize2 = {0,0,0};
    vector<vector<Pixel> > reverseImageBack(image.at(0).size(), vector<Pixel>(image.size(),initialize2));
    for (int i = 0; i < image.size(); i++) {
        vector<Pixel> row;
        for(int j = 0; j < image.at(i).size(); j++) {
            reverseImageBack.at(j).at(i) = image.at(i).at(j);
        }
    }
    image = reverseImageBack;

   
    return totalDistance;
     }

