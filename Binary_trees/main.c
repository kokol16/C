
#define _CRT_SECURE_NO_WARNINGS

#include"Darwin.h"




//initialize


int initialize(void)
{
	Species_root = NULL;
	Homo_Sapiens_root = NULL;
	int i = 0;
	for (i = 0; i < 5; i++)//initialize tree with sentinel
	{
		continents[i] = (struct ContinentTree*) malloc(sizeof(struct ContinentTree));
		(continents[i]->sentinel) = malloc(sizeof(struct ContinentPopulation));
		(continents[i]->sentinel)->gid = -1;
		(continents[i]->sentinel)->lc = NULL;
		(continents[i]->sentinel)->rc = NULL;
		(continents[i]->population_root) = (continents[i]->sentinel);
		
	}
}



//prints
void Print_Species(struct Species *sp)
{
	if (sp == NULL) { return; }
	Print_Species(sp->lc);
	Print_Species(sp->rc);
	printf("<%d> ", sp->sid);

}
int print_species()
{
	struct Species *tmp = Species_root;
	Print_Species(tmp);
}



void Print_Species_inserted_Population(struct Population  *sp)
{

	if (sp == NULL) { return; }


	Print_Species_inserted_Population(sp->lc);
	printf("  <%d,%d> ", sp->gid, sp->cid);
	Print_Species_inserted_Population(sp->rc);



}


int print_populations()
{
	Print_sid_gid(Species_root);
	return 1;

}



void print_gids(struct Population *pop)
{
	if (pop == NULL) { return; }
	print_gids(pop->lc);

	printf("  <%d>,", pop->gid);
	print_gids(pop->rc);

}
void Print_sid_gid(struct Species *sp)
{
	if (sp == NULL) { return; }

	Print_sid_gid(sp->lc);
	Print_sid_gid(sp->rc);

	printf("<%d>\n", sp->sid);

	print_gids(sp->population_root);
	printf("\b ");
	printf("\n");

}

void Pre_Print_gid(struct ContinentPopulation *root, struct ContinentPopulation * sentinel)
{

	if (root == sentinel) { return; }


	Pre_Print_gid(root->lc, sentinel);
	printf("<%d> ", root->gid);
	Pre_Print_gid(root->rc, sentinel);

}

int  print_continents()
{
	int i;
	for (i = 0; i < 5; i++)
	{
		printf("continent %d : ", i);
		Pre_Print_gid(continents[i]->population_root, continents[i]->sentinel);
		printf("\n");

	}
	return 1;
}

void Print_Continents_gid(struct ContinentPopulation * pop, struct ContinentPopulation * sentinel)
{
	if (pop == sentinel) { return; }


	Print_Continents_gid(pop->lc, sentinel);
	printf(" <%d>,", pop->gid);
	Print_Continents_gid(pop->rc, sentinel);
	printf("\b ");


}


void Print_Popul_gid(struct Population  *sp)
{

	if (sp == NULL) { return; }


	Print_Popul_gid(sp->lc);
	printf(" <%d>,", sp->gid);
	Print_Popul_gid(sp->rc);



}


//print evolution
void Print_cid_gid_leaf_oriented(struct Population  *sp)
{

	if (sp == NULL) { return; }


	Print_cid_gid_leaf_oriented(sp->lc);
	printf("<%d,%d>,", sp->gid, sp->sid);
	Print_cid_gid_leaf_oriented(sp->rc);
	printf("\b ");



}


struct HomoSapiens *BottomLeftLeaf()
{
	struct HomoSapiens *iter = Homo_Sapiens_root;
	while (iter->lc != NULL)
	{
		iter = iter->lc;
	}
	return iter;
}
int print_homo_sapiens()
{
	struct HomoSapiens *hs;
	hs = BottomLeftLeaf();
	printf("[");
	while (hs != NULL)
	{
		Print_cid_gid_leaf_oriented(hs->population_root);

		//Print_cid_gid_leaf_oriented(hs->population_root);
		printf("]");
		if (hs->next != NULL)
		{

			printf(" [");
		}

		hs = hs->next;
	}
	printf("\n");

	return 1;
}




//insert species

