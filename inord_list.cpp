#include "inord_list.h"

inord_list::inord_list()
{
	//initializing the list
	current = NULL;
	head = NULL;
	tail = NULL;
};



/// ////////////////////////////////////////////////////////////////////////////////

bool inord_list::insert(string e, int word_n, int line_n)
{
	//step 1 allocating and storing the input
	link addednode;
	link pred;
	addednode = new Node;
	if (!addednode)
		return false; //allocation failed

	addednode->elem = e;
	addednode->word_number = word_n;
	addednode->line_number = line_n;
	//step 2 check if empty list make it the head of the list;
	if (current == NULL) // empty list
	{
		head = addednode;
		current = addednode;
		tail = addednode;
		addednode->next = NULL;
	}
	else if (addednode->elem < head->elem) //  added become at the begining of the list
	{
		addednode->next = head;
		head = addednode;
		current = head;
	}
	else if (addednode->elem == head->elem) // added comes after head directly
	{
		addednode->next = head->next;
		head->next = addednode;
	}
	else if (addednode->elem >= tail->elem) // added become at the end of the list
	{
		tail->next = addednode;
		addednode->next = NULL;
		tail = addednode;
	}
	else
	{

		pred = head;
		while (pred->next->elem <= addednode->elem)
		{
			pred = pred->next;
		}
		addednode->next = pred->next;
		pred->next = addednode;
	}
	return true;
};

/// ////////////////////////////////////////////////////////////////////////////////

bool inord_list::first(string &e, int &word_n, int &line_n)
{
	if (head == NULL) // empty list
		return false;
	else
	{
		current = head;
		e = current->elem;
		word_n = current->word_number;
		line_n = current->line_number;
		return true;
	}
	
};

/// ////////////////////////////////////////////////////////////////////////////////

bool inord_list::Next(string& e, int& word_n, int& line_n)
{
	if (head == NULL) //empty list
		return false;
	else if ((current == NULL) || (current == tail)) //first is not done even once (current==null), or we stand at the end of the list
		return false;
	else
	{
		current = current->next;
		e = current->elem;
		word_n = current->word_number;
		line_n = current->line_number;
		return true;
	}
};

/// ////////////////////////////////////////////////////////////////////////////////

int inord_list::distinct() //Prints the number of distinct words in the file
{
	int countdistinct = 0;
	int number=0;
	current = head;
	link inst = current;
	while(inst != NULL) // not empty or reached the end of the list
	{	
		current = head;

		if (inst != head) //after first time of being in the fucntion (inst is not the head any more)
		{
			int number = 0;
			while (inst != current)  // loop continue until current reaches inst
			{
				if (inst->elem == current->elem) 
				{
					number++;
					break;
				}
				else
				{
					current = current->next;
				}
			}
			
			if (number == 0)
			{
				countdistinct++;
			}
			inst = inst->next;
		}

		else if ((inst == head)) // first time in the function
		{
	     countdistinct++;
		 inst = inst->next;
		}

	
	}

	return countdistinct;
};

/// ////////////////////////////////////////////////////////////////////////////////

string inord_list::freq() // Prints the word(s) that had occurred the most
{
	current = head;
	link inst = current;
	link temp = inst;
	link pred=inst;
	int currentvalue=0;
	int saved = 0;

	bool valid = true;
	string word;

	if (current == NULL)//empty list (we will check it lateerrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr)
	{
		return "false"; 
	}


	while (inst != NULL) //loop continue as long as inst not reaches after tail (the mother loop to rotate across all elements in the list)
	{
		
		temp = head;

		while (temp!=NULL) // the inside loop that compares element with rest of elemnts and get how mane times it was repeated
		{
	
			 if ((inst->elem == "a") || (inst->elem == "an") || (inst->elem == "the") || (inst->elem == "in") || (inst->elem == "on") || (inst->elem == "of") || (inst->elem == "and") || (inst->elem == "is") || (inst->elem == "are"))
			 {
				 valid = false;
				 break;
			 }
			 if ((temp->next != NULL) && (inst == head) && (inst->elem == temp->next->elem) && (inst != temp)) //inst is equal to head 
			 {
				 currentvalue++;
				 temp = temp->next;
				 valid = true;

			 }
			 else if ((inst->elem == temp->elem) && (inst != temp)) //same as above but for inst is not equal to head
			 {
				 currentvalue++;
				 temp = temp->next;
				 valid = true;
			 }
			 else
			 {
				 temp = temp->next;
				 valid = true;
			 }
		}
		if (currentvalue > saved)
		{
			saved = currentvalue;
			word = " ";
			word = inst->elem;
			valid = false;
			currentvalue = 0;
			
		}

		if ((currentvalue == saved) && (valid == true) && (inst->elem != word))
		{
			if (pred->elem != inst->elem)
			{
				word = word + " " + inst->elem;
			}
		}
		pred = inst;
		inst = inst->next;
		currentvalue = 0;
		
	}
	return word;;
};

