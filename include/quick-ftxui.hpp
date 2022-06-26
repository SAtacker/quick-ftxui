
//  This sample demontrates a parser for a comma separated list of numbers.
//  No actions.
//
#include <boost/spirit/include/qi.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace client {
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

///////////////////////////////////////////////////////////////////////////
//  Our number list parser
///////////////////////////////////////////////////////////////////////////
//[tutorial_numlist1
template <typename Iterator> bool parse_numbers(Iterator first, Iterator last) {
    using ascii::space;
    using qi::double_;
    using qi::phrase_parse;

    bool r = phrase_parse(first,                        /*< start iterator >*/
                          last,                         /*< end iterator >*/
                          double_ >> *(',' >> double_), /*< the parser >*/
                          space                         /*< the skip-parser >*/
    );
    if (first != last) // fail if we did not get a full match
        return false;
    return r;
}
//]
} // namespace client
