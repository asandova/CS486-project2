//
//  deBruijnByHash.cpp
//  k-assembler
//
//  Created by Joe Song on 11/24/15.
//  Copyright © 2015 Joe Song. All rights reserved.
//
//  Updated 3/19/2018
/*
*	Editied by: August B. Sandoval, 
*	Class: CS486
*	Assignment: Project 2
*
*/



#include "k-assembler.hpp"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct DNAHasher
// Hash function used for DNA sequence
{
    std::size_t operator()(const string & seq) const
    {
        // TO DO: Write a DNA sequence hash function here
        
        // BEGIN your code here:
		size_t val = 0;
		size_t max_width = 32;
		for (size_t i = 0; i < seq.size() && i < max_width; ++i) {
			val = val << 2;
			size_t n;
			switch (seq[i]) {
				case 'A':
				case 'a':
					n = 0;
					break;
				case 'C':
				case 'c':
					n = 1;
					break;
				case 'G':
				case 'g':
					n = 2;
					break;
				default:
					n = 3;
					break;
			}
			val += n;
		}
        // END your code above
    }
};

struct AlphabetHasher
// An example hash function used for the English alphabet
{
    std::size_t operator()(const string & seq) const
    {
        size_t val = 0;
        size_t max_width=20;
        for(size_t i=0; i<seq.size() && i<max_width; ++i) {
            val = val << 5;
            val += tolower(seq[i])-'a';
        }
        return val;
    }
};

// define the hash table class
// typedef unordered_multimap<string, size_t, AlphabetHasher> CSeqHash;

typedef unordered_multimap<string, size_t, DNAHasher> CSeqHash;

CSeqHash create_hash_table(const vector<string> & kmers)
// create one hash table by inserting both the prefix and suffix of each
//   k-mer. The prefix and suffix is the key. Associated with each element
//   in the hash table is the node id for that prefix or suffix in the
//   de Bruijn graph to be constructed.
{
    CSeqHash ht;
    size_t node_id=0; // the node id will be used in the de Bruijn graph
    for (auto i=0u; i<kmers.size(); ++i) {
        for(auto j=0u; j<2; ++j) { // j=0: prefix; j=1: suffix
            auto key = kmers[i].substr(j, kmers[i].length()-1);
            if (ht.find(key) == ht.end()) {
                ht.insert(make_pair(key, node_id ++));
            }
        }
    }
    return ht;
}

void create_deBruijn_graph_by_hashing(const vector<string> & kmers, DiGraph & g)
// create a deBruijn graph by inserting all k-mers into the graph by hashing
{
	// TO DO:

	// BEGIN your code below:

	// create one hash table for both the k-1 prefix and suffix of
	//   each k-mer
	CSeqHash NTable = create_hash_table(kmers);
	// initialize an empty node vector for graph g
	vector<Node> KNodes = vector<Node>();
	// for each k-mer
	for (vector<string>::const_iterator itr = kmers.begin(); itr != kmers.end(); ++itr) {
		string preKey = itr->substr(0, itr->size() - 1);
		string sufKey = itr->substr(1, itr->size() - 1);
		
		// find the prefix node id from_id from the hash table
		size_t pre = NTable.find(preKey)->second;
		// update node from_id's label to prefix if necessary
		size_t prePos, sufPos;
		if (pre == NTable.end) {
			Node from_id;
			from_id.m_label == preKey;
			from_id.m_num_of_incoming = 0;
			KNodes.push_back(from_id);
			prePos = KNodes.size()-1;
		} else{
			for (prePos = 0; prePos < KNodes.size(); prePos++) {
				if (KNodes[prePos].m_label == preKey) {
					break;
				}
			}
		}
		// find the suffix node id to_id from the hash table
		size_t suf = NTable.find(sufKey)->second;
		// update node to_id's label to suffix if necessary
		if (suf == NTable.end) {
			Node to_id;
			to_id.m_label = sufKey;
			to_id.m_num_of_incoming = 0;
			KNodes.push_back(to_id);
			sufPos = KNodes.size() - 1;
		}else {
			for (sufPos = 0; sufPos < KNodes.size(); sufPos++) {
				if (KNodes[sufPos].m_label == sufKey) {
					break;
				}
			}
		}
		// create a new edge (from_id, to_id) by inserting node
		//   to_id into the adjaceny list of node from_id
		KNodes[prePos].m_outgoing.push_back( sufPos );
		KNodes[sufPos].m_num_of_incoming++;

		// update the number of incoming edges of node to_id
	}
    // end for loop
	g.m_nodes.resize(KNodes.size());
	//vector<Node>::iterator litr = KNodes.begin();
	//vector<Node>::iterator virt = g.m_nodes.begin();
	auto litr = KNodes.begin();
	auto vitr = g.m_nodes.begin();
	while (litr != KNodes.end()) {
		*vitr++ = *litr++;
	}
    // END your code above

}