////////////////////////////////////////////////////////////////////////////////////////////


int inord_list::countcertain(string myword, int totalwordscount) ////prints the number of myword occurrence in the file
{
	current = head;
	int counter = 0;

	if (current == NULL)//empty list
	{
		return counter;
	}

	if (myword == "") // no input word
	{
		return counter;
	}


	int len = myword.length();  //this and the for loop used to lowercase each char
	for (int i = 0; i <= len - 1; i++)
	{
		myword[i] = tolower(myword[i]);
	}


	while (current != NULL)
	{
		for (int i = 0; i <= totalwordscount - 1; i++)  // used to loop to get all words in the list (each node in the list)
		{
			if (myword == current->elem)
			{
				counter++;
			}
			current = current->next;
		}
		
	}

	
	return counter;
};


/////////////////////////////////////////////////////////////////////////////



bool inord_list::startingwith(string myword, int totalwordscount)
{
	current = head;
	bool again = false;
	string temp = "";
	int repeated = 0;

	if (current == NULL)//empty list
	{
		return false;
	}

	if (myword == "") // no input word
	{
		return false;
	}

	int len = myword.length();  //this and the for loop used to lowercase each char
	for (int i = 0; i <= len - 1; i++)
	{
		myword[i] = tolower(myword[i]);
	}


	while (current != NULL)
	{

		for (int i = 0; i <= totalwordscount - 1; i++) // used to loop to get all words in the list (each node in the list)
		{
			if (current == NULL)
			{
				break;
			}

			repeated = 0;
			
			int elemlen = current->elem.length();
			if (len <= elemlen)  // to check if myword is larger than the elements or not
			{

				temp = current->elem.substr(0,len);

				if (myword == temp)      /// from here till the end it checks  if myword exists in a word and how many times it occured
				{
					link stopped = current;
					repeated = countcertain(current->elem, totalwordscount);
					current = stopped;
					if (again == false)
					{
						cout << current->elem << ":" << " " << repeated;
						again = true;
					}
					else
						cout << "\t" << current->elem << ":" << " " << repeated;

				}
				if ((repeated == 0) || (repeated == 1))
				{
					i = i;
					current = current->next;
				}
				else
				{
					for (int m = 1; m <= repeated; m++)
					{
						current = current->next;
					}
					for (int m = 1; m <= repeated - 1; m++)
					{
						i++;
					}

				}
			}
			else
			{
				current = current->next;
			}


		}

	}

	if (again == false)
	{
		return false;
	}

	return true;
};


/// //////////////////////////////////////////////


