/*
Author Name: Midyan Elghazali
File Name: CardShop.cpp
Date Created/Modified: 04/04/2023
*/
#include "CardShop.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
CardShop::CardShop(std::string input_file_name) 
{
  std::ifstream fin(input_file_name);
  if (fin.fail())
  {
    std::cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  //we don't use the first line
  std::string ignore;
  getline(fin, ignore);

  //the columns of the csv associated with the data members
  std::string name, type, race, attribute;
  int level_rank, atk, def;

  std::string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');
  
    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    std::istringstream(temp_string) >> temp_int;
    def = temp_int;

    //create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    //add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
//Deallocate and delete items
void CardShop::clear()
{
  for (int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

//destructor
CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line
void CardShop::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << std::endl;
    }
  }
}


//@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

template <typename Comparator>
int CardShop::quickSort(Comparator comp, std::string key){
  int swaps{0};
  quicky(comp, key, 0, item_count_ - 1, swaps);
  return swaps; 
}

template <typename Comparator>
void CardShop::quicky(Comparator comp, std::string key, int first, int last, int &swaps){
  if (last <= first)
    return;

  int pivotIndex = partition(comp, key, first, last, swaps);
  quicky(comp, key, first, pivotIndex - 1, swaps);
  quicky(comp, key, pivotIndex + 1, last, swaps);
}

template <typename Comparator>
int CardShop::partition(Comparator comp, std::string key, int first, int last, int &swaps){
  Node<YGOCard*>* pivot = getPointerTo(last);
  int i = first - 1;
  for(int j = first; j <= last - 1; j++){
    if(key == "atk"){
      if(comp(getPointerTo(j)->getItem()->getAtk(), pivot->getItem()->getAtk())){
        i++;
        swap(i, j);
        swaps++;
      }
    }
    else if(key == "def"){
      if(comp(getPointerTo(j)->getItem()->getDef(), pivot->getItem()->getDef())){
        i++;
        swap(i, j);
        swaps++;
      }
    }
  }
  i++; 
  swap(i, last);
  swaps++;
  return i;
}
//sorts using the bubble sort algorithm
template <typename Comparator>
int CardShop::bubbleSort(Comparator comp, std::string key){
  int swaps{0};
  bool swapped = true;
  while(swapped){ 
  swapped = false;
  for(int j = 0; j < getLength()-1 ; j++){
    if(key == "atk"){
      if(comp(getItem(j+1)->getAtk(),getItem(j)->getAtk() )){
        swap(j + 1, j);
        swapped = true;
        swaps++;
      }
    }
    else if(key == "def"){
      if(comp(getItem(j+1)->getDef(), getItem(j)->getDef())){
        swap(j+1,j );
        swapped = true;
        swaps++;
      }
    }
  }
}
  return swaps;
}

//sorts using the selection sort algorithm
template <typename Comparator>
int CardShop::insertionSort(Comparator comp, std::string key){
  int swaps{0};
  for(int i = 0; i < item_count_; i++){
    int j = i;
    if(key == "atk")
    {
      while(j > 0 && comp(getItem(j)->getAtk(), getItem(j-1)->getAtk())){
      swap(j-1, j );
      swaps++;
      j--;
      }
    }
    if(key == "def")
    {
      while(j > 0 && comp(getItem(j)->getDef(), getItem(j-1)->getDef())){
      swap(j-1, j );
      swaps++;
      j--;
      }
    }
  }
  return swaps;
}

//Merge sort helper function
template <typename Comparator>
int  CardShop::mergeSort(Comparator comp, std::string key ){
  int swaps{0};
  mergeSortHelper(comp, key, 0, item_count_ - 1, swaps);
  return swaps;
} 

//merge sort helper function
template <typename Comparator>
void CardShop::merge( Comparator comp, std::string key, int left_index, int middle_index, int right_index, int& swap)
{
    YGOCard* Holder[right_index];
    int left_start = left_index;
    int right_start = middle_index + 1;
    int counter_index = left_index;

    while (left_start <= middle_index && right_start <= right_index)
    {
        if (key == "atk" && comp(getPointerTo(left_start)->getItem()->getAtk(), getPointerTo(right_start)->getItem()->getAtk()))
        {
            Holder[counter_index] = getPointerTo(left_start++)->getItem();
            counter_index++;
        }
        else if (key == "def" && comp(getPointerTo(left_start)->getItem()->getDef(), getPointerTo(right_start)->getItem()->getDef()))
        {
            Holder[counter_index] = getPointerTo(left_start++)->getItem();
            counter_index++;
        }
        else
        {
            Holder[counter_index] = getPointerTo(right_start++)->getItem();
            counter_index++;

        }
    }

    while (left_start <= middle_index)
    {
        Holder[counter_index] = getPointerTo(left_start++)->getItem();
        counter_index++;
    }

    while (right_start <= right_index)
    {
        Holder[counter_index] = getPointerTo(right_start++)->getItem();
        counter_index++;
    }

    for (int i = left_index; i <= right_index; i++)
    {
        getPointerTo(i)->setItem(Holder[i]);
    }
    swap++;
}

//merge sort helper function
template <typename Comparator>
void CardShop::mergeSortHelper(Comparator comp, std::string key, int l, int r, int &swaps){
  if (l < r) {
    int m = l + (r - l) / 2;

    mergeSortHelper(comp, key, l, m, swaps);
    mergeSortHelper(comp, key, m + 1, r, swaps);

    merge(comp, key, l, m, r, swaps);
  }
}