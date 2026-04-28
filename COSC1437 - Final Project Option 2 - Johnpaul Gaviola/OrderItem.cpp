#include "OrderItem.h"
using namespace std;

string OrderItem::getType() { return itemtype; }
string OrderItem::getName() { return itemName; }
int OrderItem::getItemScore() { return itemScore; }
int OrderItem::getStock() { return stock; }


void OrderItem::setType(string in) { itemtype = in; }
void OrderItem::setName(string in) { itemName = in; }
void OrderItem::setItemScore(int in) { itemScore = in; }
void OrderItem::setStock(int in) { stock = in; }