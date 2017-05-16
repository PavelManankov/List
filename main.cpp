#include <cassert>
#include <iostream>

struct node
{
    node* prev;
    node* next;
    int data;
};

struct list
{
    list()
    {
        first = nullptr;
        last  = nullptr;

        check_invariant();
    }

    ~list()
    {
        check_invariant();

        node* current = first;
        while (current != nullptr)
        {
            node* next = current->next;
            free(current);
            current = next;
        }
    }

    list(list const&) = delete;
    list& operator=(list const&) = delete;

    void push_back(int data)
    {
        check_invariant();

        node* n = (node*)malloc(sizeof(node));
        n->prev = last;
        n->next = nullptr;
        n->data = data;

            if (last != nullptr)
        {
            assert(last->next == nullptr);
            last->next = n;
        }
        else
        {
            assert(first == nullptr);
            first = n;
        }

        last = n;

        check_invariant();
    }

    void push_front(int data)
    {
        check_invariant();

        node* n = (node*)malloc(sizeof(node));
        n->prev = nullptr;
        n->next = first;
        n->data = data;

        if(first!=nullptr)
          first->prev = n;
        else
        {
            last = n;
        }

        first = n;
    }

    node* insert_before(node* p, int data)
    {
        node* n = (node*)malloc(sizeof(node));
        n->prev = p->prev;
        n->next = p;
        n->data = data;

        if(n->prev == nullptr)
           first = n;
        else
           n->prev->next = n;

        n->next->prev = n;

        return n;
    }

    // node* insert_after(node* p, int data){}

    void erase(node* p)
    {
        if(p->prev == 0)
           first = p->next;
        else
         p->prev->next = p->next;

        if(p->next == 0)
            last = p->prev;
        else
            p->next->prev = p->prev;

        free(p);
    }

    void pop_back()
    {
        check_invariant();

        assert(last != nullptr);

        node* tmp = last;
        if (last->prev != nullptr)
            last->prev->next = nullptr;
        else
            first = nullptr;

        last = last->prev;

        free(tmp);

        check_invariant();
    }

    void check_invariant()
    {
        if (first != nullptr)
            assert(last != nullptr);
        else
            assert(last == nullptr);

        for (node* current = first;
             current != nullptr;
             current = current->next)
        {
            if (current->prev == nullptr)
                assert(current == first);
            else
            {
                assert(current != first);
                assert(current->prev->next == current);
            }

            if (current->next == nullptr)
                assert(current == last);
            else
            {
                assert(current != last);
                assert(current->next->prev == current);
            }
        }
    }

    node* first;
    node* last;
};

void print_all(list const& l)
{
    std::cout << "[";
    if (l.first != nullptr)
    {
        for (node* current = l.first;
             current != nullptr;
             current = current->next)
        {
            std::cout << current->data << ",";
        }
    }
    std::cout << "]" << std::endl;
}

int main()
{
    list l;
    node* n;
 l.push_back(1);
 l.push_back(2);
 l.push_back(3);

 print_all(l);

 n = l.insert_before(l.first,4);
 print_all(l);
 n = l.insert_before(n,5);
 print_all(l);
 n = l.insert_before(n,6);
 print_all(l);
 n = l.insert_before(n,7);
 print_all(l);
l.erase(n->next->next);
 print_all(l);
 return 0;
}
