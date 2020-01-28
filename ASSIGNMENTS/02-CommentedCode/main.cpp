///////////////////////////////////////////////////////////////////////////////
//                   
// Author:     Olanrewaju Ayedun
// Email:      lanreayedunjr@gmail.com
// Label:      A02
// Title:      Commenting Interesting Code.
// Course:     CMPS 2143
// Semester:   Spring 2020
//
// Description:
//       This program implements a class that allows a linked list to be used just like 
//       an array. It overloads the "[]" (square brackets) to simulate accessing seperate 
//       array elements, but really it traverses the list to find the specified node using
//       an index value. It also overloads the "+" and "-" signs allowing a user to "add"
//       or "push" items onto the end of the list, as well as "pop" items off the end of our 
//       array. This class is not meant to replace the STL vector library, its simply a project
//       to introduce the beginnings of creating complex / abstract data types. 
//       
// Usage: 
//      - $ ./main filename
//      - This will read in a file containing whatever values to be read into our list/array. 
//      
// Files:            
//      main.cpp    : driver program 
//      list.h      : header file with list defintion
//      list.cpp    : list implementation
/////////////////////////////////////////////////////////////////////////////////#include <iostream>


#include <iostream>;
using namespace std;

int A[100]; // Creates integer type array of size 100.





/**
 *  Struct Name: Node.
 * 
 *  Description: For basic Linked List construction, and for default and overloaded constructors.
 * 
 * Public Methods:
 * All methods in a struct are public.
 * 
 * Usage:
 * Node()           // Default Constructor.  \\
 * Node(int n)     //  Overloaded Constructor.\\
 * 
 */

struct Node
{
    int x; 
    Node *next;
    Node()
    {
        x = -1;
        next = NULL;
    }
    Node(int n)
    {
        x = n;
        next = NULL;
    }
};







/** Class Name : List
 * Description:  
 * This class constructs a linked list from the 
 * previous struct framework along with implementing the
 * push, insert, print and pop methods.
 * 
 * Public Methods:
 *    void      Push(int val)
 *    void      Insert(int val)
 *    void      PrintTail()
 *    int       Pop()
 *    String    Print()
 *    List      operator+(const List &Rhs)
 * 
 * Private Methods:
 *          None. 
 * 
 * 
 * Usage:
 *  Push(5):             // Push 5 into the list.\\
 *  Insert(3):          // Insert 3 into the list.\\
 *  PrintTail():       //   Print Tail value out.  \\
 *  Pop():            // Pops a value from the list.\\
 *  Print():         //    Prints the entire list.   \\    
 *  
 * List ():         // Clones previously created lists \\ 
 *                 // and makes a new list from their   \\
 *                //  union.                             \\
 * 
 * 
 */


class List
{
  private:
    Node *Head;
    Node *Tail;
    int Size;

  public:
    List()
    {
        Head = Tail = NULL;
        Size = 0;
    }



 /**
  * Public : Push
  * 
  * Description:
  *      Inserts a node to the end of the list.
  * 
  * Params:
  *      int val: integer type data to be pushed in.
  * 
  * Returns:
  *    A Black Hole. ( Nothing)
  */


    void Push(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail)
        {
            Head = Tail = Temp;
        }
        else
        {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }


  /**
     * Public : Insert
     * 
     * Description:
     *      Inserts a value into the list.
     * 
     * Params:
     *      int:  data of int type to be inserted
     * 
     * Returns:
     *      Void!
     */
    

     void Insert(int val)
    {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail)
        {
            Tail = Head;
        }
        Size++;
    }


  /**
     * Public : PrintTail
     * 
     * Description:
     *      Prints Tail Value.
     * 
     * Params:
     *      Nonexistent like my GF.
     * 
     * Returns:
     *      Void.
     */

    

    void PrintTail()
    {
        cout << Tail->x << endl;
    }



  /**
     * Public : Print
     * 
     * Description:
     *      Prints the entire list in a nice beautiful string.
     * 
     * Params:
     *  Where is my GF? (Nothing).
     *   
     *  
     * 
     * Returns:
     *       A string of values.
     */


    string Print()
    {
        Node *Temp = Head;
        string list;

        while (Temp != NULL)   // Loop runs until no value is in the list.
        {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    // not implemented 
    int Pop()
    {
        Size--;
        return 0; //
    }


  /**
     * Public : operator+
     * 
     * Description:
     *      Clones previous linked lists, then adds them together.
     * 
     * Params:
     *       const : List passsed in?
     * 
     * Returns:
     *      List  : A new concatenated version of lists
     */

    List operator+(const List &Rhs)
    {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL)
        {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
    int operator[](int index)
    {
        Node *Temp = Head;

        if (index >= Size)
        {
            cout << "Index out of bounds, exiting";
            exit(0);
        }
        else
        {

            for (int i = 0; i < index; i++)
            {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    friend ostream &operator<<(ostream &os, List L)
    {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv)
{
    List L1;    // Creates List1
    List L2;   // Creates list 2

    for (int i = 0; i < 25; i++) // pushes values 0<i>25 into list1.
    {
        L1.Push(i);
    }
 
    for (int i = 50; i < 100; i++) // pushes values 50<i>100 into list2.
    
    {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();         // Prints tail for List 1
    L2.PrintTail();         // Prints tail for list 2

    List L3 = L1 + L2;     // combines list1 and list2 into a new list.
    cout << L3 << endl;   // Print NewList.

    cout << L3[5] << endl; // Prints fifth value in the list ( can do this because of array structure.)
    return 0;
}
