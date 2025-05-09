/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <vector>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    std::vector<std::vector<std::string>> res;
    std::string csv = file_to_string(filename);
    std::vector<std::string> lines;
    SplitString(csv, '\n', lines);
    for (std::string l : lines) {
        std::vector<std::string> inner;
        SplitString(l, ',', inner);
        std::vector<std::string> vectorized;
        for (std::string w : inner) {
            std::string first = TrimLeft(w);
            vectorized.push_back(first);
        }
        res.push_back(vectorized);
    }
    return res;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE
    std::map<std::string, std::vector<std::string>> validStudents;
    std::vector<std::vector<std::string>> res;
    //creating valid students
    for (auto v : student) {
        std::vector<std::string> classes;
        for (unsigned i = 1; i < v.size(); i++) {
            classes.push_back(v[i]);
        }
        validStudents.insert({v[0], classes});
    }

    for (unsigned l = 0; l < cv.size(); l++) {
        bool valid = true;
        std::vector<std::string> fixedLine;
        std::string course = cv[l][0];
        for (unsigned i = 1; i < cv[l].size(); i++) {
            if (validStudents.count(cv[l][i])) {
                std::vector<std::string> check = validStudents[cv[l][i]];
                if (std::find(check.begin(), check.end(), course) != check.end()) {
                    if (std::find(fixedLine.begin(), fixedLine.end(), cv[l][i]) == fixedLine.end()) {
                        if (valid) {
                            fixedLine.push_back(course);
                            valid = false;
                        }
                        fixedLine.push_back(cv[l][i]);
                    }
                } 
            } 
        }
        if (fixedLine.size() != 0) {
            res.push_back(fixedLine);
        }
    }
    return res;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */

 //time slots are the colors
 //we now need to change to keep checking with differen possible nodes
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots) {
    bool finished = false;
    std::vector<std::vector<std::string>> res;
    std::map<std::string, std::vector<std::string>> graph = createGraph(courses);
    std::map<std::string, std::string> colorMappings;
    for (unsigned x = 0; x < courses.size(); x++) {
        colorMappings.insert({courses[x][0], timeslots[0]});

        std::map<std::string, bool> available;
        available.insert({timeslots[0],true});

        for (unsigned i = 0; i < courses.size(); i++) {
            if (i != x) {
                colorMappings.insert({courses[i][0], "-1"});
            }
        }
        for (unsigned i = 1; i < timeslots.size(); i++) {
            available.insert({timeslots[i], false});
        }
        
        // Assign colors to remaining V-1 vertices
        for (unsigned u = 0; u < courses.size(); u++) {
            if (u != x) {
                std::vector<std::string>::iterator i;
                std::vector<std::string> adj = graph.at(courses[u][0]);
                for (i = adj.begin(); i != adj.end(); ++i) {
                    if (colorMappings.at(*i) != "-1") {
                        available.at(colorMappings.at(*i)) = true;
                    }
                }
                unsigned cr;
                for (cr = 0; cr < timeslots.size(); cr++) {
                    if (available.at(timeslots[cr]) == false) {
                        break;
                    }
                }
                if (cr < timeslots.size()) {
                    colorMappings.at(courses[u][0]) = timeslots[cr];
                    for (i = adj.begin(); i != adj.end(); ++i) {
                        if (colorMappings.at(*i) != "-1") {
                            available.at(colorMappings.at(*i)) = false;
                        }
                    }
                }
            }
        }
        bool redo = true;
        for (unsigned i = 0; i < courses.size(); i++) {
            if (colorMappings.at(courses[i][0]) == "-1") {
                redo = false;
            }
        }
        if (redo) {
            finished = true;
            break;
        }
        std::map<std::string, std::string> newMap;
        colorMappings = newMap;
    }
    if (!finished) {
        std::vector<std::vector<std::string>> failed;
        std::vector<std::string> inside;
        inside.push_back("-1");
        failed.push_back(inside);
        return failed;
    }
    for (unsigned i = 0; i < timeslots.size(); i++) {
        std::vector<std::string> inner;
        inner.push_back(timeslots[i]);
        for (unsigned y = 0; y < courses.size(); y++) {
            std::string time = colorMappings.at(courses[y][0]);
            if (time == timeslots[i]) {
                inner.push_back(courses[y][0]);
            }
        }
        res.push_back(inner);
    }
    std::cout << std::endl;
    return res;
}

