#ifndef BEBRUIJNBYHASH_HPP
#define BEBRUIJNBYHASH_HPP

//
//  deBruijnByHash.hpp
/*
*	Editied by: August B. Sandoval,
*	Class: CS486
*	Assignment: Project 2
*
*/
#include <unordered_map>
#include <vector>
#include "k-assembler.hpp"

using namespace std;

extern struct DNAHasher;

extern struct AlphabetHasher;

typedef unordered_multimap<string, size_t, DNAHasher> CSeqHash;

extern CSeqHash create_hash_table(const vector<string> & kmers);

extern void create_deBruijn_graph_by_hashing(const vector<string> & kmers, DiGraph & g);

#endif // !BEBRUIJNBYHASH_H
