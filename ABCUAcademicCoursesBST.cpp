/*
==================================================
University of South New Hampshire
Professor       : Mais Nijim
Student         : Mohamed Fahim El-Hewie
Date            : June 18 2026
Class           : CS 300 DSA Analysis and Design
Module          : 7-1 Project Two
==================================================
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// Define a structure to hold data for individual course objects
struct Course {                     // object Course has three variables to hold data
    string courseNum;               // variable holds course identifier data
    string courseTitle;             // variable holds course title
    vector<string> prereqs;         // dynamic array holds list of prerequisites
};

// Internal structure for the Binary Search Tree node
struct Node {                   // object Node has content and two pointers pointing to two children
    Course nodeCourse;          // nodeCourse is data stored at Node in the form of structure Course
    Node* left;
    Node* right;

    /*
    * Constructor initializes node contents as aCourse, left pointer as null, right pointer as null
    * Node has no children, yet has content aCourse
    */
     
    Node(Course aCourse) : nodeCourse(aCourse), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class definition
class BinarySearchTree {                // Object BST contains data on scattered nodes connected by pointers
private:
    Node* root;                         // pointer root anchors the BST at a starting point 
                                        // or node to start a tree of data structure

    void delTree(Node* node) {          // delete children and node if node has content
        if (node != nullptr) {
            delTree(node->left);        // recursive operation conceals the traversal process on left subtree
                                        // that ends when node has null left child 
            delTree(node->right);       // recursive operation on right subtree starts after left subtree is traversed
            delete node;                // node is only deleted when both right and left children are null
        }
    }

    Node* insert(Node* node, Course aCourse) {      // function inserts pointer to node and content of structure 
        if (node == nullptr) {
            return new Node(aCourse);               // new node created with content "aCourse"
        }
        // BST alphanumeric sort order: lowest to highest based on courseNum
        if (aCourse.courseNum < node->nodeCourse.courseNum) {
            node->left = insert(node->left, aCourse);       // insert in left child based on value of class identifier
        } 
        else {
            node->right = insert(node->right, aCourse);     // insert in right child if class number is greater than node content
        }
        return node;        // returned node has new child inserted based on courseNumber
    }

    /*
    * In-order traversal naturally prints data in sorted alphanumeric order
    * Function inOrder() poses difficulty when analyzed due to the recursive operation on pointing to 
    * successive left child of current node. Function starts by a node, checks a non-null status,
    * if node is non-null, then replaces node by left child as successive node, repeats until
    * a null child is found, then prints the content of childless node.
    * Right shift happens after last left childless node is located.
    * Function returns handle to original caller when a right node is found null.
    */
    void inOrder(Node* node) {         // inOrder traverses nodes along a map of pointers
                                       // it only needs a node to start traversal
        if (node != nullptr) {
            inOrder(node->left);    // recursive loop traverses entire left subtree, exit at null

            cout << "            " << node->nodeCourse.courseNum << ": " << node->nodeCourse.courseTitle << "\n";

            inOrder(node->right);   // only executed after left subtree traversed to leaves or null
        }
    }
    /* 
    * Unlike function inOrder() that returns void, function search() returns an object Node that holds object Course
    * in addition to Node's pointers and dynamic array of prerequisites. Function search() requires a course identifier to 
    * locate and a node in a tree to start searching.
    */
    Node* search(Node* node, string courseNum) {  
                                                    
        if (node == nullptr || node->nodeCourse.courseNum == courseNum) {
            return node;        // This is the only return to original caller after all recursive operations.
                                // returned node either has no data or has matching data of searched and existing 
                                // course number. nodeCourse exists at that node with its identifier. courseNum is
                                // the sought identifier that matches existing data on node.
        }
        if (courseNum < node->nodeCourse.courseNum) {   // sought identifier courseNum is compared to existing nodeCourse ID
            return search(node->left, courseNum);       // this a tricky return because it begins a recursive search on left
                                                        // subtree that continues until a match is found and returned to 
                                                        // original caller
        }
        return search(node->right, courseNum);          // if search on left subtree fails to return to original caller
                                                        // recursive search resumes on right subtree.
    }

    /*
    * In order to validate prerequisites as existing courses, the scattered nodes are collected in a temporary 
    * dynamic array courseList. The recursive structure renders analysis troublesome. Recursion on left subtree
    * must conclude by a null left child before reaching the push_back at end of the dynamic array. The original 
    * node is successively shifting to left child of current node, until a childless node is located
    * its content pushed back in the vector sourseList.  
    */

