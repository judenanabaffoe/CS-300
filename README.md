CS-300: Data Structures and Algorithms Portfolio
This repository contains the algorithmic solutions and data structure analysis developed for the ABCU Advising Assistance Program.
Project Overviews
•	Project One Analysis: A comprehensive evaluation of computational complexity (Big O) and memory utilization for various data structures (Vectors, Hash Tables, and Trees).
•	Project Two Implementation: A functional C++ application utilizing a Binary Search Tree (BST) to store, sort, and search course information in alphanumeric order.

Reflection

1. The Problem
The core problem was developing a robust "Advising Assistance" system for ABCU. The system needed to ingest a large volume of course data (including prerequisites), store it efficiently, and allow advisors to print a sorted list of all courses or search for specific course details instantly. The challenge was ensuring the system remained performant as the number of courses scaled.

2. Approach and Importance of Data Structures
I approached the problem by evaluating the trade-offs between different structures. Data structures are critical because they dictate the efficiency of an application. For Project Two, I implemented a Binary Search Tree (BST). This was chosen over a simple Vector because a BST allows for $O(\log n)$ search time and $O(n)$ in-order traversal, which inherently sorts the data. Understanding these structures is the difference between an application that crashes under load and one that scales seamlessly.

3. Overcoming Roadblocks
A major roadblock I encountered was managing the recursive logic for the in-order traversal and the prerequisite lookup. In the Search function, I had to ensure that if a course had multiple prerequisites, the system would not only list the ID but also fetch the corresponding title from the tree. I overcame this by implementing a recursive destroyRecursive method for memory management and refining the Search logic to handle empty or complex prerequisite vectors without causing segmentation faults.

4. Expansion of Software Design
This project expanded my design approach by shifting my focus from "just making it work" to "making it efficient." I now start the design phase by identifying the primary operations—such as frequency of searches versus frequency of inserts—to choose the most appropriate algorithm. It taught me to view software through the lens of Big O notation, ensuring that the backend logic is optimized before the first line of code is written.

5. Maintainability, Readability, and Adaptability
My work evolved to prioritize industry-standard practices. In my ProjectTwo.cpp file, I utilized:
•	Modular Design: Separating the Node structure, Course object, and BinarySearchTree class.
•	Memory Management: Implementing a destructor with recursive cleanup to prevent memory leaks.
•	Code Clarity: Using descriptive variable names and consistent commenting so that the program is adaptable for future developers who might need to integrate a different data source or user interface.