bool inord_list::containing(string myword, int totalwordscount)
{

	current = head;
	bool again = false;
	string temp = "";
	int repeated = 0;
	if (current == NULL)//empty list
	{
		return false;
	}

	if (myword == "") // no input word
	{
		return false;
	}

	int len = myword.length();  //this and the for loop used to lowercase each char
	for (int i = 0; i <= len - 1; i++)
	{
		myword[i] = tolower(myword[i]);
	}


	while (current != NULL)
	{
		for (int i = 0; i <= totalwordscount - 1; i++) // used to loop to get all words in the list (each node in the list)
		{
			if (current == NULL)
			{
				break;
			}

			repeated = 0;
			temp = "";     //reset the temp for each node element
			int elemlen = current->elem.length();
			if (len <= elemlen)  // to check if myword is larger than the elements or not
			{

				for (int j = 0; j <= elemlen-len; j++)  //used to rotate across elem chars //elem=4
				{
					temp = current->elem.substr(j, len);
					if (temp == myword)  /// from here till the end it checks  if myword exists in a word and how many times it occured
					{
						link stopped = current;
						repeated = countcertain(current->elem, totalwordscount);
						current = stopped;
						if (again == false)
						{
							cout << current->elem << ":" << " " << repeated;
							again = true;
							break;
						}
						else
						{
							cout << "\t" << current->elem << ":" << " " << repeated;
							break;
						}
					}

				}

				if ((repeated == 0) || (repeated == 1))
				{
					i = i;
					current = current->next;
				}
				else
				{
					for (int m = 1; m <= repeated; m++)
					{
						current = current->next;
					}
					for (int m = 1; m <= repeated - 1; m++)
					{
						i++;
					}

				}
			}
			else
			{
				current = current->next;
			}


		}

	}
	if (again == false)
	{
		return false;
	}

	return true;
};

////////////////////////////////

bool inord_list::search(string myword, int totalwordscount)
{

	current = head;
	int linenumber = 0;
	bool again = false;
	bool found = false;

	string temp = "";
	int repeated = 0;
	if (current == NULL)//empty list
	{
		return false;
	}

	if (myword == "") // no input word
	{
		return false;
	}

	int len = myword.length();  //this and the for loop used to lowercase each char
	for (int i = 0; i <= len - 1; i++)
	{
		myword[i] = tolower(myword[i]);
	}


	while (current != NULL)
	{
		for (int i = 0; i <= totalwordscount - 1; i++) // used to loop to get all words in the list (each node in the list)
		{
			bool equal = false;
			bool occured = false;
			if (current == NULL)
			{
				break;
			}

			repeated = 0;
			temp = "";     //reset the temp for each node element
			int elemlen = current->elem.length();
			if (len <= elemlen)  // to check if myword is larger than the elements or not
			{
				
				for (int j = 0; j <= elemlen - len; j++)  //used to rotate across elem chars //elem=4
				{
					temp = current->elem.substr(j, len);
					if (temp == myword)  /// from here till the end it checks  if myword exists in a word and how many times it occured
					{
						found = true;
						link stopped = current;
						repeated = countcertain(current->elem, totalwordscount);
						current = stopped;
						if (again == false)
						{
							cout << current->elem << ":" << "\t" << "lines";
							for (int clock = 1; clock <= repeated; clock++)
							{
								int saver = current->line_number;
								if ((equal == false) || (occured == false))
								{
									cout << " " << current->line_number;
									occured = true;
								}
								if (clock != repeated)
								{
									current = current->next;
									i++;
									if (saver == current->line_number)
									{
										equal = true;
									}
									else
										equal = false;
								}
							}
						    //i--;
							again = true;
							break;
						}
						else
						{
							cout <<endl<<current->elem << ":" << "\t" << "lines";
							for (int clock = 1; clock <= repeated; clock++)
							{
								int saver = current->line_number;
								if ((equal == false) || (occured == false))
								{
									cout << " " << current->line_number;
									occured = true;
								}
								if (clock != repeated)
								{
									current = current->next;
									i++;
									if (saver == current->line_number)
									{
										equal = true;
									}
									else
										equal = false;
								}
							}
							//i--;
						}
						break;
					}

				}
				if (i <= totalwordscount - 1)
				{
						if (current->next != NULL)
							current = current->next;
						else
							current = NULL;
				}
				else
					current = NULL;
			}
			else
			{
				current = current->next;
			}


		}

	}

	if (found == false)
	{
		return false;
	}
	return true;
};

inord_list::~inord_list()
{
	current = head;
	link additional = current;
	while (current != NULL)
	{
		additional = current->next;
		delete current;
		current = additional;
    }
};
