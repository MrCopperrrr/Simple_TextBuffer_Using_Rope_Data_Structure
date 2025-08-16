#ifndef ROPE_TEXTBUFFER_H
#define ROPE_TEXTBUFFER_H

#include "main.h"

/*
    Student can define other list data structures here
*/

/**
 * Rope (AVL-based, fixed leaf chunk size = 8)
 */
class Rope {
public:
    static const int CHUNK_SIZE = 8;
private:
    class Node {
    public:
        enum BalanceFactor { LH = 1, EH = 0, RH = -1 };
    private:
        Node* left;
        Node* right;
        string data;
        int weight;
        int height;
        BalanceFactor balance;
        int totalLength; //add

        Node();
        explicit Node(const string& s);
        bool isLeaf() const;
        friend class Rope; // add
        // ===== FRIEND TEST HELPER (REMOVE BEFORE SUBMIT) =====
        friend class TestHelper; // <--- thêm dòng này để test private
        // =====================================================
        
    };
    

    Node* root;

    int height(Node* node) const;
    int getTotalLength(Node* node) const;
    void update(Node* node);
    Node* rotateLeft(Node* x);
    Node* rotateRight(Node* y);
    Node* rebalance(Node* node);
    void split(Node* node, int index, Node*& outLeft, Node*& outRight);
    Node* concatNodes(Node* left, Node* right);
    char charAt(Node* node, int index) const;
    void toStringHelper(Node* node, std::string& result) const;
    string toString(Node* node) const;
    void destroy(Node*& node);
    int collectSubstring(Node* node, int start, int len, string &out) const; //add
    Node* buildFromString(const std::string& s);

public:
    Rope();
    ~Rope();

    int length() const;
    bool empty() const;
    char charAt(int index) const;
    string substring(int start, int length) const;
    void insert(int index, const string& s);
    void deleteRange(int start, int length);
    string toString() const;

    // ===== FRIEND TEST HELPER (REMOVE BEFORE SUBMIT) =====
    friend class TestHelper; // <--- thêm dòng này để test private
    // =====================================================
#ifdef TESTING
    friend class TestHelper;
#endif
};

class RopeTextBuffer {
public:
    class HistoryManager; 

private:
    Rope rope;
    int cursorPos;
    HistoryManager* history;

public:
    RopeTextBuffer();
    ~RopeTextBuffer();

    void insert(const string& s);
    void deleteRange(int length);
    void replace(int length, const string& s);
    void moveCursorTo(int index);
    void moveCursorLeft();
    void moveCursorRight();
    int  getCursorPos() const;
    string getContent() const;
    int findFirst(char c) const;
    int* findAll(char c) const;
    void undo();
    void redo();
    void printHistory() const;
    void clear();
    // ===== FRIEND TEST HELPER (REMOVE BEFORE SUBMIT) =====
    friend class TestHelper; // <--- thêm dòng này để test private
    // =====================================================
#ifdef TESTING
    friend class TestHelper;
#endif
};


class RopeTextBuffer::HistoryManager {
public:
    struct Action {
        string actionName; // "insert", "delete", "move", "replace"
        int cursorBefore;
        int cursorAfter;
        string data;
        string oldData; // chuỗi cũ
        string newData; // chuỗi mới
    };

private:
    // Thuộc tính động cho quản lý lịch sử
    Action* actions;
    int capacity;
    int size;
    int current; // con trỏ undo/redo: -1 nếu chưa có hành động nào

    void ensureCapacity() {
        if (size < capacity) return;
        int newCap = capacity * 2;
        Action* newArr = new Action[newCap];
        for (int i = 0; i < size; ++i) newArr[i] = actions[i];
        delete[] actions;
        actions = newArr;
        capacity = newCap;
    }

public:
    HistoryManager();
    ~HistoryManager();

    void addAction(const Action& a);
    bool canUndo() const;
    bool canRedo() const;
    void printHistory() const;

    // Các hàm phụ trợ cho undo/redo
    Action getUndoAction() const {
    if (!canUndo()) return Action{}; // trả về Action rỗng
    return actions[current];
    }

    Action getRedoAction() const {
        if (!canRedo()) return Action{};
        return actions[current + 1];
    }
    
    void moveUndoPointer(int delta) {
        current += delta;
    }
    // ===== FRIEND TEST HELPER (REMOVE BEFORE SUBMIT) =====
    friend class TestHelper; // <--- thêm dòng này để test private
    // =====================================================
#ifdef TESTING
    friend class TestHelper;
#endif
};

#endif // ROPE_TEXTBUFFER_H

