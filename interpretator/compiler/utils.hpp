#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace interpreter {
    class utils {
    public:

        static string getFileContents(string filePath) {
            ifstream inFile;
            inFile.open(filePath); //open the input file

            stringstream strStream;
            strStream << inFile.rdbuf(); //read the file
            return strStream.str();
        }

        // trim from start (in place)
        static inline void ltrim(std::string &s) {
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
        }

        // trim from end (in place)
        static inline void rtrim(std::string &s) {
            s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), s.end());
        }

        // trim from both ends (in place)
        static inline void trim(std::string &s) {
            ltrim(s);
            rtrim(s);
        }


        // Function to in-place trim all spaces in the
        // string such that all words should contain only
        // a single space between them.
        static void removeSpaces(string &str) {
            // n is length of the original string
            int n = str.length();

            // i points to next position to be filled in
            // output string/ j points to next character
            // in the original string
            int i = 0, j = -1;

            // flag that sets to true is space is found
            bool spaceFound = false;

            // Handles leading spaces
            while (++j < n && str[j] == ' ');

            // read all characters of original string
            while (j < n) {
                // if current characters is non-space
                if (str[j] != ' ') {
                    // remove preceding spaces before dot,
                    // comma & question mark
                    if ((str[j] == '.' || str[j] == ',' ||
                         str[j] == '?') && i - 1 >= 0 &&
                        str[i - 1] == ' ')
                        str[i - 1] = str[j++];

                    else
                        // copy current character at index i
                        // and increment both i and j
                        str[i++] = str[j++];

                    // set space flag to false when any
                    // non-space character is found
                    spaceFound = false;
                }
                    // if current character is a space
                else if (str[j++] == ' ') {
                    // If space is encountered for the first
                    // time after a word, put one space in the
                    // output and set space flag to true
                    if (!spaceFound) {
                        str[i++] = ' ';
                        spaceFound = true;
                    }
                }
            }
        }

        static void replaceAll(std::string &str, const std::string &from, const std::string &to) {
            size_t start_pos = 0;
            while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
                str.replace(start_pos, from.length(), to);
                start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
            }
        }

        static void print(const std::string &message) {
            std::cout << message << endl;
        }

    };
}