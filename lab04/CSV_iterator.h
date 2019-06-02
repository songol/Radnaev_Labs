//
// Created by songol on 30.05.19.
//

#ifndef LAB04_CSV_ITERATOR_H
#define LAB04_CSV_ITERATOR_H
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <type_traits>
#include <tuple>
#include <gtest/gtest.h>

namespace internal {
    template <size_t index, typename ... Args>
    void tuple_printer(std::ostream& stream, const std::tuple<Args...>& my_tuple) {
        stream << std::get<index>(my_tuple);
        if constexpr (index < sizeof...(Args) - 1) {
            stream << ' ';
            tuple_printer < index + 1 > (stream, my_tuple);
        }
    }
}
template <typename ... Args>
std::ostream& operator<<(std::ostream& stream, const std::tuple<Args...>& my_tuple) {
    internal::tuple_printer<0>(stream, my_tuple);
    return stream;
}

template <typename...>
class CSVParser;


template <typename... Args>
class CSV_iterator {
public:
    explicit CSV_iterator(CSVParser<Args...> *parser = nullptr) : parser_(parser) {};
    bool operator!=(const CSV_iterator& it) {
        return !(parser_->end_of_file_ && it.parser_ == nullptr);
    }

    CSV_iterator& operator++() {
        if (parser_) {
            parser_->read_line();
        }
        return *this;
    }
    const std::tuple<Args...>& operator*() {
        return parser_->parseline();
    }

private:
    CSVParser<Args...>* parser_;
};


#endif //LAB04_CSV_ITERATOR_H
