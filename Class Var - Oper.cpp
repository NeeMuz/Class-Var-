#include <iostream>
#include <string>

class var {
private:
    enum Type { INT, DOUBLE, STRING };
    Type type;
    union {
        int intValue;
        double doubleValue;
        std::string* stringValue;
    };

public:
    var() : type(INT), intValue(0) {}

    var(int value) : type(INT), intValue(value) {}

    var(double value) : type(DOUBLE), doubleValue(value) {}

    var(const char* value) : type(STRING) {
        stringValue = new std::string(value);
    }

    ~var() {
        if (type == STRING) {
            delete stringValue;
        }
    }

    var operator+(const var& other) const;
    var operator-(const var& other) const;
    var operator*(const var& other) const;
    var operator/(const var& other) const;
    bool operator==(const var& other) const;
    bool operator!=(const var& other) const;

    void Show() const;
};

var var::operator+(const var& other) const {
    if (type == STRING || other.type == STRING) {
        return var(std::to_string(intValue) + std::to_string(other.intValue));
    }

    if (type == DOUBLE || other.type == DOUBLE) {
        return var(doubleValue + other.doubleValue);
    }

    return var(intValue + other.intValue);
}

var var::operator-(const var& other) const {
    if (type == DOUBLE || other.type == DOUBLE) {
        return var(doubleValue - other.doubleValue);
    }

    return var(intValue - other.intValue);
}

var var::operator*(const var& other) const {
    if (type == STRING && other.type == STRING) {
        std::string result;
        for (char ch : *stringValue) {
            if (other.stringValue->find(ch) != std::string::npos) {
                result += ch;
            }
        }
        return var(result);
    }

    if (type == DOUBLE || other.type == DOUBLE) {
        return var(doubleValue * other.doubleValue);
    }

    return var(intValue * other.intValue);
}

var var::operator/(const var& other) const {
    if (type == STRING && other.type == STRING) {
        std::string result;
        for (char ch : *stringValue) {
            if (other.stringValue->find(ch) == std::string::npos) {
                result += ch;
            }
        }
        return var(result);
    }

    if (other.intValue == 0 || other.doubleValue == 0.0) {
        std::cerr << "Error: Division by zero." << std::endl;
        return var();
    }

    if (type == DOUBLE || other.type == DOUBLE) {
        return var(doubleValue / other.doubleValue);
    }

    return var(intValue / other.intValue);
}

bool var::operator==(const var& other) const {
    if (type == STRING || other.type == STRING) {
        return *stringValue == *other.stringValue;
    }

    return intValue == other.intValue && doubleValue == other.doubleValue;
}

bool var::operator!=(const var& other) const {
    return !(*this == other);
}

void var::Show() const {
    if (type == STRING) {
        std::cout << *stringValue;
    }
    else if (type == DOUBLE) {
        std::cout << doubleValue;
    }
    else {
        std::cout << intValue;
    }
    std::cout << std::endl;
}

int main() {
    var a = 15;
    var b = "hi";
    var c = 8;
    var d = "50";
    b = a + d;
    b.Show();
    if (a == b)
        std::cout << "Equal\n";
    else
        std::cout << "Not Equal\n";

    return 0;
}
