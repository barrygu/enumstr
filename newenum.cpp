#include <iostream>
#include <string>
#include <vector>
#include <map>

/**************************************************
 * TRIM LEFT IN-PLACE
 * s.erase( 0, s.find_first_not_of( delimiters ) );
 * 
 * TRIM LEFT COPY
 * s.substr( s.find_first_not_of( delimiters ) );
 **************************************************/

// http://stackoverflow.com/questions/9150538/how-do-i-tostring-an-enum-in-c
// http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
std::vector<std::string> split(const std::string &text, char sep) {
    std::string s,delimiters = " \t";
    std::vector<std::string> tokens;
    size_t found, start = 0, end = 0;
    while ((end = text.find(sep, start)) != std::string::npos) {
        s = text.substr(start, end - start);

//        std::cout << "untrimmed:" << s << ":" << std::endl;
        found = s.find_first_not_of(delimiters, 0);
        if (found != std::string::npos) s.erase(0, found); // trim left
//        std::cout << "trimmed left:" << s << ":" << std::endl;
        found = s.find_last_not_of(delimiters);
        if (found != std::string::npos) s.erase(found + 1); // trim right
//        std::cout << "trimmed right:" << s << ":" << std::endl;
//        std::cout << std::endl;
        
        tokens.push_back(s);
        start = end + 1;
    }

    s = text.substr(start);
//    std::cout << "untrimmed:" << s << ":" << std::endl;
    found = s.find_first_not_of(delimiters, 0);
    if (found != std::string::npos) s.erase(0, found); // trim left
//    std::cout << "trimmed left:" << s << ":" << std::endl;
    found = s.find_last_not_of(delimiters);
    if (found != std::string::npos) s.erase(found + 1); // trim right
//    std::cout << "trimmed right:" << s << ":" << std::endl;
//    std::cout << std::endl;

    tokens.push_back(s);
    return tokens;
}

#define ENUM(name, ...)\
    typedef enum __eTag_##name\
    {\
        __VA_ARGS__\
    }name;\
    static const int name##Size = (sizeof((int[]){__VA_ARGS__})/sizeof(int));\
    static const vector<string> name##ToStringMap = split(#__VA_ARGS__, ',');\
    const string name##ToString(const name value)\
    {\
        return name##ToStringMap.at(value);\
    };\
    map<string, name> name##ToFromStringMap(...)\
    {\
        map<string, name> m;\
        name args[name##Size] = { __VA_ARGS__ };\
        \
        int i;\
        for(i = 0; i < name##Size; ++i)\
        {\
            m[name##ToString(args[i])] = args[i];\
        }\
        return m;\
    };\
    static map<string, name> name##FromStringMap = name##ToFromStringMap(__VA_ARGS__);\
    const name name##FromString(const string value, const name defaultValue)\
    {\
        if(name##FromStringMap.count(value) == 0)\
        {\
            return defaultValue;\
        }\
        return name##FromStringMap[value];\
    };

using namespace std;

ENUM(MyEnum, Invalid,	Red	, Green   ,   Blue,   Black)

/************************************************************
 * The syntax MyEnum::SomethingElse is a Microsoft extension. 
 * It happens to be one I like, but it's not Standard C++.
 * Indeed, C++0x allows that feature. I could enable it
 * successfully in gcc using this command line flag: -std=c++0x
 ************************************************************/
 
 /***********************************************************
  * If we needn't get value from string, we can cut-off from 
  * map<string, name> name##ToFromStringMap(...)
  ***********************************************************/
 
int main(int argc, char *argv[])
{
    MyEnum value;
    string valueName;
    
    value = MyEnum::Green;
    valueName = MyEnumToString(value);
    std::cout << value << " to string:" << valueName << std::endl;

    value = MyEnum::Black;
    valueName = MyEnumToString(value);
    std::cout << value << " to string:" << valueName << std::endl;

    valueName = "Blue";
    value = MyEnumFromString(valueName, MyEnum::Red);
    std::cout << "from string: " << valueName << ": " << value << std::endl;

    valueName = "Gray";
    value = MyEnumFromString(valueName, MyEnum::Invalid);
    std::cout << "from string: " << valueName << ": " << value << std::endl;
    return 0;
}
