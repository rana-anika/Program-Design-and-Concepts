#include <iostream>
#include <sstream>
#include <limits>
#include "functions.h"

using std::cout, std::cin, std::endl, std::exception, std::invalid_argument; 
using std::getline, std::string;


int main () { 
    LinkedList list;
    string line;
    bool verbose = false;
    
    if (verbose) print_inst_2();
    if (verbose) print_inst_1();
    getline (cin, line);    
    while (!line.empty()) {
        string operation;
        string location;
        int mapped_loc;

        get_op (line, &operation);
        if (operation == "insert" || operation == "add"){
            int insert_location = 0; 
            getline (cin, line);
            get_loc (line, &location);
            mapped_loc = mapping(location);
            if (mapped_loc != 0) { 
                if (list.link_list_empty()) {
                    {list.push(mapped_loc);}
                }
                else {
                    insert_location = list.find_closest_less_than(mapped_loc);
                    if (insert_location != 0) {
                        list.insertNode(mapped_loc, insert_location);
                    }
                    else { list.push(mapped_loc); } // if adding first location then insert_location is 0 (default)
                }
            }
        }
        else if (operation == "delete" || operation == "remove"){
            getline (cin, line);
            get_loc (line, &location);
            mapped_loc = mapping(location);
            if (mapped_loc != 0) { 
                if (list.link_list_empty()) {
                    // do nothing
                }
                else {
                    if (mapped_loc != 0) {
                        list.deleteNode(mapped_loc);
                    }
                    else { // do nothing 
                    } 
                }
            }
        }
        else if (operation == "push"){
            getline (cin, line);
            get_loc (line, &location);
            mapped_loc = mapping(location);
            if (mapped_loc != 0) {list.push(mapped_loc);}
        }
        else if (operation == "pop"){
            list.pop();
        }
        else if (operation == "clear"){
            list.~LinkedList();            
        }
        else if (operation == "print"){
            list.printLinkedList();
        }
        else if (operation == "locations") {
            if (verbose) print_inst_2();
        }
        else if (operation == "duplicate") {
            LinkedList B;
            B = list;
            B.printLinkedList();
        }
        else if (operation == "quit") {
            break;
        }
        else {
            cout << "operation type undefined, re-enter operation" << endl;
        }    
        if (verbose) print_inst_3();
        getline (cin, line);
    }
    return 0;
}