/*Post order sorted binaty tree */
int insert_species(int sid)
{
	struct Species *sp;
	bool found = false;
	//new species node 
	sp = (struct Species*) malloc(sizeof(struct Species));
	sp->sid = sid;
	sp->lc = NULL;
	sp->rc = NULL;
	sp->population_root = NULL;
	if (Species_root == NULL)//insert root
	{
		Species_root = sp;
	}
	else
	{
		struct Species *iter = Species_root;
		struct Species *parent = Species_root;

		while (iter != NULL && iter->sid > sp->sid)//find where the new node will be inserted
		{
			parent = iter;
			if (iter->lc == NULL)//default position left
			{
				iter->lc = sp;
				found = true;
				break;
			}
			if (iter->rc == NULL && iter->lc != NULL)//if it has one child on left
			{

				if (iter->lc->sid < sp->sid)//if the new child is bigger  than left child then ,  make it right child
				{
					iter->rc = sp;
					found = true;
					break;
				}

			}



			if (sp->sid < iter->lc->sid)
			{
				iter = iter->lc;
			}
			else
			{
				iter = iter->rc;
			}



		}
		//found variable tells us if the insertion has been completed , so we don't want to make any changes
		if (!found && iter == Species_root)//we have to insert the new node as a root
		{


			sp->lc = Species_root;//make root left child of new node
			Species_root = sp;

		}
		else if (!found)
		{
			sp->lc = iter;

			if (parent->lc == iter)//parent left child will be the new node
			{
				parent->lc = sp;
			}
			else//parent right child
			{
				parent->rc = sp;

			}

		}




	}
	print_species();




}


//insert population







struct Species  *FindSpecie(int sid)
{
	//If the key is not found this function returns NULL
	if (Species_root == NULL) { return NULL; }
	struct Species *p = Species_root;

	if (p->sid == sid)
	{
		return p;
	}
	if (Species_root->lc->sid < sid)
	{
		p = p->rc;
	}
	else
	{
		p = p->lc;
	}
	while (1)
	{
		if (p->sid == sid) { return p; }
		if (p->lc != NULL && p->lc->sid >= sid)
		{

			p = p->lc;
		}
		else
		{
			p = p->rc;
		}

		if (p == NULL) { return NULL; }

	}



}

/*inorder sorted binary tree*/
int insert_population(int gid, int sid, int cid)
{

	struct Species *sp = FindSpecie(sid);//find the current specie
	if (sp == NULL)//check if specie not found
	{
		return 0;
	}
	struct Population *pop;
	pop = (struct Population *) malloc(sizeof(struct Population));
	pop->cid = cid;
	pop->gid = gid;
	pop->sid = sid;
	pop->parent = NULL;
	pop->rc = NULL;
	pop->lc = NULL;
	if (sp->population_root == NULL)
	{
		sp->population_root = pop;
	}
	else
	{
		struct Population *iter = sp->population_root;
		struct Population *parent = iter;

		while (iter != NULL)
		{
			parent = iter;
			if (iter->gid > pop->gid)
			{
				iter = iter->lc;
			}
			else
			{
				iter = iter->rc;
			}
		}

		if (pop->gid < parent->gid)	//check if the key will be left or right child of the parent
		{
			parent->lc = pop;
			pop->parent = parent;
		}
		else
		{
			parent->rc = pop;
			pop->parent = parent;
		}

	}
	printf("<%d>\n", sid);
	Print_Species_inserted_Population(sp->population_root);
	printf("\n");
	printf("DONE\n");


	return 1;

}
//lowest common ansestor





struct Population* Find_Population(struct Population* pop, int gid)
{
	if (pop == NULL)
	{
		return NULL;
	}
	else
	{
		struct Population *iter = pop;


		while (iter != NULL)
		{
			if (iter->gid == gid)
			{
				return iter;
			}
			if (iter->gid > pop->gid)
			{
				iter = iter->lc;
			}
			else
			{
				iter = iter->rc;
			}
		}



	}



}
int countLevels(struct Population * pop, int gid)
{
	struct Population *iter = pop;
	int levels = 0;
	while (iter != NULL)
	{
		if (iter->gid == gid)
		{
			return iter;
		}
		if (iter->gid > pop->gid)
		{
			iter = iter->lc;
		}
		else
		{
			iter = iter->rc;
		}
		levels++;
	}
	return levels;
}

int lowest_common_ancestor(int sid, int gid1, int gid2)
{
	struct Species *sp = FindSpecie(sid);//find specie with current sid
	struct Population * pop1 = Find_Population(sp->population_root, gid1);//find population with current gid
	struct Population * pop2 = Find_Population(sp->population_root, gid2);//find population with current gid
	int lvl_pop1, lvl_pop2;
	if (sp == NULL || pop1 == NULL || pop2 == NULL) { return 0; }
	lvl_pop1 = countLevels(sp->population_root, pop1->gid);
	lvl_pop2 = countLevels(sp->population_root, pop2->gid);

	if (lvl_pop1 > lvl_pop2)//make the at the same level
	{
		while (pop1 != NULL && lvl_pop1 != lvl_pop2)
		{
			pop1 = pop1->parent;
			lvl_pop1--;
		}
		if (pop1 == NULL)
		{
			return 0;
		}

	}
	else
	{
		while (pop2 != NULL && lvl_pop1 != lvl_pop2)
		{
			pop2 = pop2->parent;
			lvl_pop2--;
		}
		if (pop2 == NULL)
		{
			return 0;
		}

	}


	while (pop1 != NULL && pop2 != NULL)
	{
		if (pop1 == pop2)//found the common ancestor
		{
			printf("Lowest Common Ancestor: <%d>\n", pop1->gid);
			break;
			printf("DONE\n");
		}
		pop1 = pop1->parent;
		pop2 = pop2->parent;
	}





	return 1;
}