//make a graph with vertices being classes and edges being if they share a student or not
std::map<std::string, std::vector<std::string>> createMap(V2D list) {
    std::map<std::string, std::vector<std::string>> res;
    for (unsigned i = 0; i < list.size(); i++) {
        std::string course = list[i][0];
        std::vector<std::string> inner;
        for (unsigned j = 1; j < list[i].size(); j++) {
            inner.push_back(list[i][j]);
        }
        res.insert({course, inner});
    }
    return res;
}


std::map<std::string, std::vector<std::string>> createGraph(V2D list) {
    std::map<std::string, std::vector<std::string>> classes = createMap(list);
    std::map<std::string, std::vector<std::string>> res;
    for (unsigned i = 0; i < list.size(); i++) {
        std::string course = list[i][0];
        std::vector<std::string> s1 = classes[course];
        std::vector<std::string> connections;
        for (unsigned j = 0; j < list.size(); j++) {
            if (i != j) {
                std::vector<std::string> s2 = classes.at(list[j][0]);
                if (intersection(s1, s2)) {
                    connections.push_back(list[j][0]);
                }
            }
        }
        res.insert({course, connections});
    }
    return res;
}

bool intersection(std::vector<std::string> v1, std::vector<std::string> v2) {
    // std::sort(v1.begin(), v1.end());
    // std::sort(v2.begin(), v2.end());
    for (unsigned i = 0; i < v1.size(); i++) {
        for (unsigned j = 0; j < v2.size(); j++) {
            if (v2[j] == v1[i]) {
                return true;
            }
        }
    }
    return false;
}

    //std::map<std::string, std::vector<std::string>> timesMap;


    // int result[V];
  
    // // Assign the first color to first vertex
    // result[0]  = 0;
  
    // // Initialize remaining V-1 vertices as unassigned
    // for (int u = 1; u < V; u++)
    //     result[u] = -1;  // no color is assigned to u
  
  // A temporary array to store the available colors. True
    // value of available[cr] would mean that the color cr is
    // assigned to one of its adjacent vertices
    

    // bool available[V];
    // for (int cr = 0; cr < V; cr++)
    //     available[cr] = false;
  

          //std::string insert = timeslots[i] + ", ";
        //res.push_back(insert);

            //std::string start = timeslots[0] + ", " + course[0][0];
    //res.push_back(start);



    // std::cout << "CLASS LIST" << std::endl;
    // for (unsigned i = 0; i < courses.size(); i++) {
    //     for (unsigned j = 0; j < courses[i].size(); j++) {
    //         std::cout << courses[i][j] << ", ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << std::endl;
    // std::cout << "ADJACENT LIST" << std::endl;
    // for (unsigned i = 0; i < courseList.size(); i++) {
    //     std::vector<std::string> adj = graph.at(courseList[i]);
    //     std::cout << courseList[i] << " is adjacent to the following:" << std::endl;
    //     for (unsigned j = 0; j < adj.size(); j++) {
    //         std::cout << adj[j] << ", ";
    //     }
    //     std::cout << std::endl;
    // }


        // for (unsigned i = 0; i < courses.size(); i++) {
    //     std::string time = colorMappings.at(courses[i][0]);
    //     if (timesMap.count(time)) {
    //         std::vector<std::string> c = timesMap[time];
    //         c.push_back(courses[i][0]);
    //         timesMap.at(time) = c;
    //     } else {
    //         std::vector<std::string> c;
    //         c.push_back(courses[i][0]);
    //         timesMap.insert({time, c});
    //     }
    // }

    // for (unsigned i = 0; i < timeslots.size(); i++) {
    //     std::vector<std::string> inner;
    //     inner.push_back(timeslots[i]);
    //     if (timesMap.count(timeslots[i])) {
    //         std::vector<std::string> adj = timesMap[timeslots[i]];
    //         for (unsigned j = 0; j < adj.size(); j++) {
    //             inner.push_back(adj[j]);
    //         }
    //     }
    //     res.push_back(inner);
    // }