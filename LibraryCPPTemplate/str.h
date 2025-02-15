#ifndef STRING_TEMPLATE_H
#define STRING_TEMPLATE_H

#include <vector>

class String 
{

public:
    static const int NULL_POS = -1;

    size_t getLength() const { return length; }

    String() : string(nullptr), length(0) {}

    String(const char* chars, size_t len) : string(copyChars(chars, len)), length(len) {}

    String(const String& src) : string(copyChars(src.string, src.length)), length(src.length) {}

    ~String() 
    { 
        delete[] string;
    }

    String& operator=(const String& src) 
    {
        if (this != &src) {
            delete[] string;
            string = copyChars(src.string, src.length);
            length = src.length;
        }
        return *this;
    }

    // Перегрузка оператора []
    char& operator[](size_t index)
    {
        if (index >= length)
        {
            throw std::out_of_range("Index out of range");
        }
        return string[index];
    }

    // Константная перегрузка оператора []
    const char& operator[](size_t index) const
    {
        if (index >= length)
        {
            throw std::out_of_range("Index out of range");
        }
        return string[index];
    }

    void append(char ch) 
    {
        size_t id = length;
        resize(id + 1);
        string[id] = ch;
    }

    void append(String const& secondString) 
    {
        size_t startId = length;
        size_t secondLength = secondString.length;
        resize(length + secondLength);
        for (size_t i = 0; i < secondLength; i++) 
        {
            string[startId + i] = secondString.string[i];
        }
    }

    void resize(size_t newSize) 
    {
        char* newString = new char[newSize + 1];
        size_t newLength = (length < newSize) ? length : newSize;

        for (size_t i = 0; i < newLength; i++)
        {
            newString[i] = string[i];
        }

        newString[newSize] = '\0';

        delete[] string;
        string = newString;
        length = newSize;
    }


    int findString(String const& str, size_t pos = 0) 
    {
        std::vector<size_t> prefix(str.length);
        prefix[0] = 0;
        for (size_t k = 0, i = 1; i < str.length; i++)
        {
            while ((k > 0) && (str.string[i] != str.string[k])) 
            {
                k = prefix[k - 1];
            }
            if (str.string[i] == str.string[k])
            {
                k++;
            }
            prefix[i] = k;
        }

        for (size_t k = 0, i = pos; i < length; i++)
        {
            while ((k > 0) && (string[i] != str.string[k]))
            {
                k = prefix[k - 1];
            }
            if (string[i] == str.string[k])
            {
                k++;
            }
            if (k == str.length)
            {
                return int(i - k + 1);
            }
        }
        return NULL_POS;
    }

    int compare(String const& secondString)
    {
        char* str1 = string;
        char* str2 = secondString.string;
        while (*str1 != 0)
        {
            if (*str1 != *str2)
                return *str1 > *str2 ? 1 : -1;
            str1++;
            str2++;
        }
        return 0;
    }

    bool equal(String const& secondString)
    {
        return compare(secondString) == 0;
    }

    char* getCharArray()
    {
        return copyChars(string, length);
    }

private:

    char* copyChars(const char* chars, size_t len) 
    {
        if (chars == nullptr) 
        {
            char* result = new char[1];
            result[0] = '\0';
            return result;
        }
        char* result = new char[len + 1];
        for (size_t i = 0; i < len; ++i) 
        {
            result[i] = chars[i];
        }
        result[len] = '\0';
        return result;
    }

protected:
    char* string = nullptr;
    size_t length = 0;

};

#endif