    void collectCourses(Node* node, vector<Course>& courseList) const {
        if (node != nullptr) {
            collectCourses(node->left, courseList);     // node shifts to left pointer for recursion on left subtree

            courseList.push_back(node->nodeCourse);     // left childless node arrives at push_back in vector array

            collectCourses(node->right, courseList);    // right shift occurs when null left child is located.
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}           // Constructor initiates a tree with empty root.

    ~BinarySearchTree() {                           // Destructor frees resources by recursive node deletion operations.
        delTree(root);
    }

    /* 
    * Deletion of tree nodes by delTree() requires re-allocation of the root pointer
    * assign root to nullptr, after all nodes are deleted, implies a new tree is ready anew for construction
    * with allocated root, pointing to no children.
    */
    void BSTClear() {
        delTree(root);
        root = nullptr;
    }
    /*
     Helper function implements insert object aCourse in a tree of specified root.
     */

    void BSTInsert(Course aCourse) {
        root = insert(root, aCourse);
    }
    /* 
    Helper function implements in-order traversal of data tree structure
    It starts at the root pointer
    */
    void BSTInOrder() {
        inOrder(root);
    }
/*
* Helper function BSTSearch() implements the search function on course identifier courseNum
* If a match found with sought courseNum equal existing nodeCourse's number, search returns node
* named current. A non-null pointer current signified a found match, returns nodeCourse object.
* nodeCourse object contains the three members: title, number, and array of prerequisites.
*/
    Course BSTSearch(string courseNum) {

        Node* current = search(root, courseNum);
        if (current != nullptr) {
            return current->nodeCourse;     // match found between courseNum and existing course number
                                            // on node current's content: nodeCourse.courseNum
        }
        return Course(); // Return empty course structure if not found
    }

    bool IsEmpty() const {
        return root == nullptr;
    }
    /*
    * Validates that all prerequisites against registered course numbers
    * It has three iteration loops. One loops on courses in temporary dynamic array.
    * Another loops on prerequisites in every course.
    * Third loops on matching prerequisites with course numbers
    */
    bool ValidatePrereqs() const {

        vector<Course> allCourses;          // create temporary dynamic array to hold all courses
                                            // for the purpose of matching prerequisites 
        collectCourses(root, allCourses);

        bool vettedPrereq = true;
        for (const auto& course : allCourses) {             // Loops through every course in array allCourses
            for (const auto& prereq : course.prereqs) {     // Iterates through prerequisites in specific course
                bool found = false;
                for (const auto& target : allCourses) {     // Searches for a match of prerequisites
                    if (target.courseNum == prereq) {
                        found = true;
                        break;          // exits inner loop if match found
                    }
                }
                if (!found) {
                    cout << "            Data Warning: Prerequisite '" << prereq 
                              << "' for course " << course.courseNum 
                              << " does not exist in the course list.\n";

                    vettedPrereq = false;
                }   // end of matching loop
            }       // end of searching prerequisites per courses
        }           // end of searching courses in array of courses
        return vettedPrereq        ;
    }
};

// Helper function to convert a string to uppercase for clean, uniform mapping
string toUpperCase(string str) {

    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
        return toupper(c);
        }
    );
    return str;     // str is the reassembled string of capitalized characters.
} 
/*
[1]: Prompts user for the file name and parses data straight into the BST
Function loadData() takes a single argument "coursesList"
coursesList is a vector datatype or dynamic array, that consists of course objects
Passing changes by reference "&" implies local changes propagate by reference without
passing a list of changes
*/
void loadData(BinarySearchTree& bst) {

    string filePath;
    cout << "            Enter the file name containing the course data: " << endl << endl;
    cout << "            e.g. CS 300 ABCU_Advising_Program_Input.csv " << endl << endl
        << "                        :";

    cin.ignore();                        // clears leftover new line
    getline(cin, filePath);              // reads whole string includin spaces


    ifstream file(filePath);            // create input file stream named file with path filePath

    if (!file.is_open()) {              // function is_open() applies to ifstream objects
        cout << "            Error: File '" << filePath << "' could not be opened. Verify the path.\n";
        return;
    }

    bst.BSTClear();                // starting binary search tree from scratch
    string line;                   // create place holder for a line string
    int count = 0;

    /*=================================================
    Loop read on lines in file stream
    *=================================================*/
    while (getline(file, line)) {           // read input stream file and place it in string line
        if (line.empty()) {
            continue;                       // skip an empty line
        }

        stringstream strStream(line);       // initiate object stringStream for parsing operations on string line
        string token;
        vector<string> tokenList;           // create place holder for strings of a line

       
        /**=================================================
        Loop on chunks of strings in each line, separated by comma delimiters
        Construct dynamic array tokenList to hold line tokens
        *=================================================*/        
        while (getline(strStream, token, ',')) {
            // Trim whitespace variations if necessary
            tokenList.push_back(token);
        }

        if (tokenList.size() < 2) {     // at minimum a course must have a number and a title, that is 2.
            cout << "            Skipping incomplete data row: " << line << "\n";
            continue;
        }

        Course course;
        course.courseNum = toUpperCase(tokenList[0]); // Normalize keys to upper-case
        course.courseTitle = tokenList[1];

        /**=================================================
        Loop on each line tokes to collect prerequisites starting from third token
        Construct the array of course prerequisites
        *=================================================*/
        for (size_t i = 2; i < tokenList.size(); ++i) {
            if (!tokenList[i].empty()) {
                course.prereqs.push_back(toUpperCase(tokenList[i]));
            }
        }
        /*
        BST is constructed by inserting courses and passed by reference "&"
        */
        bst.BSTInsert(course);         // function insert() creates a node in the bst to hold the course object
        count++;
    }

    file.close();       // release resources by closing file, return handle to OS
    cout << "                  ============================================================" << endl;
    cout << "            Successfully loaded " << count << " courses into the BST data structure.\n";
    cout << "                  ============================================================" << endl;
    // Perform required validation
    bst.ValidatePrereqs();
}

