#include <iostream>
#include <string>

#include <cstdlib>              //for srand() and rand()
#include <ctime>                //for time()

using namespace std;

struct Element
{
	float value;
	Element* next;				// a pointer of type Element, will point to next Element
};

class List
{
	Element *m_pBegin;

public:
	List() {
		m_pBegin = NULL;
	}
	~List() {
		clear();
	}

	Element* begin() const {        //const because not changing
		return m_pBegin;
	}


	void clear() {
		Element *it = begin();          // First Element of List
		while (it != NULL) {            // Loop till we are end of List
			Element *next = it->next;   // Next element of list
			delete it;                  // Delete current element of list
			it = next;                  // Move to next element
		}
		m_pBegin = NULL;                // Remember to initialize this to NULL!
	}

	int size() const {				//const because not changing antghing
		Element *it = begin();		//begin
		int numElements = 0;		//local counter
		while (it != NULL) {		//while not null
			numElements++;			//increase counter
			it = it->next;			//increment interator, go to next iterator
		}
		return numElements;			//return
	}

	Element* insert(Element *pInsertAfter, float value) {		//inserting the point right before where we want our new point, ex you have a, b, c and after b I want to insert z
		if (pInsertAfter == NULL) return push_front(value);		//we're saying this is going to have a special meaning. If the previous element is null, call push front
		Element *next = pInsertAfter->next;						//say we had a to b to c, and we want to do a to b to z to c, z is now going to point to c
		Element *pNewElement = new Element{ value, next };		//the new thing
		pInsertAfter->next = pNewElement;						
		return pNewElement;
	}

	Element* push_front(float value) {						    // say we have a to b to c and we want soemthing like z to a to b to c  only thing we need to do is change which element is the beggining
		Element *next = m_pBegin;							    //sore beggining in a local variable called next
		Element *pNewElement = new Element{ value, next };	    //create new element and sets two things, value and the next pointer
		m_pBegin = pNewElement;								    //then say the beggining is the new guy
		return pNewElement;									    //return the new guy because likely that soon the user will want to edit this
	}

	/*ALTERNATIVE 3 LINES TO REPLACE THE TOP
	Element *push_front(float value) {
		mp_Begin = new Element{value, m_pBegin };
		return m_pBegin;
	*/

	Element* find(float value) const {						
		Element* it = begin();								    //make iterator, pointer of type Element and set equal to Element pointer of List
		while (it != NULL) {                                    //that it is not null
			if (it->value == value)	                            //if the value inside "it" matches what you want to find,
				return it;			                            //return it
            it = it->next;									    //if not, set the iterator equal to the "next ", (the pointer that points to the next element)
		}								
		return it;										        //return NULL if item not found
	}
};

float generateFloat(float low, float high) {
    float f_rand = low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low)));
    return f_rand;
}

float generateFloat(float low, float high, int decimal_places) {                                            //assuming int is good enough for the purposes of this program
    float f_rand = low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high-low)));        //generated random float
    float multiplier = 1;
    
    for (int i = 0; i < decimal_places; i++) {
        multiplier *= 10;
    }
    
    f_rand = static_cast<float>((static_cast<int>(multiplier * f_rand)) / multiplier);
    return f_rand;
}

// int generateInt(int low, int high) {
//     int generated;

//     int i_rand = low + static_cast <int> (rand()) /( static_cast <int> (RAND_MAX/(high-low)));

//     return generated;
// }

// float printList(List l)
// {
// 	//get first element
// 		Element *it = l.begin();
// 		//print entire list contents
// 		while (it != NULL) {
// 			cout << it->value << " -> ";
// 			it = it->next;
// 		}
// 		cout << "NULL" << endl;
// }

int main()
{
    srand (static_cast <unsigned> (time(0)));

    int init_size = 10;
    float F_LOW = 0.0;
    float F_HIGH = 1.0;
	int decimal_places = 2;
	bool found = false ;
    float f_randTarget = generateFloat(F_LOW, F_HIGH, decimal_places);

	Element* e = NULL;
	List l;
	
	//repeat while random element has not been found
	while (!found)
	{
		//populate list
		for (int i=0; i < init_size; i++) {
			l.push_front(generateFloat(F_LOW, F_HIGH, decimal_places));
		}
		cout << "Pushing " << init_size << " elements into list." << endl;
		cout << "List contents are " ;
		
		//get first element
		Element *it = l.begin();
		//print entire list contents
		while (it != NULL) {
			cout << it->value << " -> ";
			it = it->next;
		}
		cout << "NULL" << endl;

		//find random element
		cout << "Looking for " << f_randTarget << "... " << "It is "; 
		e = l.find(f_randTarget);

		if(e != NULL) {
			cout << "in the list!" << endl;
			cout << "List has " << l.size() << " elements." << endl;
			found = true;
		}
		else
			cout << "not in the list."  << endl;
	}

		l.insert(e, 0.0001);

		//get first element
		Element *it = l.begin();
		//print entire list contents
		while (it != NULL) {
			cout << it->value << " -> ";
			it = it->next;
		}
		cout << "NULL" << endl;

	return 0;
}