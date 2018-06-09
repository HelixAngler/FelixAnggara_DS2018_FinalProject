#ifndef HASHING
#define HASHING
#include <iostream>
#include <string>
#include "bstemergency.h"
template<class T>
//WARNING: The hash table is really unstable. Some certain value from the hash function can cause crash. Any help to fix the problem is welcome.
class Hash
{
	private:
		unsigned int size;
		AVLtree<T> *hashtab;
		//hash function
		unsigned int hashing(string identifier){
			unsigned int hashresult=0;
			unsigned int temp;
			unsigned int halfsize = this->size/2;

			for(int i = 0;i < identifier.length(); i++){
				temp = (unsigned int)(identifier[i]);
				hashresult = hashresult + (temp % halfsize);

			}
			while(hashresult >= size){
				hashresult = hashresult - this->size;
			}
			//'hashresult==...' must to be added or changed depending by the hash table size and modulo value
			/*if(hashresult==0 || hashresult==117 || hashresult==119 || hashresult==115 || hashresult == 121 || hashresult == 118){
                hashresult=+1;
			}*/
			return hashresult;
		}
	public:
	    //constructor
		Hash(const int &si=1000)
		{
			this->size=si;
			this->hashtab = new AVLtree<T>[si];

		}
		//add method
		bool add(string idtifier,T value){
			unsigned int hashcoord=this->hashing(idtifier);

                /*if(this->hashtab[hashcoord]==NULL){
                    hashtab[hashcoord]=new AVLtree<T>();

                }*/
                return this->hashtab[hashcoord].insert(value);

		}
		//delete method
		void del(string idtifier, T value){
		    unsigned int hashcoord=this->hashing(idtifier);

                //if(this->hashtab[hashcoord]!=NULL){
                    hashtab[hashcoord].deleteKey(value);
                //}

        }
        //data retrieval method
        T get_thing(string idtifier, T value){
		    T retrieval;
		    unsigned int hashcoord=this->hashing(idtifier);

                //if(this->hashtab[hashcoord]!=NULL){
                    retrieval = hashtab[hashcoord].findin(value);
                //}

			return retrieval;
        }
        //search method
        bool checkav(string idtifier, T value){
            bool retrieval = false;
		    unsigned int hashcoord=this->hashing(idtifier);

                //if(this->hashtab[hashcoord]!=NULL){
                    retrieval = hashtab[hashcoord].check(value);
                //}

			return retrieval;
        }
};
#endif