// [2] Performs in-order tree traversal to output alphanumeric elements directly
void printCourseList(BinarySearchTree& bst) {       // print all courses function access the binary search tree by reference "&"
    if (bst.IsEmpty()) {
        cout << "            Error: No data available. Please load file data first (Option 1).\n";
        return;
    }
    cout << "            ============================================================" << endl;
    cout << "\n            --- Alphanumeric Program Course List ---\n";
    cout << "            ============================================================" << endl;
    bst.BSTInOrder();          // function BSTInOrder() prints courses alphanumerically
    cout << "            ============================================================" << endl;
}

// [3] Tree searching to reveal matching items along with respective structural text attributes
void printCourseInfo(BinarySearchTree& bst) {
    if (bst.IsEmpty()) {
        cout << "            Error: No data available. Please load file data first (Option 1).\n";
        return;                         // if bst has no nodes, it has no data to print
    }

    string searchNum;                   // place holder of user input for search number
    cout << "            Enter the course number to look up: ";
    cin >> searchNum;

    string upperCaseNum = toUpperCase(searchNum);       // function toUpperCase() removes case sensitivity by capitalizing characters
    Course aCourse = bst.BSTSearch(upperCaseNum);          // function search() works on bst to locate course object

    if (aCourse.courseNum.empty()) {                    // if structure of object has no course number, the course does not exist in tree
        cout << "            Error: Course number '" << searchNum 
            << "' was not found in the system.\n";
        return;
    }

    cout << "            ============================================================" << endl;
    cout << "\n            Course Title: " << aCourse.courseTitle << "\n";
    cout << "            Prerequisites: " << endl;

    if (aCourse.prereqs.empty()) {                    // object aCourse has been located by function search()
        cout << "None\n";
    } else {
        for (size_t i = 0; i < aCourse.prereqs.size(); ++i) {
            string prereqNum = aCourse.prereqs[i];
            Course prereqCourse = bst.BSTSearch(prereqNum);  // prerequisite is declareds as an object Class in order to retrieve its title
            string prereqTitle = prereqCourse.courseNum.empty() ? "No Title" : prereqCourse.courseTitle;

            cout << "            " << prereqNum << " (" << prereqTitle << ")";

            if (i < aCourse.prereqs.size() - 1) {
                cout << endl;
            }
        }
        cout << "\n";
    }
    cout << "            ============================================================" << endl;
}
/*
* Main driving function providing user controls loop and menu display parameters
*/

int main() {

    /*
    * Binary Tree Data structure comprises the core concept of this code. It stores structure objects
    * in nodes, connected by pointers, arranged between tree root and tree leaves, according to binary
    * rules right > node > left. The BST structure is governed by methods defined in: insert, remove, search
    * inOrder, preOrder, postOrder, and destructor.
    * Pointers user extra resources as variables used to localize nodes.
    * The scattered, yet connected, nodes preclude shifting the entire array of objects when inserting
    * of removing nodes, thus balances the lost resources of pointers by gained resources of undisturbed
    * static arrays
    */
    BinarySearchTree courseBSTree;  // instantiate data structure BST consisting of root, 
                                    // pointers to nodes, contingent on rules of binary tree structure
    string userInput;               // user input is held as string to be converted later to integer
    int choice = 0;

    cout << "            Welcome to the Academic Advisor Course System!\n";

    while (choice != 9) {           // 9 is an optional choice to allow for expanding the menu if needed
        cout << "            \n            ===== MENU OPTIONS =====\n";
        cout << "            1: Load course data file\n";
        cout << "            2: Print alphanumeric list of all courses\n";
        cout << "            3: Print course title and prerequisites for a specific course\n";
        cout << "            9: Exit the program\n\n\n";
        cout << "            Enter your choice: " << endl;

        cin >> userInput;

        try {
            choice = stoi(userInput);               // stoi convert string to integer
        } catch (const invalid_argument&) {         // exception handling of invalid choice of switch
            choice = 0;                             // reset choice and restart the wile loop
        }
        /*
        * The switch statement is an alternative to nested if-else-if's conditional flow
        * it offers better readability over traditional conditional statements
        * each case corresponds to a value of the parameter choice
        */
        switch (choice) {
            case 1:
                loadData(courseBSTree);
                break;                      // breaks restart the menu at the top of the while block
            case 2:
                printCourseList(courseBSTree);
                break;
            case 3:
                printCourseInfo(courseBSTree);
                break;
            case 9:
                cout << "Thank you for using the Academic Advisor Course System. Goodbye!\n";
                break;
            default:                        // default offer user chances to re-enter valid menu choice
                cout << "Error: '" << userInput << "' is not a valid menu parameter. Please enter 1, 2, 3, or 9.\n";
                break;
        }
    }

    return 0;       // function int main() returns 0 when successfully executed.
}
