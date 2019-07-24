#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "NodeList.h"
#include "Resistor.h"
#include "ResistorList.h"
#include "Node.h"
#include "easygl.h"
#include "Rparser.h"

extern easygl window;

NodeList::NodeList() {
    head = NULL;
    totalNode = 0;
}

NodeList::~NodeList() {
    delete head;
}

Node * NodeList::insertNode(int nodeid) {
    Node *r = new Node(nodeid);
    Node *p = head;
    Node *prev = p;

    if (p == NULL) { //the first Node
        head = r;
        totalNode++;
    } else {
        while (p != NULL) {
            if (p->id == nodeid) { // Node alread exists
                delete r;
                return p;
            }
            if (p->id > nodeid && p == head) { // Node ID is smaller than the first Node
                head = r;
                r->next = p;
                totalNode++;
                return r; // return directly
            } else if (p->id > nodeid && p != head) {
                prev->next = r;
                r->next = p;
                totalNode++;
                return r;
            } else {
                prev = p;
                p = p->next;
            }
        }
        // if the NodeID is larger than any existing Node, insert the Node to the end of the list
        prev->next = r;
        totalNode++;
        return r ;
    }
    return r ;
}

void NodeList::printNode(int nodeid, const ResistorList &rl) {
    Node *p = head;

    cout << "Print:" << endl;
    if (p == NULL) {
        cout << "Error: Node " << nodeid << " not found" << endl;
    }

    while (p != NULL) {
        if (p->id == nodeid) {

            if (p->numRes != 0) {
                cout << "Connections at node " << p->id << ": " << p->numRes << " resistor(s)" << endl;

                Resistor * r = rl.gethead();
                while (r != NULL) {
                    if (r->getNode1() == nodeid || r->getNode2() == nodeid) {
                        cout << *r << endl;
                        r = r->next;
                    } else {
                        r = r->next;
                    }
                }
            } else {
                if (p->ifFixV) //if connect to a Voltage Set
                    cout << "Connections at node " << p->id << ": " << p->voltage << " V" << endl;
            }
            return;
        } else
            p = p->next;
    }
    cout << "Error: Node " << nodeid << " not found" << endl;
  
}

void NodeList::printNode(const ResistorList &rl) { //printNode all
    Node *p = head;
    Resistor *r;


    cout << "Print:" << endl;

    while (p != NULL) {
        if (p->numRes != 0) {
            cout << "Connections at node " << p->id << ": " << p->numRes << " resistor(s)" << endl;
            r = rl.gethead();
            while (r != NULL) {
                if (r->node1 == p->id || r->node2 == p->id) {
                    cout << *r << endl;
                }
                r = r->next;
            }
        } else {
            if (p->ifFixV) //if connect to a Voltage Set
            cout << "Connections at node " << p->id << ": " << p->voltage << " V" << endl;
        }
        p = p->next;
    }
}

void NodeList::deleteNode() { // free all memory for Nodes created
    Node *p = head;

    while (p != NULL) {
        head = p->next;
        //cout <<"freeNode:"<<p->id<<endl ;
        delete p;
        p = head;
        totalNode--;
    }
}

void NodeList::deleteResistor() {
    Node *n = head;

    while (n != NULL) {
        n->numRes = 0;
        n = n->next;
    }
}

Node * NodeList::findNode(int nodeid, int &node_index) {
    Node *p = head;

    int i = 0;

    while (p != NULL) {
        node_index = i;

        if (p->id == nodeid)
            return p;
        else
            p = p->next;
        i++;
    }
    return NULL;
}

Node * NodeList::findNode(int &total) {
    total = totalNode;
    return head;
}

void NodeList::draw() {
    Node *p;
    int interval;

    if (totalNode == 0)  // if no Node
        return ;
    
    interval = max_width / totalNode;

    p = head;
    int i = 0;
    char ss[20];

    while (p != NULL) {
        // draw node one by one
        window.gl_setcolor(BLACK);
        window.gl_drawrect(98 + interval*i, 148, interval * i + 142, max_heigth - 28) ;
        window.gl_setcolor(LIGHTGREY);
        window.gl_fillrect(100 + interval*i, 150, interval * i + 140, max_heigth - 30);

        // print Node name + Node voltage
        sprintf(ss, "%s %d", "Node", p->id);
        window.gl_setcolor(BLACK);
        window.gl_drawtext(100 + interval*i, 100, ss, 400);

        sprintf(ss, "%-5.2f %s", p->voltage, "V");
        window.gl_drawtext(100 + interval*i, 60, ss, 400);
        i++;
        p = p->next;
    }
}

bool NodeList::solve(const ResistorList &reslist) {

    Node *node_p;
    Resistor *res_p;
    int node2;
    int reSolve = 1, haveVoltage = 0;
    double v1 = 0, r1 = 0;
    int noid;

    //clear all non-FixVoltage to re-calculate the voltage on node
    node_p = head;
    while (node_p) {
        if (node_p->ifFixV) {
            haveVoltage = 1;
            break;
        } else
            node_p->voltage = 0;
        node_p = node_p->next;
    }

    // calculate the voltage
    while (reSolve && haveVoltage) {
        reSolve = 0;
        haveVoltage = 0;
        node_p = head;
        while (node_p != NULL) {
            v1 = 0;
            r1 = 0;
            if (!node_p->ifFixV) {
                res_p = reslist.gethead();
                while (res_p != NULL) {
                    if (node_p->id == res_p->node1) {
                        node2 = res_p->node2;
                    } else if (node_p->id == res_p->node2)
                        node2 = res_p->node1;
                    else {
                        res_p = res_p->next;
                        continue;
                    }

                    v1 = (findNode(node2, noid))->voltage / res_p->resistance + v1;
                    r1 = r1 + 1 / (res_p->resistance);
                    res_p = res_p->next;
                }

                if (r1 == 0) //no resistor connected to the node
                    node_p->voltage = 0;
                else {
                    if (fabs(v1 / r1 - node_p->voltage) > MIN_INTERATION_CHANGE)
                        reSolve = 1;
                    if (v1 / r1 != 0)
                        haveVoltage = 1;
                    node_p->voltage = v1 / r1;
                }
            } else
                haveVoltage = 1;
            node_p = node_p->next;
        }
    }

    if (haveVoltage == 0)
        return false  ;
    else
        return true ;
}

void NodeList::printVoltage() {
    Node *node_p = head;
    
    cout << "Solve:" << endl;
    while (node_p != NULL) {
        cout << "Node " << node_p->id << ":" << node_p->voltage << "V" << endl;
        node_p = node_p->next;
    }
}
            
            
bool NodeList::setV(int nodeid, double vol, bool boolean) {
    Node *p;

    p = head ;
    while (p != NULL) {
        if (p->id == nodeid) {
            p->voltage = vol ;
            p->ifFixV = boolean ;            
            return true;
        } else
            p = p->next;
    }
    return false ; 
}

