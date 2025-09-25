#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "bfilter.h"
#include <functional>

// (a)

class SillyHashFun : public HashFun
{
    unsigned int operator()(const std::string& key)
    {
        // Here's my silly hash function that always returns 0.
        // You should make some good hash functions and not use this one.
        // This is just an example of how to inherit the HashFun class.
        return 0;
    }
};

class GoodHashFun_0 : public HashFun
{
    unsigned int operator()(const std::string& key)
    {
        // You've seen my silly hash function above.
        // Your good hash function should go here!

        return 0; // You'll need to change this
    }
};

// choose 05 - SDBM Hash Function
 class SDBMHash : public HashFun
{
    unsigned int operator()(const std::string& key)
    {
        unsigned int hash = 0;
        unsigned int i = 0;

        for (i = 0; i < key.length(); ++i)
        {
            hash = key[i] + (hash << 6) + (hash << 16) - hash;
        }

        return hash;
    }
}; 

// choose 06 - DJB Hash Function
class DJBHash : public HashFun
{
    unsigned int operator()(const std::string& key)
    {
        unsigned int hash = 5381;
        unsigned int i    = 0;

        for (i = 0; i < key.length(); ++i)
        {
            hash = ((hash << 5) + hash) + key[i];
        }

        return hash;
    }
}; 


void BloomFilter::add_hash_funs()
{
    SDBMHash* h1 = new SDBMHash();
    DJBHash* h2 = new DJBHash();
    this->hash_funs.push_back(h1);
    this->hash_funs.push_back(h2);
}


const size_t filterSize = 330; 

void BloomFilter::insert(const std::string& key)
{
    for (size_t i = 0; i < this->hash_funs.size(); i++)
    {
        unsigned int hash_result = this->call_hash(i, key);
        (this->filter)[hash_result % filterSize] = 1;
    }
}

bool BloomFilter::member(const std::string& key)
{
    for (size_t i = 0; i < this->hash_funs.size(); i++)
    {
        unsigned int hash_result = this->call_hash(i, key);
        if ((this->filter)[hash_result % filterSize] == 0)
        {
            return false;
        }
    }
    return true;
}


