#pragma once
#pragma once
#ifndef __DARWIN_H__
#define __DARWIN_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>

struct Species {
	int					sid;
	struct Population	*population_root;
	struct Species		*lc;
	struct Species		*rc;
};

struct Population {
	int					gid;
	int					sid;
	int					cid;
	struct Population	*parent;
	struct Population	*lc;
	struct Population	*rc;
};

struct ContinentPopulation {
	int 						gid;
	struct ContinentPopulation	*lc;
	struct ContinentPopulation	*rc;
};

struct ContinentTree
{
	struct ContinentPopulation *population_root;
	struct ContinentPopulation *sentinel;
};

struct HomoSapiens {
	int					sid;
	struct Population	*population_root;
	struct HomoSapiens	*next;
	struct HomoSapiens	*lc;
	struct HomoSapiens	*rc;
};

/*
 * Global variables
 *
 */

struct ContinentTree *continents[5]; // Continents' array. Each element is two pointers. 
									 // One to the continent's population tree root
									 // and one to the tree's sentinel node

struct Species *Species_root; // Pointer to the root of Species' tree


struct HomoSapiens *Homo_Sapiens_root; // Pointer to the root of Homo Sapiens tree

/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 1 on success
 *         0 on failure
 */
int initialize(void)
;
/**
 * @brief insert new species in Species' list with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_species(int sid)
;

/**
 * @brief insert new population with ID <gid> in Species' with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int insert_population(int gid, int sid, int cid);

/**
 * @brief find the lowest (earliest) common ancestor of populations with ID <gid1> and <gid2> of species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int lowest_common_ancestor(int sid, int gid1, int gid2);

/**
 * @brief merge species with IDs <sid1> and <sid2> into new species with ID <sid3>
 *
 * @return 1 on success
 *         0 on failure
 */
int merge_species(int sid1, int sid2, int sid3);

/**
 * @brief Distribute species' population in continents array
 *
 * @return 1 on success
 *         0 on failure
 */
int distribute();

/**
 * @brief delete population with ID <gid> from species with ID <sid>
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_population(int gid, int sid);

/**
 * @brief delete the species with lowest id and its populations
 *
 * @return 1 on success
 *         0 on failure
 */
int delete_species();
/**
 * @brief Remaining species evolve into homo sapiens.
 *
 * @return 1 on success
 *         0 on failure
 */
int evolution();

/**
 * @brief Gather statistics on species from homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int species_statistics();

/**
 * @brief Gather statistics on population belonging to species with ID <sid> from homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int population_statistics(int sid);

/**
 * @brief Print species' leaves list
 *
 * @return 1 on success
 *         0 on failure
 */
int print_species();
void Print_Species_inserted_Population(struct Population  *sp);
struct ContinentPopulation*  parent_cont;//parent of the node
struct HomoSapiens *BottomLeftLeaf();
void Print_sid_gid(struct Species *sp);
struct Species  *FindSpecie(int sid);
/**
 * @brief Print species' tree with population trees
 *
 * @return 1 on success
 *         0 on failure
 */
int print_populations();

/**
 * @brief Print continents array with each continent's population tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_continents();
/**
 * @brief Print homo_sapiens tree
 *
 * @return 1 on success
 *         0 on failure
 */
int print_homo_sapiens();
/**
 * @brief Free resources
 *
 * @return 1 on success
 *         0 on failure
 */
int free_all(void);

void InsertLeafOriented(struct Species* sp);


#endif /* __DARWIN_H__ */
