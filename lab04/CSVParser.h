//
// Created by songol on 30.05.19.
//

#ifndef LAB04_CSVPARSER_H
#define LAB04_CSVPARSER_H
#include "CSV_iterator.h"
#include <sstream>
#include <exception>
#include <utility>

template <typename... Args>
class CSVParser {
    friend class CSV_iterator<Args...>;

public:
    explicit CSVParser(std::ifstream& file, int skip_lines = 0, char separator = ',', char shield = '"') :
            file_(file), start_line(skip_lines), separator_(separator), end_of_file_(false), num_of_columns_(sizeof...(Args)), shield_(shield) {
        if (separator_ == shield_) {
            throw std::runtime_error(std::string("Сепаратор и символ экранирования не должны совпадать"));
        }
        for (int i = 0; i < start_line; ++i) {
            std::getline(file_, str_);
        }

    }
    ~CSVParser() {
        file_.close();
    }
    std::tuple<Args...>& parseline() {
        current_iter_ = str_.begin();
        output_ = {};
        ParseImpl(std::make_index_sequence<sizeof...(Args)> {});
        return output_;
    }

    CSV_iterator<Args...> begin() {
        end_of_file_ = false;
        if (file_.eof()) {
            end_of_file_ = true;
        } else {
            std::getline(file_, str_);
        }
        return CSV_iterator<Args...>(this);
    }
    CSV_iterator<Args...> end() {
        return CSV_iterator<Args...>();
    }

    void read_line() {
        if (!file_.eof()) {
            std::getline(file_, str_);
        } else {
            end_of_file_ = true;
        }
    }


private:
    template <size_t... Is>
    void ParseImpl(std::index_sequence<Is...> sequence) {
        leftindex_ = 0;
        rightindex_ = 0;
        ((ParseArgument(std::get<Is>(output_), Is)), ...);
    }

    template <typename T>
    void ParseArgument(T& tuple_element, size_t column_number) {
        if (column_number != num_of_columns_ - 1) {
            if (str_[leftindex_] == shield_) {
                rightindex_ = str_.find(shield_, leftindex_ + 1) + 1;
            } else {
                rightindex_ = str_.find(separator_, leftindex_);
            }
            if (rightindex_ == -1 && column_number != num_of_columns_ - 1) {
                throw std::runtime_error(std::string("bad separator at row \"" + str_ + "\""));
            }
        } else {
            if (str_.find(separator_, leftindex_) != -1) {
                throw std::runtime_error(std::string("too many values to unpack at row  \"" + str_ + "\" pos : "));
                }
            rightindex_ = str_.size();
        }
        std::string current_str = str_.substr(leftindex_, rightindex_ - leftindex_);
        std::stringstream ss(current_str);
        T value{};
        if (!(ss >> value)) {
            throw std::runtime_error(std::string("can't parse parameter at raw \"" + str_ + "\" pos : ") + std::to_string(rightindex_));
        }
        leftindex_ = rightindex_ + 1;
        tuple_element = value;


    }
    int leftindex_;
    int rightindex_;
    std::ifstream& file_;
    int start_line;
    char separator_;
    bool end_of_file_;
    char shield_;
    size_t num_of_columns_;

    std::tuple<Args...> output_;
    std::string::iterator current_iter_;
    std::string str_;
};



#endif //LAB04_CSVPARSER_H
