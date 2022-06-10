#include "data.h"

const string Data::RCC = "Riverside City College";
const string Data::RCC_CONTENT =
        "Welcome to RCC! What discipline would you like to ask? Two possible "
        "ones "
        "are 'Computer Science' and 'Computer Engineering':";

const string Data::CS = "Computer Science";
const vector<string> Data::CS_KEYWORDS = {"Science", "Computer Science"};
const string Data::CS_CONTENT =
        "Computer Science, the study of computers and computing, including their "
        "theoretical and algorithmic foundations, hardware and software, and their "
        "uses for processing information. The discipline of computer science "
        "includes the study of algorithms and data structures, computer and "
        "network design, modeling data and information processes, and artificial "
        "intelligence. Computer science draws some of its foundations from "
        "mathematics and engineering and therefore incorporates techniques from "
        "areas such as queueing theory, probability and statistics, and electronic "
        "circuit design. Computer science also makes heavy use of hypothesis "
        "testing and experimentation during the conceptualization, design, "
        "measurement, and refinement of new algorithms, information structures, "
        "and computer architectures.\nWithin this major, RCC is currently "
        "offering 'Computer Networking' and 'Algorithm & Data Structure.' Which "
        "course you would like to study?";

const string Data::CE = "Computer Engineering";
const vector<string> Data::CE_KEYWORDS = {"Engineer", "Engineering",
    "Computer Engineering"};
const string Data::CE_CONTENT =
        "Computer Engineering is defined as the discipline that embodies the "
        "science "
        "and technology of design, construction, implementation, and maintenance "
        "of "
        "software and hardware components of modern computing systems and "
        "computer-controlled equipment. Computer engineering has traditionally "
        "been "
        "viewed as a combination of both computer science (CS) and electrical "
        "engineering (EE). It has evolved over the past three decades as a "
        "separate, "
        "although intimately related, discipline. Computer engineering is solidly "
        "grounded in the theories and principles of computing, mathematics, "
        "science, "
        "and engineering and it applies these theories and principles to solve "
        "technical problems through the design of computing hardware, software, "
        "networks, and processes.\nWithin this major, RCC is currently "
        "offering 'Software Engineering' and 'Control System Engineering.' Which "
        "course you would like to study?";

const string Data::CS_NET = "Computer Networking";
const vector<string> Data::CS_NET_KEYWORDS = {
    "Computer", "Network", "Networking", "Computer Networking"
};
const string Data::CS_NET_CONTENT =
        "Computer Networking refers to connected computing devices (such as "
        "laptops, desktops, servers, smartphones, and tablets) and an "
        "ever-expanding array of IoT devices (such as cameras, door locks, "
        "doorbells, refrigerators, audio/visual systems, thermostats, and various "
        "sensors) that communicate with one another.";

const string Data::CS_AL_DT = "Algorithm & Data Structure";
const vector<string> Data::CS_AL_DT_KEYWORDS = {"Algorithm", "Data Structure",
    "Algorithm & Data Structure",
    "Algorithm and Data Structure"};
const string Data::CS_AL_DT_CONTENT =
        "Informally, an algorithm is any well-defined computational procedure that "
        "takes some value, or set of values, as input and produces some value, or "
        "set of values, as output. An algorithm is thus a sequence of "
        "computational steps that transform the input into the output.\nA data "
        "structure is a specialized format for organizing, processing, retrieving "
        "and storing data. There are several basic and advanced types of data "
        "structures, all designed to arrange data to suit a specific purpose. Data "
        "structures make it easy for users to access and work with the data they "
        "need in appropriate ways.";

const string Data::CE_SE = "Software Engineering";
const vector<string> Data::CE_SE_KEYWORDS = {"Software",
    "Software Engineering"};
const string Data::CE_SE_CONTENT =
        "Software Engineering can be considered as a branch of computer science "
        "that deals with "
        "the design, development, testing, and maintenance of software "
        "applications. Software engineers apply engineering principles and "
        "knowledge of programming languages to build software solutions for end "
        "users.";

const string Data::CE_CSE = "Control System Engineering";
const vector<string> Data::CE_CSE_KEYWORDS = {
    "Control", "System", "Control System", "Control System Engineering"
};
const string Data::CE_CSE_CONTENT =
        "Control System Engineering: system modeling and performance "
        "specifications of dynamic systems. Design "
        "and analysis of linear time invariant feedback control systems via root "
        "locus and frequency response compensation techniques.";

const string Data::FINAL_OPTIONS =
        "Would you like to restart this chat session, to search for a professor, or to terminate "
        "it? Please type 'restart' for the first option. Or please enter the professor's initials (e.g.,'LM' for Prof Lehr, Mark)"
        ". Otherwise please hit enter to exit the program.";