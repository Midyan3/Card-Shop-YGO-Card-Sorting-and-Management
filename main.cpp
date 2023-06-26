
#include "CardShop.cpp"
int main(){ 
    CardShop list("cards.csv");
    CardShop list2("cards.csv");
    CardShop list3("cards.csv");
    list2.display();
    // add YGOCard objects to the list
    std::cout<<list2.mergeSort(std::greater<int>(), "atk")<<std::endl;
    //std::cout<<list3.quickSort(std::greater<int>(), "atk")<<std::endl;
    
    std::cout<<"--------------------------------------------"<<std::endl;
    list2.display();
}