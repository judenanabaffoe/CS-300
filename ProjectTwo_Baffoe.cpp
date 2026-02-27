//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Jude Mensah Nana Baffoe
// Course      : CS 300: Data Structures and Algorithms
// Description : ABCU Advising Assistance Program using a Binary Search Tree
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// --- Structure to hold Course information ---
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;

    Course() {}
};

// --- Internal structure for the Tree node ---
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course aCourse) : Node() {
        this->course = aCourse;
    }
};

// --- Binary Search Tree Class ---
class BinarySearchTree {
private:
    Node* root;
    void inOrder(Node* node);
    void destroyRecursive(Node* node);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Course course);
    Course Search(string courseNumber);
};

BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree() {
    destroyRecursive(root);
}

// Memory cleanup for industry standards
void BinarySearchTree::destroyRecursive(Node* node) {
    if (node != nullptr) {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

void BinarySearchTree::InOrder() {
    this->inOrder(root);
}

// BST Insertion logic
void BinarySearchTree::Insert(Course course) {
    if (root == nullptr) {
        root = new Node(course);
    } else {
        Node* curr = root;
        while (curr != nullptr) {
            if (course.courseNumber < curr->course.courseNumber) {
                if (curr->left == nullptr) {
                    curr->left = new Node(course);
                    curr = nullptr;
                } else {
                    curr = curr->left;
                }
            } else {
                if (curr->right == nullptr) {
                    curr->right = new Node(course);
                    curr = nullptr;
                } else {
                    curr = curr->right;
                }
            }
        }
    }
}

// BST Search logic
Course BinarySearchTree::Search(string courseNumber) {
    Node* curr = root;
    while (curr != nullptr) {
        if (curr->course.courseNumber == courseNumber) {
            return curr->course;
        } else if (courseNumber < curr->course.courseNumber) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return Course();
}

void BinarySearchTree::inOrder(Node* node) {
    if (node != nullptr) {
        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.title << endl;
        inOrder(node->right);
    }
}

// --- Helper Functions ---

string toUpperCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

bool loadCourses(string csvPath, BinarySearchTree* bst) {
    ifstream file(csvPath);
    if (!file.is_open()) {
        cout << "Error: File '" << csvPath << "' not found." << endl;
        return false;
    }

    string line;
    int count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        vector<string> tokens;

        while (getline(ss, item, ',')) {
            // Clean up invisible characters (industry standard for CSV parsing)
            item.erase(remove(item.begin(), item.end(), '\r'), item.end());
            item.erase(remove(item.begin(), item.end(), '\n'), item.end());
            if (!item.empty()) tokens.push_back(item);
        }

        // Basic validation: number and title must exist
        if (tokens.size() < 2) continue;

        Course course;
        course.courseNumber = tokens[0];
        course.title = tokens[1];
        for (size_t i = 2; i < tokens.size(); i++) {
            course.prerequisites.push_back(tokens[i]);
        }
        bst->Insert(course);
        count++;
    }
    file.close();
    cout << "Successfully loaded " << count << " courses." << endl;
    return true;
}

int main() {
    BinarySearchTree* bst = new BinarySearchTree();
    string fileName;
    string userCourse;
    int choice = 0;

    cout << "Welcome to the ABCU course planner." << endl << endl;

    while (choice != 9) {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl << endl;
        cout << "What would you like to do? ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter 1, 2, 3, or 9." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                // Rubric Requirement: Prompt for file name
                cout << "Enter the file name containing course data: ";
                cin >> fileName;
                loadCourses(fileName, bst);
                break;

            case 2:
                cout << "Here is a sample schedule:" << endl << endl;
                bst->InOrder();
                break;

            case 3:
                cout << "What course do you want to know about? ";
                cin >> userCourse;
                userCourse = toUpperCase(userCourse);
                {
                    Course found = bst->Search(userCourse);
                    if (!found.courseNumber.empty()) {
                        cout << found.courseNumber << ", " << found.title << endl;
                        cout << "Prerequisites: ";
                        if (found.prerequisites.empty()) {
                            cout << "None";
                        } else {
                            for (size_t i = 0; i < found.prerequisites.size(); i++) {
                                string pNum = found.prerequisites[i];
                                // Rubric Requirement: Look up the title for each prerequisite
                                Course pDetail = bst->Search(pNum);
                                cout << pNum;
                                if (!pDetail.title.empty()) cout << " (" << pDetail.title << ")";
                                if (i < found.prerequisites.size() - 1) cout << ", ";
                            }
                        }
                        cout << endl;
                    } else {
                        cout << "Course " << userCourse << " not found." << endl;
                    }
                }
                break;

            case 9:
                cout << "Thank you for using the course planner!" << endl;
                break;

            default:
                cout << choice << " is not a valid option." << endl;
                break;
        }
        cout << endl;
    }

    delete bst; // Clean up the tree
    return 0;
}