//Merge

void * Delete_Postorder2(struct Species *sp, int sid)
{
	struct Species * parent = NULL, *iter = sp;
	if (sp == NULL) { return NULL; }



	while (iter != NULL && iter->sid != sid)
	{
		parent = iter;
		if (sid > iter->sid)
		{
			return NULL;
		}
		if (iter->lc != NULL && iter->lc->sid >= sid)
		{

			iter = iter->lc;
		}
		else
		{
			iter = iter->rc;
		}

	}
	iter->population_root = NULL;//delete population list
	//after we found specie


	//check if node has one or no childrens

	if (iter->rc == NULL)
	{
		if (parent != NULL)
		{
			if (iter == parent->lc)
			{
				parent->lc = iter->lc;
			}
			else
			{
				parent->rc = iter->lc;
			}
		}
		else
		{
			Species_root = iter->lc;
		}

	}
	else if (iter->lc == NULL)
	{
		if (parent != NULL)
		{
			if (iter == parent->lc)
			{
				parent->lc = iter->rc;
			}
			else
			{
				parent->rc = iter->rc;
			}
		}
		else
		{
			Species_root = iter->lc;
		}
	}

	else//node has 2 childrens
	{

		//find left most of node
		struct Species * tmp = iter->rc;
		struct species *left = iter->lc;

		while (tmp->lc != NULL)
		{
			tmp = tmp->lc;
		}
		if (parent != NULL)
		{
			tmp->lc = iter->lc;
			if (iter == parent->lc)
			{
				parent->lc = iter->rc;
			}
			else
			{
				parent->rc = iter->rc;
			}
		}
		else
		{
			Species_root = iter->rc;
		}
		tmp->lc = left;

	}




}
int insert_species_no_print(int sid)
{
	struct Species *sp;
	bool found = false;
	//new species node 
	sp = (struct Species*) malloc(sizeof(struct Species));
	sp->sid = sid;
	sp->lc = NULL;
	sp->rc = NULL;
	sp->population_root = NULL;
	if (Species_root == NULL)//insert root
	{
		Species_root = sp;
	}
	else
	{
		struct Species *iter = Species_root;
		struct Species *parent = Species_root;

		while (iter != NULL && iter->sid > sp->sid)//find where the new node will be inserted
		{
			parent = iter;
			if (iter->lc == NULL)//default position left
			{
				iter->lc = sp;
				found = true;
				break;
			}
			if (iter->rc == NULL && iter->lc != NULL)
			{

				if (iter->lc->sid < sp->sid)
				{
					iter->rc = sp;
					found = true;
					break;
				}

			}
			if (sp->sid < iter->lc->sid)
			{
				iter = iter->lc;
			}
			else
			{
				iter = iter->rc;
			}



		}
		if (!found && iter == Species_root)//we have to insert the new node as a root
		{
			//struct Species *tmp = Species_root->lc;
			// Species_root->lc=NULL;

			sp->lc = Species_root;
			Species_root = sp;
			//Species_root->lc = tmp;
		}
		else if (!found)
		{
			sp->lc = iter;

			if (parent->lc == iter)//parent left child will be the new node
			{
				parent->lc = sp;
			}
			else//parent right child
			{
				parent->rc = sp;

			}

		}




	}




}




int   countNodes(struct Population  * p)
{
	int counter = 1;
	if (p == NULL)return 0;
	counter += countNodes(p->lc);
	counter += countNodes(p->rc);
	return counter;

}

int size_cid = 0;
int size_gid = 0;
void createArray(int * array_cid, int * array_gid, struct Population * p)
{


	if (p == NULL)return;

	createArray(array_cid, array_gid, p->lc);
	array_cid[size_cid++] = p->cid;
	array_gid[size_gid++] = p->gid;
	createArray(array_cid, array_gid, p->rc);





}

int * tree3_cid;
int * tree3_gid;

