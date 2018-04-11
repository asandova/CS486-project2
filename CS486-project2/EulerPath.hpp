#ifndef EULERPATH_HPP
#define EULERPATH_HPP

//
//  EulerPath.hpp
//  Created by August B. Sandoval, Hector Alva
//	CS486
//	Project 2
//
//  4/11/2018


extern size_t source(const DiGraph & g);

extern size_t sink(const DiGraph & g);

extern list<size_t> find_Eulerian_cycle(DiGraph & g);

extern list<size_t> find_Eulerian_path(DiGraph & g);

extern bool has_Eulerian_path(const DiGraph & g);

#endif // !EULERPATH_HPP