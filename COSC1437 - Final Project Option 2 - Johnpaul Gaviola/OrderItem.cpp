#include "OrderItem.h"
using namespace std;


string OrderItem::getName() { return itemName; }
int OrderItem::getItemScore() { return itemScore; }
int OrderItem::getStock() { return stock; }
int OrderItem::getExpNeeded() { return ExpNeeded; }
int OrderItem::getCost() { return cost; }


void OrderItem::setItemScore(int in) { itemScore = in; }
void OrderItem::setStock(int in) { stock = in; }