void    arrayMerge(int  *tree1_cid, int  *tree2_cid, int  *tree2_gid, int *tree1_gid, int size1, int size2)
{
	if (size1 == 0 && size2 == 0)
	{
		return NULL;
	}
	int size3 = size1 + size2;


	//alocate memory
	tree3_cid = malloc(size3 * sizeof(int));
	tree3_gid = malloc(size3 * sizeof(int));




	if (size1 == 0)
	{
		for (int i = 0; i < size2; i++)
		{

			tree3_cid[i] = tree1_cid[i];
			tree3_gid[i] = tree1_gid[i];

		}
	}
	else if (size2 == 0)
	{
		for (int i = 0; i < size1; i++)
		{
			tree3_cid[i] = tree2_cid[i];
			tree3_gid[i] = tree2_gid[i];

		}
	}
	else//regular case
	{

		int index3 = 0;
		int index1 = 0;
		int index2 = 0;
		while (1)
		{
			if (tree1_gid[index1] < tree2_gid[index2])
			{
				tree3_gid[index3] = tree1_gid[index1];
				tree3_cid[index3] = tree1_cid[index1];
				index1++;
			}
			else
			{
				tree3_gid[index3] = tree2_gid[index2];
				tree3_cid[index3] = tree2_cid[index2];
				index2++;
			}

			index3++;
			if (index1 == size1 || index2 == size2) { break; }




		}
		if (index1 == size1)//tree1 reached his end
		{
			for (int i = index2; i < size2; i++)
			{
				tree3_gid[index3] = tree2_gid[i];
				tree3_cid[index3] = tree2_cid[i];
				index3++;
			}
			return;
		}
		else if (index2 == size2)//tree2 reached his end
		{
			for (int i = index1; i < size1; i++)
			{
				tree3_gid[index3] = tree1_gid[i];
				tree3_cid[index3] = tree1_cid[i];
				index3++;
			}
			return;
		}




	}





}
struct Population *a, *b;
struct Population  * createMergedTree(int  *tree3_cid, int * tree3_gid, int begin, int finish, int sid3)
{
	//Binary search on array




	if (begin > finish)
	{
		return NULL;

	}


	int middle = (begin + finish) / 2;

	struct Population  *	pop_root3 = (struct Population *) malloc(sizeof(struct Population));
	pop_root3->sid = sid3;
	pop_root3->cid = tree3_cid[middle];
	pop_root3->gid = tree3_gid[middle];
	pop_root3->lc = NULL;
	pop_root3->rc = NULL;


	//printf("%d\n", tree3[middle]);
	a = createMergedTree(tree3_cid, tree3_gid, begin, middle - 1, sid3);
	pop_root3->lc = a;
	b = createMergedTree(tree3_cid, tree3_gid, middle + 1, finish, sid3);
	pop_root3->rc = b;
	return pop_root3;
}



int merge_species(int sid1, int sid2, int sid3)
{
	size_cid = 0;
	size_gid = 0;
	tree3_cid = NULL;
	tree3_gid = NULL;
	a = NULL;
	b = NULL;

	int * tree1_cid;
	int * tree1_gid;
	int * tree2_cid;
	int * tree2_gid;



	int size1, size2;
	struct Species *sp1, *sp2, *sp3;
	insert_species_no_print(sid3);
	sp1 = FindSpecie(sid1);
	sp2 = FindSpecie(sid2);
	sp3 = FindSpecie(sid3);

	if (sp1 == NULL || sp2 == NULL) { return 0; }

	size1 = countNodes(sp1->population_root);




	size2 = countNodes(sp2->population_root);


	//	tree1=BindMemory( size1);
	//	tree2=BindMemory( size2);

	tree1_cid = malloc(size1 * sizeof(int));
	tree1_gid = malloc(size1 * sizeof(int));
	tree2_cid = malloc(size2 * sizeof(int));
	tree2_gid = malloc(size2 * sizeof(int));

	//fill the arrays of sid and gid for the first tree
	createArray(tree1_cid, tree1_gid, sp1->population_root);

	size_cid = 0;
	size_gid = 0;


	//fill the arrays of sid and gid for the second  tree

	createArray(tree2_cid, tree2_gid, sp2->population_root);




	arrayMerge(tree1_cid, tree2_cid, tree2_gid, tree1_gid, size1, size2);


	sp3->population_root = createMergedTree(tree3_cid, tree3_gid, 0, size1 + size2 - 1, sid3);




	//deleting
	Delete_Postorder2(Species_root, sid1);
	Delete_Postorder2(Species_root, sid2);

	//printing 


	Print_sid_gid(Species_root);
	printf("\b");

	return 1;


}

//Distribute



