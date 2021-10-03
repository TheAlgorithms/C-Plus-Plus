/*
Made by Anuran Roy (https://github.com/anuran-roy)
*/

#include <bits/stdc++.h>

#include <chrono>
#include <ctime>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#define ll long long int
// using namespace std;

std::hash<std::string> hashfunc;

typedef struct content  // The metadata of a block
{
    std::string lastblock;
    ll bno;
} block;

std::string getTime() {  // method to get the current time
    return std::__cxx11::to_string(time(nullptr));
}

void proofOfWork(int time) {  // a simple proof-of-work algorithm
    std::cout << "\nSolving the proof of work puzzle worth " << time / 1000
              << "seconds...\n\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

class Transaction  // The smallest unit of a blockchain - The Transaction
{
 public:
    Transaction() {}
    Transaction(std::string sender, std::string receiver, float amt) {
        senderAddress = sender;
        receiverAddress = receiver;
        amount = amt;
    }

    void printDetails() {
        std::cout << "Sender:\t" << senderAddress << std::endl;
        std::cout << "Receiver:\t" << receiverAddress << std::endl;
        std::cout << "Amount:\t" << amount << std::endl;
    }
    float getAmount() { return amount; }
    std::string getReceiver() { return receiverAddress; }
    std::string getSender() { return senderAddress; }

 protected:
    std::string senderAddress;
    std::string receiverAddress;
    float amount;
};

class Node  // The encapsulation of a Transaction
{
 public:
    Node(const Transaction &a, ll num, std::string lastblock) {
        nodeTransaction = a;
        current.lastblock = lastblock;
        current.bno = num;
    }
    block getDetails() { return current; }
    void printDetails() {
        std::cout << "\nTransaction Info:\n";
        nodeTransaction.printDetails();

        std::cout << "\n\nBlock Info:\n";
        std::cout << "Block number:\n" << current.bno << std::endl;
        std::cout << "Hash of last block:\n" << current.lastblock << std::endl;
    }
    Transaction getTransaction() { return nodeTransaction; }

 private:
    Transaction nodeTransaction;
    block current;
};

std::string hashNode(Node a) {
    block details = a.getDetails();
    std::string t =
        getTime() + details.lastblock + std::__cxx11::to_string(details.bno);

    return std::__cxx11::to_string(hashfunc(t));
}

bool NodeEquals(Node a, Node b) {
    bool resp = false;
    std::string t1_sender = a.getTransaction().getSender();
    std::string t1_receiver = a.getTransaction().getReceiver();
    float t1_amount = a.getTransaction().getAmount();

    std::string t2_sender = b.getTransaction().getSender();
    std::string t2_receiver = b.getTransaction().getReceiver();
    float t2_amount = b.getTransaction().getAmount();

    ll t1_bno = a.getDetails().bno;
    std::string t1_lastblock = a.getDetails().lastblock;

    ll t2_bno = b.getDetails().bno;
    std::string t2_lastblock = b.getDetails().lastblock;

    if (t1_sender == t2_sender) {
        if (t1_receiver == t2_receiver) {
            if (t1_amount == t2_amount) {
                if (t1_bno == t2_bno) {
                    if (t1_lastblock == t2_lastblock) {
                        resp = true;
                    }
                }
            }
        }
    }

    return resp;
}
class Ledger  // The sequenced chain of blocks
{
 public:
    std::vector<Node> getLedger() { return ledger; }
    void setLedger(std::vector<Node> &a) { ledger.assign(a.begin(), a.end()); }
    void addToLedger(const Node &a) {
        const Node b = a;
        ledger.push_back(b);
    }
    ll ledgerLength() { return ledger.size(); }
    void printInstance(int i) { ledger[i].printDetails(); }
    Node getInstance(int i) { return ledger[i]; }

 private:
    std::vector<Node> ledger;
};

class User  // A user in the blockchain network
{
 public:
    User(std::string seed, float amt) {
        address = std::__cxx11::to_string(hashfunc(seed));
        balance = amt;
    }
    std::string getAddress() { return address; }
    bool receiveToken(float amt) {
        if (amt >= 0.0) {
            balance += amt;
            return true;
        } else {
            std::cout << "\n\nCannot receive negative amount of tokens.\n\n";
            return false;
        }
    }
    bool sendToken(float amt) {
        if (amt <= balance && amt >= 0.0) {
            balance -= amt * 1.0;
            return true;
        } else {
            return false;
        }
    }
    void setUserLedger(const std::vector<Node> &a) {
        ledgerCopy.assign(a.begin(), a.end());
    }
    void getDetails() {
        std::cout << "\nUser address:\t" << address;
        std::cout << "\nBalance:\t" << balance << "\n\n";
        std::cout << "\nLedger details for user:" << std::endl;
        for (int i = 0; i < ledgerCopy.size(); i++)
            ledgerCopy[i].printDetails();
    }
    std::vector<Node> getUserLedger() { return ledgerCopy; }

 private:
    std::string address;
    float balance;
    std::vector<Node> ledgerCopy;
};

User makeUser(float amt) {
    std::string seed;
    std::cout << "\n\nEnter seed phrase:\n\n";
    std::cin >> seed;
    User newUser = User(seed, amt);
    return newUser;
}

bool compareLedgers(User a, User b) {
    // std::cout << "\ncompareLedgers() invoked!\n";
    std::vector<Node> l1;
    // std::cout << "Going to invoke assign() for l1\n\n";
    l1 = a.getUserLedger();
    // l1.assign(a.getUserLedger().begin(), a.getUserLedger().end());
    std::vector<Node> l2;
    // std::cout << "Going to invoke assign() for l2\n\n";
    l2 = b.getUserLedger();
    // l2.assign(b.getUserLedger().begin(), b.getUserLedger().end());

    if (l1.size() == l2.size()) {
        for (int i = 0; i < l1.size(); i++) {
            if (NodeEquals(l1[i], l2[i])) {
                std::cout << "";
            } else {
                return false;
            }
        }
        return true;
    }
    return false;
}
class Contract : protected Transaction {
    // You can customize this class by extending it, but it should always
    // inherit Transaction. Also, it MUST contain the boolean functions
    // validate() and transit(), returning a boolean value. Validate must call
    // transit() An atomic contract (ie., the most basic contract) involves two
    // users and a transaction.
 public:
    Contract() {
        // num = 0;
    }
    bool validate(User &a, User &b, Node &n) {
        // num++;
        // if (num%2) // Implementation of a smart contract that returns true on
        // alternate valid nodes
        //     return false;
        // else{
        //     if(transit(a, b, n.getTransaction().getAmount())){
        //         return true;
        //     }
        //     else{
        //         return false;
        //     }
        // }
        if (transit(a, b, n.getTransaction().getAmount())) {
            return true;
        } else {
            return false;
        }
    }

 protected:
    bool transit(User &sender, User &receiver, float amt) {
        if (sender.sendToken(amt)) {
            receiver.receiveToken(amt);
            std::cout << "\n\nTransaction complete!\n\n";
            return true;
        } else {
            std::cout
                << "\n\nTransaction couldn't be completed. Check the balance "
                   "of sender, and the amount of tokens sent.\n\n";
            return false;
        }
    }
    // int num;
};

Node makeNode(std::string usr1, std::string usr2, float amt, std::string THash,
              ll bnum) {
    Transaction tx = Transaction(usr1, usr2, amt);
    Node nNode = Node(tx, bnum, THash);

    return nNode;
}

void propagate() { std::cout << ""; }

int main() {
    Ledger ledgerInstance = Ledger();

    std::cout << "\nEnter number of mock transactions to generate:\n";
    int n;
    std::cin >> n;

    Node genesisBlock = Node(Transaction("__init__", "__init__", 0.00), 1,
                             std::__cxx11::to_string(hashfunc("0")));
    std::cout << "\n"
              << "Genesis block:\nHash: " << hashNode(genesisBlock) << "\n";
    std::string THash = hashNode(genesisBlock);
    Contract democontract = Contract();

    std::cout << "\n\nEnter balance of sender to initialize with:";
    float a;
    std::cin >> a;
    User u1 = makeUser(a);
    std::string sender = u1.getAddress();

    std::cout << "\n\nEnter balance of receiver to initialize with:";
    std::cin >> a;
    User u2 = makeUser(a);
    std::string receiver = u2.getAddress();

    ledgerInstance.addToLedger(genesisBlock);

    for (int i = 0; i < n - 1; i++) {
        std::cout << "\n\n-----------------------------\n\nMaking new block..."
                  << std::endl;
        std::cout << "Hash of last block: " << THash << std::endl;

        std::cout << "Enter amount to be transacted for Transaction ID "
                  << std::__cxx11::to_string(i + 1) << ":\n";
        std::cin >> a;
        Node nd = makeNode(sender, receiver, a * 1.00, THash, i + 2);
        nd.printDetails();
        if (democontract.validate(u1, u2, nd)) {
            THash = hashNode(nd);
            std::cout << "Hash of current block: " << THash
                      << "\n\n-----------------------------\n\n";
            ledgerInstance.addToLedger(nd);
        } else {
            std::cout << "Block is not valid according to contract. Discarding "
                         "block...\n\n-----------------------------\n\n";
        }
        proofOfWork(5000);

        u1.setUserLedger(ledgerInstance.getLedger());
        u2.setUserLedger(ledgerInstance.getLedger());
    }
    std::cout << "\n\n--------------------------------- Printing Ledger "
                 "---------------------------------"
              << std::endl;
    for (int i = 0; i < ledgerInstance.ledgerLength(); i++) {
        std::cout << "\n\n---------------------------------" << std::endl;
        if (i > 0) {
            ledgerInstance.printInstance(i);
        } else {
            std::cout << "\n\nGenesis block (Block #1)";
        }
        std::cout << "\n\n---------------------------------" << std::endl;
    }

    std::cout
        << "\n========================================\nBalance of sender now: "
        << std::endl;
    u1.getDetails();

    std::cout
        << "\n========================================\nBalance of receiver "
           "now: "
        << std::endl;
    u2.getDetails();

    std::cout << "\n\nAre the ledgers same?\n\n";
    std::cout << compareLedgers(u1, u2) << std::endl;

    return 0;
}