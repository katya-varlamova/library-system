//
// Created by Екатерина on 19.11.2022.
//

#ifndef SRC_TESTSESSSION_HPP
#define SRC_TESTSESSSION_HPP
#include "Session.h"

template <>
template<typename INTO_T>
int Session<TestingSession>::exec_into(const std::string &query, INTO_T &into)
{
    session.analyze(query);
    return 0;
}
template <>
template<typename INTO_T>
int Session<TestingSession>::exec_into(const std::string &query, std::vector<INTO_T> &into)
{
    session.analyze(query);
}


//class SQLParser{
//public:
//    size_t split(const std::string &txt, std::vector<std::string> &strs, const std::string &delim)
//    {
//        size_t pos = txt.find( delim );
//        size_t initialPos = 0;
//        strs.clear();
//
//        // Decompose statement
//        while( pos != std::string::npos ) {
//            strs.push_back( txt.substr( initialPos, pos - initialPos ) );
//            initialPos = pos + delim.size();
//
//            pos = txt.find( delim, initialPos );
//        }
//
//        // Add the last one
//        strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + delim.size() ) );
//
//        return strs.size();
//    }
//    std::string join(const std::vector<std::string> &strs){
//        std::string str;
//        for (auto s : strs)
//            str += s;
//        return str;
//    }
//    std::vector<std::string> cut(const std::vector<std::string> &strs, int b, int e){
//        std::vector<std::string> cut;
//        for (int i = b; i < e; i++)
//            cut.push_back(strs[i]);
//        return cut;
//    }
//    int find_word(const std::vector<std::string> &strs, const std::string &word, int b, int e){
//        for (int i = b; i < e; i++)
//            if (strs[i] == word)
//                return i;
//        return strs.size();
//    }
//    void parse(const std::string &query, std::vector<std::string> &tables, std::string &action, std::vector<std::string> &cols, std::vector<std::string> &vals, std::vector<std::string> &joincl,  std::vector<std::string> &jointypes){
//        std::vector<std::string> strs;
//        split(query, strs, " ");
//        action = strs[0];
//
//        if (action == "select"){
//            int from = find_word(strs, "from", 1, strs.size());
//            split(join(cut(strs, 1, from)), cols, ",");
//
//            int where = find_word(strs, "where", 1, strs.size());
//            tables.push_back(strs[from + 1]);
//            int pos = find_word(strs, "join", from + 1, strs.size());
//            while (pos != strs.size())
//            {
//                if (strs[pos - 1] == "left")
//                    jointypes.push_back("left");
//                else
//                    jointypes.push_back("ordinary");
//                tables.push_back(strs[pos + 1]);
//                int lpos = find_word(strs, "left", pos + 1, strs.size());
//                int jpos = find_word(strs, "join", pos + 1, strs.size());
//                joincl.push_back(join(cut(strs, pos + 3, std::min(std::min(jpos, lpos), where))));
//                pos = jpos;
//            }
//
//            if (where != strs.size()) {
//                split(join(cut(strs, where + 1, strs.size())), vals, ",");
//            }
//        } else if (action == "insert"){
//            tables.push_back(strs[2]);
//
//            int fc = find_word(strs, ")", 3, strs.size());
//            split(join(cut(strs, 4, fc)), cols, ",");
//
//            int vc = find_word(strs, "values(", fc + 1, strs.size());
//            int sc = find_word(strs, ")", fc + 1, strs.size());
//            split(join(cut(strs, vc + 1, sc)), vals, ",");
//        } else if (action == "update"){
//            tables.push_back(strs[1]);
//
//            int set = find_word(strs, "set", 2, strs.size());
//            int where = find_word(strs, "where", set + 1, strs.size());
//
//            split(join(cut(strs, set + 1, where)), cols, ",");
//            split(join(cut(strs, where + 1, strs.size())), vals, ",");
//        } else if (action == "delete"){
//            tables.push_back(strs[2]);
//
//            int where = find_word(strs, "where", 3, strs.size());
//
//            split(join(cut(strs, where + 1, strs.size())), vals, ",");
//        }
//
//    }
//    std::pair<std::string, std::string>parse_arg(const std::string &q){
//        std::vector<std::string> vals;
//        split(q, vals, "=");
//        return std::pair<std::string, std::string>(vals[0], vals[1]);
//    }
//    std::pair<std::string, std::string>parse_name(const std::string &q){
//        std::vector<std::string> vals;
//        split(q, vals, ".");
//        return std::pair<std::string, std::string>(vals[0], vals[1]);
//    }
//};
//
//class TestDB{
//public:
//    void setDB(std::map<std::string, std::map<std::string, std::vector<std::string>>> db) {
//        this->db = db;
//    }
//    std::map<std::string, std::map<std::string, std::vector<std::string>>> getDB()
//    {
//        return db;
//    }
//    void select(std::vector<std::string> tables, std::vector<std::string> cols, std::vector<std::string> vals, std::vector<std::string> jcls, std::vector<std::string> jt){
//        std::map<std::string, std::vector<std::string>> resjoin;
//        resjoin = db[tables[0]];
//        for (int i = 0; i < jt.size(); i++){
//            auto p = parser.parse_arg(jcls[i]);
//            auto p1 = parser.parse_name(p.first);
//            auto p2 = parser.parse_name(p.second);
//            std::string tn1 = p1.first;
//            std::string cn1 = p1.second;
//            std::string tn2 = p2.first;
//            std::string cn2 = p2.second;
//            if (jt[i] == "ordinary")
//            {
//            }
//
//        }
//    }
//
//private:
//    SQLParser parser;
//    std::map<std::string, std::map<std::string, std::vector<std::string>>> db;
//};
#endif //SRC_TESTSESSSION_HPP