/*Inorder sorted tree*/
void insert(struct ContinentTree *array, struct ContinentPopulation * cont_pop)
{

	cont_pop->lc = array->sentinel;
	cont_pop->rc = array->sentinel;
	if (array->population_root == array->sentinel)//first node of the tree
	{
		array->population_root = cont_pop;
	}
	else
	{
		struct ContinentPopulation *iter = array->population_root;
		struct ContinentPopulation *parent = iter;

		while (iter != array->sentinel)
		{
			parent = iter;
			if (iter->gid > cont_pop->gid)
			{
				iter = iter->lc;
			}
			else
			{
				iter = iter->rc;
			}
		}

		if (cont_pop->gid < parent->gid)	//check if the key will be left or right child of the parent
		{
			parent->lc = cont_pop;
		}
		else
		{
			parent->rc = cont_pop;
		}

	}
}

void CreateContinent_Pop(struct Population *pop)
{
	//run every population node
	if (pop == NULL) { return; }

	struct ContinentPopulation *cont_pop = (struct ContinentPopulation *) malloc(sizeof(struct ContinentPopulation));
	cont_pop->gid = pop->gid;


	insert(continents[pop->cid], cont_pop);

	CreateContinent_Pop(pop->lc);
	CreateContinent_Pop(pop->rc);

}
void Postorder(struct Species *sp)
{
	//run every specie
	if (sp == NULL) { return; }

	CreateContinent_Pop(sp->population_root);
	Postorder(sp->lc);

	Postorder(sp->rc);
}






int distribute()
{
	struct Species * head = Species_root;
	Postorder(head);

	print_continents();
	return 1;




}
















//delete population





struct population * FindPopulation(struct Population* pop, int gid)
{

	while (pop != NULL)
	{
		if (pop->gid == gid) { return pop; }
		if (pop->gid < gid)
		{
			pop = pop->rc;
		}
		else
		{
			pop = pop->lc;
		}
	}

	return NULL;
}
struct ContinentPopulation * Find_Continent_Population(struct ContinentPopulation* pop, int gid, struct ContinentPopulation* sentinel)
{
	//change with sentinel
	parent_cont = NULL;
	sentinel->gid = gid;
	while (pop->gid != gid)
	{
		parent_cont = pop;
		if (pop->gid < gid)
		{
			pop = pop->rc;
		}
		else
		{
			pop = pop->lc;
		}
	}
	sentinel->gid = -1;
	if (pop == sentinel)
	{
		return NULL;

	}
	else
	{
		return pop;
	}
}



struct Population* TreeSuccessor_cont(struct ContinentPopulation* pop, struct ContinentPopulation* sentinel)
{





	//find the minimum going deep down left subtree until   null,     parto olo aristera
	if (pop->rc != sentinel)
	{
		parent_cont = pop;
		//find minimum
		pop = pop->rc;
		while (1)
		{
			if (pop->lc == sentinel) { break; }
			pop = pop->lc;
			parent_cont = pop;
		}
		return pop;

	}
	else
	{
		//if node hasn't right subtree then successor will be his parent , we will change parent only when we turn left

		return parent_cont;


	}
}


struct Population* TreeSuccessor(struct Population* pop)
{

	//find the minimum going deep down left subtree until   null,     parto olo aristera
	if (pop->rc != NULL)
	{
		//find minimum
		pop = pop->rc;
		while (1)
		{
			if (pop->lc == NULL) { break; }
			pop = pop->lc;
		}
		return pop;

	}
	else
	{
		//if node hasn't right subtree then successor will be his parent , we will change parent only when we turn left
		struct Population *parent = pop->parent;
		while (parent->gid < pop->gid)
		{

			parent = parent->parent;
		}
		return parent;


	}













}


