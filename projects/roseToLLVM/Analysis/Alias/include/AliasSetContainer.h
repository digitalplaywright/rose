#ifndef _ALIASSETCONTAINER_H
#define _ALIASSETCONTAINER_H

#include <set>
#include <vector>
#include <map>
#include <llvm/Function.h>
#include <llvm/Module.h>
#include <utility>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

enum AliasType {May = 2, Must = 1, No = 0};

namespace AliasDataSet 
{
    typedef std::set<std::string> AliasRef;
    typedef std::pair<AliasRef, AliasType> AliasSet;
    typedef std::vector<AliasSet> AliasSetList;
}

/*
 * AliasSetContainer holds all alias sets in a function
 *
 */

class AliasSetContainer
{
    std::string _functionname;       // to associate sets with a function

    std::string _aliaslocations;     // written by llvm pass

    AliasDataSet::AliasSetList _aliasSetList;

    public:

    AliasSetContainer(std::string _fn_name );

    
    /*
     * use this function to add alias sets in LLVM Pass
     */ 
     
    void addaliasinglocations(std::string _alias);        

    /*
     * Parse LLVM's Alias Analysis output
     */

    void parseAliasSet();


    // for debugging purposes
    void print();
     
};

class AliasSetContainerList
{
    std::string _modulename;
    std::map<std::string, AliasSetContainer*>  _list;

    public:
        AliasSetContainerList(std::string _module_name);

        void addNewFunction(std::string _functionname ) ;

        AliasSetContainer* getContainer(std::string _functionname );

        ~AliasSetContainerList();

        void parseAliasSet();

        // for debugging purposes
        void print();
};

#endif