/*
Filename:  Deck.h
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class Specification
*/

#ifndef DECK_H
#define DECK_H

//System libraries
#include  <iostream>
using namespace std;


template <typename T>
class Deck {
  private:
    //Private variables defined here
    T* cards;
    int size;
    int MaxSize;
    int currentIndex; // Index of the next card to draw
  public:
    //constructors
    Deck(int maxSize){
        this->MaxSize = maxSize;
        size = 0;
        currentIndex = 0;
        cards = new T[MaxSize];
    }

    //destructors
    ~Deck() {
        delete[] cards;
    }

    //Accessors
    
    //Mutators

    //Operator overloads


    //Member functions
    void addCard(const T& card) {
        if (size < MaxSize) {
            cards[size++] = card;
        } else {
            cout << "Deck is full. Cannot add more cards." << endl;
        }
    }
    T drawCard() {
        if (size == 0) {
            cout << "Deck is empty. Cannot draw a card." << endl;
            return T(); // Return default-constructed card
        }
        T card = cards[currentIndex];
        currentIndex = (currentIndex + 1) % size; // Move to the next card, wrap around if at the end
        return card;
    }

    void shuffle() {
        // Implement a simple shuffle algorithm (e.g., Fisher-Yates)
        for (int i = size - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(cards[i], cards[j]);
        }
    }

    void initializeDeck(const T* cardArray, int arraySize) {
        if (arraySize > MaxSize) {
            cout << "Card array size exceeds deck capacity. Cannot initialize deck." << endl;
            return;
        }
        for (int i = 0; i < arraySize; i++) {
            cards[i] = cardArray[i];
        }
        size = arraySize;
        currentIndex = 0;
    }

};

#endif  // DECK_H