int delete_population(int gid, int sid)
{


	parent_cont = NULL;
	bool found = false;
	struct Population* pop;//population of the current specie
	struct Species *sp;
	struct Population * tmp, *x;
	sp = FindSpecie(sid);
	if (sp == NULL) { return 0; }

	pop = FindPopulation(sp->population_root, gid);
	int cid = pop->cid; //keep cid in case we change it after
	if (pop == NULL) { return 0; }
	if (pop->lc == NULL || pop->rc == NULL)
		tmp = pop;
	else tmp = TreeSuccessor(pop);
	if (tmp->lc != NULL) x = tmp->lc;
	else x = tmp->rc;
	if (x != NULL) x->parent = tmp->parent;

	if (tmp->parent == NULL)
	{//delete the root 
		sp->population_root = x;
		found = true;

	}
	else if (tmp == tmp->parent->lc) tmp->parent->lc = x;
	else tmp->parent->rc = x;
	if (tmp != pop && !found)
	{
		pop->gid = tmp->gid;
		pop->sid = tmp->sid;
		pop->cid = tmp->cid;
	}


	printf("<%d>\n", sid);
	Print_Popul_gid(sp->population_root);
	printf("\n");



	//delete from array

	struct ContinentPopulation *pop_cont = Find_Continent_Population(continents[cid]->population_root, gid, continents[cid]->sentinel);
	struct ContinentPopulation *tmp2, *x2;

	if (pop_cont == NULL) { return 0; }
	if (pop_cont->lc == continents[cid]->sentinel || pop_cont->rc == continents[cid]->sentinel)
		tmp2 = pop_cont;
	else
	{
		tmp2 = TreeSuccessor_cont(pop_cont, continents[cid]->sentinel);
	}
	if (tmp2->lc != continents[cid]->sentinel) x2 = tmp2->lc;
	else x2 = tmp2->rc;



	if (parent_cont == NULL)
	{//delete the root 
		continents[cid]->population_root = x2;
		printf("CONTINENTS\n");
		printf(" Continent <%d> :", cid);
		Print_Continents_gid(continents[cid]->population_root, continents[cid]->sentinel);
		printf("\n");
		printf("DONE\n");
		return 1;
	}
	else if (tmp2 == parent_cont->lc)parent_cont->lc = x2;
	else if (tmp2 == parent_cont->rc)
	{
		parent_cont->rc = x2;

	}
	if (tmp2 != pop_cont)
	{
		pop_cont->gid = tmp2->gid;

	}



	printf("CONTINENTS\n");
	printf(" Continent <%d> :", cid);
	Print_Continents_gid(continents[cid]->population_root, continents[cid]->sentinel);
	printf("\n");
	printf("DONE\n");

	return 1;
}





int delete_population_no_print(int gid, int sid)
{


	parent_cont = NULL;
	bool found = false;
	struct Population* pop;//population of the current specie
	struct Species *sp;
	struct Population * tmp, *x;
	sp = FindSpecie(sid);
	if (sp == NULL) { return 0; }

	pop = FindPopulation(sp->population_root, gid);
	int cid = pop->cid; //keep cid in case we change it after
	if (pop == NULL) { return 0; }



	if (pop->lc == NULL || pop->rc == NULL)
		tmp = pop;
	else tmp = TreeSuccessor(pop);
	if (tmp->lc != NULL) x = tmp->lc;
	else x = tmp->rc;
	if (x != NULL) x->parent = tmp->parent;

	if (tmp->parent == NULL)
	{//delete the root 
		sp->population_root = x;
		found = true;

	}
	else if (tmp == tmp->parent->lc) tmp->parent->lc = x;
	else tmp->parent->rc = x;
	if (tmp != pop && !found)
	{
		pop->gid = tmp->gid;
		pop->sid = tmp->sid;
		pop->cid = tmp->cid;
	}






	//delete from array

	struct ContinentPopulation *pop_cont = Find_Continent_Population(continents[cid]->population_root, gid, continents[cid]->sentinel);
	struct ContinentPopulation *tmp2, *x2;

	if (pop_cont == NULL) { return 0; }
	if (pop_cont->lc == continents[cid]->sentinel || pop_cont->rc == continents[cid]->sentinel)
		tmp2 = pop_cont;
	else
	{
		tmp2 = TreeSuccessor_cont(pop_cont, continents[cid]->sentinel);
	}
	if (tmp2->lc != continents[cid]->sentinel) x2 = tmp2->lc;
	else x2 = tmp2->rc;


	if (parent_cont == NULL)
	{//delete the root 
		continents[cid]->population_root = x2;

		return 1;
	}
	else if (tmp2 == parent_cont->lc)parent_cont->lc = x2;
	else if (tmp2 == parent_cont->rc)
	{
		parent_cont->rc = x2;

	}
	if (tmp2 != pop_cont)
	{
		pop_cont->gid = tmp2->gid;

	}




	return 1;
}



//delete species




void Indorder_del(struct Population * pop)
{
	if (pop == NULL) { return; }
	Indorder_del(pop->lc);
	delete_population_no_print(pop->gid, pop->sid);
	Indorder_del(pop->rc);
}
void * Delete_Postorder_lowest()
{
	struct Species * parent = NULL, *iter = Species_root;
	if (Species_root == NULL) { return NULL; }


	//full left
	while (iter->lc != NULL)
	{
		parent = iter;
		iter = iter->lc;

	}
	if (parent != NULL)
	{
		Indorder_del(iter->population_root);


		parent->lc = parent->rc;
		parent->rc = NULL;


	}
	iter->population_root = NULL;
	return;


}










