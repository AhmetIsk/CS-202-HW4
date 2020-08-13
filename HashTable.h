/**
* Author : Ahmet Isik
* ID: 21702226
* Section : 2
* Assignment : 4
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H
enum CollisionStrategy {LINEAR, QUADRATIC, DOUBLE};
enum Condition { OCCUPIED, DELETED, EMPTY }; // to determine the condition of node
class HashTable
{
    public:
        HashTable( const int tableSize, const CollisionStrategy option );
        virtual ~HashTable();
        bool insert( const int item );
        bool remove( const int item );
        bool search( const int item, int& numProbes );
        void unsuccSearch( int index, int& probes ); // takes index of the hashArr and finds the number of probes needed for unsuccessful search
        void display();
        void analyze( int& numSuccProbes, int& numUnsuccProbes );


    protected:

    private:
        CollisionStrategy option;
        int numOfElements;
        int size;
        struct HashNode {
            Condition current;
            int number;
        };

        HashNode *hashArr;
};

#endif // HASHTABLE_H
