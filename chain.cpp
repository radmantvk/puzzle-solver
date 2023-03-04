#include "chain.h"
#include <cmath>
#include <iostream>


// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
  // clear();
}

/**
 * Inserts a new node after the node pointed to by p in the
 * chain (so p->next is the new node) and returns a pointer to
 * the newly created node.
 * If p is NULL, inserts a new head node to the chain.
 * This function **SHOULD** create a new Node and increase length_.
 *
 * @param p = The new node should be pointed to by p->next.
 *            If p is NULL, the new node becomes the head of the chain.
 * @param ndata = The data to be inserted.
 */
Chain::Node * Chain::insertAfter(Node * p, const Block &ndata) {
  Node *temp = new Node(ndata);
  // if (p == NULL) {
  //   temp->next = head_;
  //   if (head_ != NULL) {
  //     head_->prev = temp;
  //   }
  //   head_ = temp;
  // } else {
  //   p->next = temp;
  //   temp->prev = p;
  //   temp->next = NULL;
  // }
  // length_++;
  // return temp; 

  if (p == NULL) {
    temp->next = head_;
    if (head_ != NULL) {
    temp->next->prev = temp;
    }
    head_ = temp;
  } else {
    if (p->next != NULL) {
    temp->next = p->next;
    p->next->prev = temp;
    temp->prev = p;
    p->next = temp;
    } else {
      temp->prev = p;
      p->next = temp;
      temp->next = NULL;
    }
   }
  length_++;  
  return temp;
}

/**
 * Swaps the position in the chain of the two nodes pointed to
 * by p and q.
 * If p or q is NULL or p==q, do nothing.
 * Change the chain's head pointer if necessary.
 */
void Chain::swap(Node *p, Node *q) {
  if (p == NULL || q == NULL) return;

if (p->next == q || q->next == p) {
  if  (p->next == q && q->next == NULL && p->prev == NULL) {
    p->prev = q;
    q->next = p;
    p->next = NULL;
    q->prev = NULL;
  } else if (q->next == p && p->next == NULL && q->prev == NULL) {
    q->prev = p;
    p->next = q;
    q->next = NULL;
    p->prev = NULL;
  } else if (p->next == q && q->next == NULL) {
    p->prev->next = q;
    q->prev = p->prev;
    p->next = NULL;
    q->next = p;
  } else if (q->next == p && p->next == NULL) {
    q->prev->next = p;
    p->prev = q->prev;
    q->next = NULL;
    p->next = q;
    q->prev = q;
  } else if (p->next == q) {
    p->next = q->next;
    q->prev = p->prev;
    p->prev->next = q;
    p->next->prev = p;
    p->prev = q;
    q->next = p;
  } else if (q->next == p) {
    q->prev->next = p;
    p->next->prev = q;
    p->prev = q->prev;
    q->next = p->next;
    p->next = q;
    q->prev = p;
  }
} else {
  if (p->prev == NULL && q->next == NULL) {
    std::cout << "p->prev == NULL && q->next == NULL\n";
    Node *pnext = p->next;
    Node *qprev = q->prev;
    p->prev = qprev;
    q->next = pnext;
    qprev->next = p;
    pnext->prev = q;
    p->next = NULL;
    q->prev = NULL;
    head_ = q;
  } else if (p->next == NULL && q->prev == NULL) {
    std::cout << "p->next == NULL && q->prev == NULL\n";
    q->next->prev = p;
    p->prev->next = q;
    p->next = q->next;
    q->prev = p->prev;
    p->prev = NULL;
    q->next = NULL;
    head_ = p;
  } else if (q->next == NULL) {
    std::cout << "q->next = NULL\n";
    q->next = p->next;
    p->next->prev = q;
    p->prev->next = q;
    q->prev->next = p;
    Node *pprev = p->prev;
    p->prev = q->prev;
    q->prev = pprev;
    p->next = NULL;   
  } else if (p->next == NULL) {
    std::cout << "p->next == NULL\n";
    p->next = q->next;
    q->next->prev = p;
    q->prev->next = p;
    p->prev->next = q;
    Node *qprev = q->prev;
    q->prev = p->prev;
    p->prev = qprev;
    q->next = NULL;  
  } else if (p->prev == NULL) {
    std::cout << "p->prev == NULL\n";
    p->prev = q->prev;
    q->prev->next = p;
    q->prev = NULL;
    Node *qnext = q->next;
    q->next = p->next;
    p->next = qnext;
    qnext->prev = p;
    head_ = q;
  } else if (q->prev == NULL) {
    std::cout << "q->prev == NULL\n";
    q->prev = p->prev;
    p->prev->next = q;
    p->prev = NULL;
    Node *pnext = p->next;
    p->next = q->next;
    q->next = pnext;
    pnext->prev = q;
    head_ = p;
  } else {
    std::cout << "swap: else case\n";
    p->next->prev = q;
    p->prev->next = q;
    q->next->prev = p;
    q->prev->next = p;
    Node *qnext = q->next;
    Node *qprev = q->prev;
    q->next = p->next;
    q->prev = p->prev;
    p->next = qnext;
    p->prev = qprev;
  }
}
  

}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear() {
  if (head_ == NULL || head_->next == NULL) {
    delete head_;
    head_ = NULL;
  } else {
    Node * temp = head_;
    head_  = head_->next;
    delete temp;
    temp = NULL;
    clear();
  }
}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other) {
  clear();
  if (other.empty()) return;
  Node * tempHead = new Node(other.head_->data);
  Node * head = tempHead;
  Node * tempOther = other.head_;
  for (int i=0; i<other.size()-1; i++) {
    Node * temp = new Node(tempOther->next->data);
    tempOther = tempOther->next;
    tempHead->next = temp;
    tempHead->next->prev = tempHead;
    tempHead = tempHead->next;
  }
  head_ =  head;
}

/* Modifies the current chain: 
 * 1) Find the node with the first (leftmost) block in the unscrambled
 *    image and move it to the head of the chain.
 *	This block is the one whose closest match (to the left) is the
 *	largest.  That is, the distance (using distanceTo) to this block 
 *	is big for all other blocks.
 *	For each block B, find the distanceTo B from every other block
 *	and take the minimum of these distances as B's "value".
 *	Choose the block B with the maximum value over all blocks and
 *	swap its node to the head of the chain.
 *
 * 2) Starting with the (just found) first block B, find the node with
 *    the block that is the closest match to follow B (to the right)
 *    among the remaining blocks, move (swap) it to follow B's node,
 *    then repeat to unscramble the chain/image.
 */
void Chain::unscramble() {
  // for (int i=0;)

  // Node * current = head_;
  // double highestScore = 0;

  // for (int i=0; i < size(); i++ {
  //   double score = calcScore(current)
  //   if (score > highestScore) {
  //     swap(head_, current);
  //   }
  //   current++;
  // }

  // Node* closestMatch = findClosestMatch(head_);

}

// double Chain::calcScore(Node *current) {
//   Node *other = head_;
//   double score = 0;
//   for (int i=0; i<size(); i++ {
//     if(current != other) {
//       score += other->data->distanceTo(*other);
//     }
//   }
//   return score;
// }

// void Chain::findClosestMatch(Node *current) {
//   for (int i=0; i<size(); i++) {

//   }
// }