int delete_species()
{

	struct Species* iter;


	printf("SPECIES\n");
	iter = Delete_Postorder_lowest();
	Print_sid_gid(Species_root);
	//delete from array







	printf("CONTINENTS\n");
	print_continents();
	printf("DONE\n");




	return 1;
}




//evolution




void Species_tree(struct Species *sp)
{
	if (sp == NULL) { return; }




	InsertLeafOriented(sp);
	Species_tree(sp->lc);



	Species_tree(sp->rc);



}
struct HomoSapiens* newNode(struct Population  * pop, int sid)
{
	struct HomoSapiens* hs;

	hs = (struct HomoSapiens*) malloc(sizeof(struct HomoSapiens));
	hs->sid = sid;

	hs->lc = NULL;
	hs->rc = NULL;
	hs->next = NULL;
	hs->population_root = pop;
	return hs;
}

void InsertLeafOriented(struct Species* sp)
{

	struct HomoSapiens * p = Homo_Sapiens_root, *parent = NULL, *grandparent = NULL, *small, *big, *top, *rc, *lc;
	struct HomoSapiens * Nnode = newNode(sp->population_root, sp->sid);

	if (p == NULL)
	{
		Homo_Sapiens_root = Nnode;

	}
	else
	{
		while (p != NULL)
		{
			grandparent = parent;
			parent = p;
			if (sp->sid <= p->sid)
			{
				p = p->lc;
			}
			else
			{
				p = p->rc;
			}
		}

		//find the biggest and smallest 
		if (parent->sid < sp->sid)
		{
			small = parent;
			big = Nnode;
		}
		else
		{
			small = Nnode;
			big = parent;
		}

		top = newNode(small->population_root, small->sid);
		rc = newNode(big->population_root, big->sid);
		lc = parent;

		top->lc = lc;

		top->rc = rc;
		rc->next = parent->next;
		parent->sid = small->sid;
		parent->population_root = small->population_root;
		//parent becomes leaf

		parent->lc = NULL;
		parent->rc = NULL;
		lc->next = rc;
		if (grandparent != NULL)
		{
			if (grandparent->lc == parent)
			{
				grandparent->lc = top;
			}
			else
			{
				grandparent->rc = top;
			}
		}
		else
		{
			Homo_Sapiens_root = top;
		}

	}

	return 1;


}
int evolution()
{

	Species_tree(Species_root);
	print_homo_sapiens();
	Species_root = NULL;
	return 1;
}


//species statistics



int species_statistics()
{
	struct HomoSapiens * hs;
	int counter = 0;
	hs = BottomLeftLeaf();
	printf("Homo Sapiens:");
	while (hs != NULL)
	{
		counter++;
		if (hs->next != NULL)
		{
			printf("<%d>,", hs->sid);

		}
		else
		{
			printf("<%d>\n", hs->sid);

		}
		hs = hs->next;
	}
	printf("Homo Sapiens species: %d\n", counter);
	return 1;
}


//population statistics




struct HomoSapiens * FindNode(int key)
{
	//if key hasn't found return null
	struct HomoSapiens * p = Homo_Sapiens_root;
	if (p == NULL)
	{
		return 0;
	}
	while (p != NULL)
	{
		if (p->sid == key && p->rc == NULL && p->lc == NULL)//check if keys are equal and node is leaf

		{

			return p;
		}
		if (p->sid >= key)
		{
			p = p->lc;
		}
		else
		{
			p = p->rc;
		}


	}
	printf("sid %d couldn't be found \n", key);
	return NULL;



}
int FindPopulations(struct Population * sp)
{
	int left_count = 0, right_count = 0;
	if (sp == NULL) { return 0; }

	left_count = FindPopulations(sp->lc);
	right_count = FindPopulations(sp->rc);
	return (right_count + left_count + 1);
}

int population_statistics(int sid)
{
	int count;
	struct HomoSapiens* hs = FindNode(sid);
	if (hs == NULL) { return 0; }
	count = FindPopulations(hs->population_root);
	printf("Homo Sapiens Populations: %d\n", count);
	printf("DONE\n");
	return 1;
}



//main



#define _CRT_SECURE_NO_WARNINGS
#include "Darwin.h"

#define BUFFER_SIZE 1024  /* Maximum length of a line in input file */

/* Uncomment the following line to enable debugging prints
 * or comment to disable it */
#define DEBUG

#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else  /* DEBUG */
#define DPRINT(...)
#endif /* DEBUG */


int free_all(void) {
	return 1;
}


/**
 * @brief The main function
 *
 * @param argc Number of arguments
 * @param argv Argument vector
 *
 * @return 0 on success
 *         1 on failure
 */
int main(int argc, char** argv)
{
	FILE *fin = NULL;
	char buff[BUFFER_SIZE], event;

	/* Check command buff arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <input_file> \n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Open input file */
	if ((fin = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "\n Could not open file: %s\n", argv[1]);
		perror("Opening test file\n");
		return EXIT_FAILURE;
	}

	/* Initializations */
	initialize();

	/* Read input file buff-by-buff and handle the events */
	while (fgets(buff, BUFFER_SIZE, fin)) {

		DPRINT("\n>>> Event: %s", buff);

		switch (buff[0]) {

			/* Comment */
		case '#':
			break;

			/* Insert Species
			 * S <sid> */
		case 'S':
		{
			int sid;

			sscanf(buff, "%c %d", &event, &sid);
			DPRINT("%c %d\n", event, sid);

			if (insert_species(sid)) {
				DPRINT("%c %d succeeded\n", event, sid);
			}
			else {
				fprintf(stderr, "%c %d failed\n", event, sid);
			}

			break;
		}

		/* Insert population
		 * G <gid> <sid> <cid> */
		case 'G':
		{
			int gid, sid, cid;

			sscanf(buff, "%c %d %d %d", &event, &gid, &sid, &cid);
			DPRINT("%c %d %d %d\n", event, gid, sid, cid);

			if (insert_population(gid, sid, cid)) {
				DPRINT("%c %d %d %d succeeded\n", event, gid, sid, cid);
			}
			else {
				fprintf(stderr, "%c %d %d %d failed\n", event, gid, sid, cid);
			}

			break;
		}

		/* Lowest Common Ancestor
		 * L <sid> <gid1> <gid2> */
		case 'L':
		{
			int sid, gid1, gid2;

			sscanf(buff, "%c %d %d %d", &event, &sid, &gid1, &gid2);
			DPRINT("%c %d %d %d\n", event, sid, gid1, gid2);

			if (lowest_common_ancestor(sid, gid1, gid2)) {
				DPRINT("%c %d %d %d succeeded\n", event, sid, gid1, gid2);
			}
			else {
				fprintf(stderr, "%c %d %d %d failed\n", event, sid, gid1, gid2);
			}

			break;
		}

		/* Merge species
		 * M <sid1> <sid2> <sid3> */
		case 'M':
		{
			int sid1, sid2, sid3;

			sscanf(buff, "%c %d %d %d", &event, &sid1, &sid2, &sid3);
			DPRINT("%c %d %d %d\n", event, sid1, sid2, sid3);

			if (merge_species(sid1, sid2, sid3)) {
				DPRINT("%c %d %d %d succeeded\n", event, sid1, sid2, sid3);
			}
			else {
				fprintf(stderr, "%c %d %d %d failed\n", event, sid1, sid2, sid3);
			}

			break;
		}

		/* Distribute species
		 * D */
		case 'D':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (distribute()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Delete population
		 * K <gid> <sid> */
		case 'K':
		{
			int gid, sid;

			sscanf(buff, "%c %d %d", &event, &gid, &sid);
			DPRINT("%c %d %d\n", event, gid, sid);

			if (delete_population(gid, sid)) {
				DPRINT("%c %d %d succeeded\n", event, gid, sid);
			}
			else {
				fprintf(stderr, "%c %d %d failed\n", event, gid, sid);
			}

			break;
		}

		/* Delete species
		 * F */
		case 'F':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c \n", event);

			if (delete_species()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Evolution to homo sapiens
		 * E */
		case 'E':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (evolution()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Species' statistics
		 * N */
		case 'N':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (species_statistics()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Population statistics
		 * J <sid> */
		case 'J':
		{
			int sid;

			sscanf(buff, "%c %d", &event, &sid);
			DPRINT("%c %d\n", event, sid);

			if (population_statistics(sid)) {
				DPRINT("%c %d succeeded\n", event, sid);
			}
			else {
				fprintf(stderr, "%c %d failed\n", event, sid);
			}

			break;
		}

		/* Print species
		 * P */
		case 'P':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_species()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print populations
			 * X */
		case 'X':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_populations()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print continents
			 * C */
		case 'C':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_continents()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Print homo sapiens
			 * W */
		case 'W':
		{
			sscanf(buff, "%c", &event);
			DPRINT("%c\n", event);

			if (print_homo_sapiens()) {
				DPRINT("%c succeeded\n", event);
			}
			else {
				fprintf(stderr, "%c failed\n", event);
			}

			break;
		}

		/* Empty line */
		case '\n':
			break;

			/* Ignore everything else */
		default:
			DPRINT("Ignoring buff: %s \n", buff);

			break;
		}
	}

	free_all();
	return (EXIT_SUCCESS);
}
