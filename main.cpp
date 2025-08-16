//include files
#include "RopeTextBuffer.h"

//include lib
#include <sstream> 

// define color
#define GREEN "\033[32m"  //pass
#define RED "\033[31m"  //fail
#define ORANGE "\033[38;5;208m"  //result
#define BLUE "\033[34m"  //info
#define YELLOW "\033[33m"  //warning
#define CYAN "\033[36m"  //debug
#define MAGENTA "\033[35m"  //important
#define RESET "\033[0m"

using namespace std;

int num_correct = 0;
int num_incorrect = 0;

void sample_01() {
    Rope rope;
    std::string expect = "empty=1, length=0";
    std::ostringstream oss;
    oss << "empty=" << rope.empty() << ", length=" << rope.length();
    std::string result = oss.str();
    if (result == expect) {
        std::cout << GREEN << "sample_01 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "sample_01 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << RESET << std::endl;
        num_incorrect++;
    }
}

void sample_02() {
    Rope rope;
    rope.insert(0, "Hello");
    std::string expect = "Hello, length=5";
    std::ostringstream oss;
    oss << rope.toString() << ", length=" << rope.length();
    std::string result = oss.str();
    if (result == expect) {
        std::cout << GREEN << "sample_02 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "sample_02 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << RESET << std::endl;
        num_incorrect++;
    }
}

void sample_03() {
    Rope rope;
    rope.insert(0, "ABC");
    std::string expect = "charAt(1)=B, charAt(0)=A";
    std::ostringstream oss;
    oss << "charAt(1)=" << rope.charAt(1) << ", charAt(0)=" << rope.charAt(0);
    std::string result = oss.str();
    if (result == expect) {
        std::cout << GREEN << "sample_03 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "sample_03 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << RESET << std::endl;
        num_incorrect++;
    }
}

void sample_04() {
    RopeTextBuffer tb;
    tb.insert("Hello");
    std::string expect = "Hello, cursor=5";
    std::ostringstream oss;
    oss << tb.getContent() << ", cursor=" << tb.getCursorPos();
    std::string result = oss.str();
    if (result == expect) {
        std::cout << GREEN << "sample_04 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "sample_04 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << RESET << std::endl;
        num_incorrect++;
    }
}

void sample_05() {
    RopeTextBuffer tb;
    tb.insert("ABC");
    tb.moveCursorLeft();
    tb.insert("X");
    std::string expect = "ABXC, cursor=3";
    std::ostringstream oss;
    oss << tb.getContent() << ", cursor=" << tb.getCursorPos();
    std::string result = oss.str();
    if (result == expect) {
        std::cout << GREEN << "sample_05 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "sample_05 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << RESET << std::endl;
        num_incorrect++;
    }
}

void sample_06() {
    RopeTextBuffer tb;
    tb.insert("Hello");
    tb.moveCursorTo(2);
    tb.deleteRange(2);
    std::string expect = "Heo, cursor=2";
    std::ostringstream oss;
    oss << tb.getContent() << ", cursor=" << tb.getCursorPos();
    std::string result = oss.str();
    if (result == expect) {
        std::cout << GREEN << "sample_06 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "sample_06 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << RESET << std::endl;
        num_incorrect++;
    }
}

void sample_07() {
    RopeTextBuffer tb;
    tb.insert("ABC");
    std::string expect = "Cursor error!";
    std::ostringstream oss;
    try {
        tb.moveCursorTo(0);
        tb.moveCursorLeft();
    } catch (const cursor_error &e) {
        oss << e.what();
    }
    std::string result = oss.str();
    if (result == expect) {
        std::cout << GREEN << "sample_07 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "sample_07 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << RESET << std::endl;
        num_incorrect++;
    }
}

void sample_08() {
    RopeTextBuffer tb;
    tb.insert("Hi");
    tb.insert("!!");
    tb.moveCursorLeft();
    tb.deleteRange(1);
    std::string expect = "Hi!, cursor=3";
    std::ostringstream oss;
    oss << tb.getContent() << ", cursor=" << tb.getCursorPos();
    std::string result = oss.str();
    if (result == expect) {
        std::cout << GREEN << "sample_08 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "sample_08 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << RESET << std::endl;
        num_incorrect++;
    }
    // Kiểm tra lịch sử thao tác tự động
    std::string expectHist = "[(insert, 0, 2, Hi), (insert, 2, 4, !!), (move, 4, 3, L), (delete, 3, 3, !)]";
    std::ostringstream ossHist;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(ossHist.rdbuf());
    tb.printHistory();
    std::cout.rdbuf(oldCout);
    std::string historyResult = ossHist.str();
    if (!historyResult.empty() && historyResult.back() == '\n') historyResult.pop_back();
    if (historyResult == expectHist) {
        std::cout << GREEN << "History correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "History failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << historyResult << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expectHist << RESET << std::endl;
        num_incorrect++;
    }
}

void test_example_3_1() {
    RopeTextBuffer buf;

    // Thao tác 1: insert("A")
    buf.insert("A");
    std::string result = buf.getContent();
    std::string expect = "A";
    if (result == expect && buf.getCursorPos() == 1) {
        std::cout << GREEN << "Step 1 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 1 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << ", Cursor: " << buf.getCursorPos() << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << ", Cursor: 1" << RESET << std::endl;
        num_incorrect++;
    }

    // Thao tác 2: insert("CSE")
    buf.insert("CSE");
    result = buf.getContent();
    expect = "ACSE";
    if (result == expect && buf.getCursorPos() == 4) {
        std::cout << GREEN << "Step 2 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 2 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << ", Cursor: " << buf.getCursorPos() << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << ", Cursor: 4" << RESET << std::endl;
        num_incorrect++;
    }

    // Thao tác 3: insert("HCMUT")
    buf.insert("HCMUT");
    result = buf.getContent();
    expect = "ACSEHCMUT";
    if (result == expect && buf.getCursorPos() == 9) {
        std::cout << GREEN << "Step 3 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 3 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << ", Cursor: " << buf.getCursorPos() << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << ", Cursor: 9" << RESET << std::endl;
        num_incorrect++;
    }

    // Thao tác 4: moveCursorLeft()
    buf.moveCursorLeft();
    result = buf.getContent();
    if (buf.getCursorPos() == 8) {
        std::cout << GREEN << "Step 4 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 4 failed." << RESET << std::endl;
        std::cout << ORANGE << "Cursor: " << buf.getCursorPos() << ", Expect: 8" << RESET << std::endl;
        num_incorrect++;
    }

    // Thao tác 5: insert("123")
    buf.insert("123");
    result = buf.getContent();
    expect = "ACSEHCMU123T";
    if (result == expect && buf.getCursorPos() == 11) {
        std::cout << GREEN << "Step 5 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 5 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << ", Cursor: " << buf.getCursorPos() << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << ", Cursor: 11" << RESET << std::endl;
        num_incorrect++;
    }

    // Thao tác 6: moveCursorTo(4)
    buf.moveCursorTo(4);
    if (buf.getCursorPos() == 4) {
        std::cout << GREEN << "Step 6 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 6 failed." << RESET << std::endl;
        std::cout << ORANGE << "Cursor: " << buf.getCursorPos() << ", Expect: 4" << RESET << std::endl;
        num_incorrect++;
    }

    // Thao tác 7: deleteRange(3)
    buf.deleteRange(3);
    result = buf.getContent();
    expect = "ACSEU123T";
    if (result == expect && buf.getCursorPos() == 4) {
        std::cout << GREEN << "Step 7 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 7 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << ", Cursor: " << buf.getCursorPos() << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << ", Cursor: 4" << RESET << std::endl;
        num_incorrect++;
    }

    // Thao tác 8: undo() (khôi phục chuỗi đã xóa)
    buf.undo();
    result = buf.getContent();
    expect = "ACSEHCMU123T";
    if (result == expect && buf.getCursorPos() == 4) {
        std::cout << GREEN << "Step 8 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 8 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << ", Cursor: " << buf.getCursorPos() << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << ", Cursor: 4" << RESET << std::endl;
        num_incorrect++;
    }

    // Thao tác 9: undo() (di chuyển cursor về lại vị trí trước thao tác 6)
    buf.undo();
    result = buf.getContent();
    expect = "ACSEHCMU123T";
    if (result == expect && buf.getCursorPos() == 11) {
        std::cout << GREEN << "Step 9 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 9 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << ", Cursor: " << buf.getCursorPos() << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << ", Cursor: 11" << RESET << std::endl;
        num_incorrect++;
    }

    // Thao tác 10: undo() (xóa chuỗi "123" đã thêm)
    buf.undo();
    result = buf.getContent();
    expect = "ACSEHCMUT";
    if (result == expect && buf.getCursorPos() == 8) {
        std::cout << GREEN << "Step 10 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 10 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << ", Cursor: " << buf.getCursorPos() << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << ", Cursor: 8" << RESET << std::endl;
        num_incorrect++;
    }

    // Thao tác 11: redo() (thêm lại chuỗi "123")
    buf.redo();
    result = buf.getContent();
    expect = "ACSEHCMU123T";
    if (result == expect && buf.getCursorPos() == 11) {
        std::cout << GREEN << "Step 11 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 11 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << ", Cursor: " << buf.getCursorPos() << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << ", Cursor: 11" << RESET << std::endl;
        num_incorrect++;
    }

    // Thao tác 12: redo() (di chuyển cursor về lại vị trí 4)
    buf.redo();
    result = buf.getContent();
    expect = "ACSEHCMU123T";
    if (result == expect && buf.getCursorPos() == 4) {
        std::cout << GREEN << "Step 12 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 12 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << ", Cursor: " << buf.getCursorPos() << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << ", Cursor: 4" << RESET << std::endl;
        num_incorrect++;
    }

    // Thao tác 13: redo() (xóa 3 ký tự)
    buf.redo();
    result = buf.getContent();
    expect = "ACSEU123T";
    if (result == expect && buf.getCursorPos() == 4) {
        std::cout << GREEN << "Step 13 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "Step 13 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << ", Cursor: " << buf.getCursorPos() << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << ", Cursor: 4" << RESET << std::endl;
        num_incorrect++;
    }

}

void test_case_09() {
    RopeTextBuffer tb;
    tb.insert("Hello");
    tb.moveCursorTo(1);
    tb.replace(3, "XOX");
    std::string expect = "HXOXo, cursor=4";
    std::ostringstream oss;
    oss << tb.getContent() << ", cursor=" << tb.getCursorPos();
    std::string result = oss.str();

    // Kiểm tra nội dung
    if (result == expect) {
        std::cout << GREEN << "test_case_09 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "test_case_09 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << RESET << std::endl;
        num_incorrect++;
    }

    // Kiểm tra lịch sử thao tác
    std::string expectHist = "[(insert, 0, 5, Hello), (move, 5, 1, J), (replace, 1, 4, ell)]";
    std::ostringstream ossHist;
    // Chuyển hướng cout tạm thời
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(ossHist.rdbuf());
    tb.printHistory();
    std::cout.rdbuf(oldCout);
    std::string historyResult = ossHist.str();
    // Xóa ký tự xuống dòng cuối nếu có
    if (!historyResult.empty() && historyResult.back() == '\n') historyResult.pop_back();

    if (historyResult == expectHist) {
        std::cout << GREEN << "History correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "History failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << historyResult << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expectHist << RESET << std::endl;
        num_incorrect++;
    }
}

void test_case_10() {
    RopeTextBuffer tb;
    tb.insert("ABCDEF");
    tb.moveCursorTo(1);
    tb.replace(3, "XYZ");
    std::string expect = "AXYZEF, cursor=4";
    std::ostringstream oss;
    oss << tb.getContent() << ", cursor=" << tb.getCursorPos();
    std::string result = oss.str();
    if (result == expect) {
        std::cout << GREEN << "test_case_10 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "test_case_10 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << RESET << std::endl;
        num_incorrect++;
    }
    std::string expectHist = "[(insert, 0, 6, ABCDEF), (move, 6, 1, J), (replace, 1, 4, BCD)]";
    std::ostringstream ossHist;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(ossHist.rdbuf());
    tb.printHistory();
    std::cout.rdbuf(oldCout);
    std::string historyResult = ossHist.str();
    if (!historyResult.empty() && historyResult.back() == '\n') historyResult.pop_back();
    if (historyResult == expectHist) {
        std::cout << GREEN << "History correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "History failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << historyResult << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expectHist << RESET << std::endl;
        num_incorrect++;
    }
}

void test_case_11() {
    RopeTextBuffer tb;
    tb.insert("A");
    tb.insert("CSE");
    tb.insert("HCMUT");
    tb.moveCursorLeft();
    tb.insert("123");
    tb.moveCursorTo(4);
    tb.deleteRange(3);
    tb.undo();
    tb.undo();
    tb.undo();
    tb.redo();
    tb.redo();
    tb.redo();
    std::string expect = "ACSEU123T, cursor=4";
    std::ostringstream oss;
    oss << tb.getContent() << ", cursor=" << tb.getCursorPos();
    std::string result = oss.str();
    if (result == expect) {
        std::cout << GREEN << "test_case_11 correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "test_case_11 failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << result << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expect << RESET << std::endl;
        num_incorrect++;
    }
    std::string expectHist = "[(insert, 0, 1, A), (insert, 1, 4, CSE), (insert, 4, 9, HCMUT), (move, 9, 8, L), (insert, 8, 11, 123), (move, 11, 4, J), (delete, 4, 4, HCM)]";
    std::ostringstream ossHist;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(ossHist.rdbuf());
    tb.printHistory();
    std::cout.rdbuf(oldCout);
    std::string historyResult = ossHist.str();
    if (!historyResult.empty() && historyResult.back() == '\n') historyResult.pop_back();
    if (historyResult == expectHist) {
        std::cout << GREEN << "History correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "History failed." << RESET << std::endl;
        std::cout << ORANGE << "Result: " << historyResult << RESET << std::endl;
        std::cout << ORANGE << "Expect: " << expectHist << RESET << std::endl;
        num_incorrect++;
    }
}
class TestHelper {
public:
    static void test_height();
    static void test_getTotalLength();
    static void test_update();
    static void test_rotateLeft();
    static void test_rotateRight();
    static void test_split();
    static void test_concatNodes();
    static void test_charAt();
    static void test_toString();
    static void test_destroy();
    static void test_public_length_empty();
    static void test_public_charAt();
    static void test_public_substring();
    static void test_public_insert();
    static void test_public_deleteRange();
    static void test_public_replace();
    static void test_public_cursor();
    static void test_public_getContent();
    static void test_public_findFirst_findAll();
    static void test_public_undo();
    static void test_public_redo();
    static void test_public_printHistory_clear();
};

void TestHelper::test_height() {
    Rope rope;
    std::cout << MAGENTA << "Test height:" << RESET << std::endl;
    // Test 1: nullptr
    if (rope.height(nullptr) == 0) {
        std::cout << GREEN << "height(nullptr) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "height(nullptr) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 2: node lá
    Rope::Node* leaf = new Rope::Node("abc");
    if (rope.height(leaf) == 1) {
        std::cout << GREEN << "height(leaf) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "height(leaf) failed." << RESET << std::endl;
        num_incorrect++;
    }
    delete leaf;

    // Test 3: cây 3 tầng
    Rope::Node* left = new Rope::Node("a");
    Rope::Node* right = new Rope::Node("bc");
    Rope::Node* root = new Rope::Node();
    root->left = left;
    root->right = right;
    rope.update(root); // cập nhật height
    if (rope.height(root) == 2) {
        std::cout << GREEN << "height(root) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "height(root) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root);
}

void TestHelper::test_getTotalLength() {
    Rope rope;
    std::cout << MAGENTA << "Test getTotalLength:" << RESET << std::endl;
    // Test 1: nullptr
    if (rope.getTotalLength(nullptr) == 0) {
        std::cout << GREEN << "getTotalLength(nullptr) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "getTotalLength(nullptr) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 2: node lá
    Rope::Node* leaf = new Rope::Node("abc");
    if (rope.getTotalLength(leaf) == 3) {
        std::cout << GREEN << "getTotalLength(leaf) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "getTotalLength(leaf) failed." << RESET << std::endl;
        num_incorrect++;
    }
    delete leaf;

    // Test 3: cây nhiều lá
    Rope::Node* left = new Rope::Node("a");
    Rope::Node* right = new Rope::Node("bc");
    Rope::Node* root = new Rope::Node();
    root->left = left;
    root->right = right;
    rope.update(root);
    if (rope.getTotalLength(root) == 3) {
        std::cout << GREEN << "getTotalLength(root) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "getTotalLength(root) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root);
}

void TestHelper::test_update() {
    Rope rope;
    std::cout << MAGENTA << "Test update:" << RESET << std::endl;

    // Test 1: nullptr
    rope.update(nullptr); // Không crash, không thay đổi gì
    std::cout << GREEN << "update(nullptr) correct." << RESET << std::endl;
    num_correct++;

    // Test 2: node lá đơn giản
    Rope::Node* leaf = new Rope::Node("abc");
    leaf->weight = 0; leaf->height = 0; leaf->balance = Rope::Node::RH;
    rope.update(leaf);
    bool ok = (leaf->weight == 3 && 
        leaf->height == 0 && 
        leaf->balance == Rope::Node::EH);

    if (ok) {
        std::cout << GREEN << "update(leaf) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "update(leaf) failed." << RESET << std::endl;
        num_incorrect++;
    }
    delete leaf;

    // Test 3: node trong với 2 lá con
    Rope::Node* left = new Rope::Node("a");
    Rope::Node* right = new Rope::Node("bc");
    Rope::Node* root = new Rope::Node();
    root->left = left;
    root->right = right;
    rope.update(root);
    ok = (root->weight == 1 && root->height == 2 && root->balance == Rope::Node::EH && root->totalLength == 3);
    if (ok) {
        std::cout << GREEN << "update(root with 2 leaves) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "update(root with 2 leaves) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root);

    // Test 4: node lệch trái (chiều cao trái > phải)
    Rope::Node* l1 = new Rope::Node("x");
    Rope::Node* l2 = new Rope::Node("y");
    Rope::Node* left2 = new Rope::Node();
    left2->left = l1;
    left2->right = l2;
    rope.update(left2);
    Rope::Node* right2 = new Rope::Node("z");
    Rope::Node* root2 = new Rope::Node();
    root2->left = left2;
    root2->right = right2;
    rope.update(root2);
    ok = (root2->balance == Rope::Node::LH);
    if (ok) {
        std::cout << GREEN << "update(balance LH) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "update(balance LH) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root2);

    // Test 5: node lệch phải (chiều cao phải > trái)
    Rope::Node* r1 = new Rope::Node("m");
    Rope::Node* r2 = new Rope::Node("n");
    Rope::Node* right3 = new Rope::Node();
    right3->left = r1;
    right3->right = r2;
    rope.update(right3);
    Rope::Node* left3 = new Rope::Node("p");
    Rope::Node* root3 = new Rope::Node();
    root3->left = left3;
    root3->right = right3;
    rope.update(root3);
    ok = (root3->balance == Rope::Node::RH);
    if (ok) {
        std::cout << GREEN << "update(balance RH) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "update(balance RH) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root3);

    // Test 6: node cân bằng (chiều cao trái = phải)
    Rope::Node* l4 = new Rope::Node("a");
    Rope::Node* r4 = new Rope::Node("b");
    Rope::Node* root4 = new Rope::Node();
    root4->left = l4;
    root4->right = r4;
    rope.update(root4);
    ok = (root4->balance == Rope::Node::EH);
    if (ok) {
        std::cout << GREEN << "update(balance EH) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "update(balance EH) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root4);
}

void TestHelper::test_rotateLeft() {
    Rope rope;
    std::cout << MAGENTA << "Test rotateLeft:" << RESET << std::endl;

    // Test 1: nullptr
    Rope::Node* res = rope.rotateLeft(nullptr);
    if (res == nullptr) {
        std::cout << GREEN << "rotateLeft(nullptr) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateLeft(nullptr) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 2: node không có right
    Rope::Node* x = new Rope::Node("a");
    res = rope.rotateLeft(x);
    if (res == x) {
        std::cout << GREEN << "rotateLeft(no right) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateLeft(no right) failed." << RESET << std::endl;
        num_incorrect++;
    }
    delete x;

    // Test 3: cây 2 tầng đơn giản
    Rope::Node* x3 = new Rope::Node("x");
    Rope::Node* y3 = new Rope::Node("y");
    Rope::Node* root3 = new Rope::Node();
    root3->left = x3;
    root3->right = y3;
    Rope::Node* newRoot3 = rope.rotateLeft(root3);
    bool ok = (newRoot3 == y3 && newRoot3->left == root3 && root3->right == nullptr);
    if (ok) {
        std::cout << GREEN << "rotateLeft(2-level) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateLeft(2-level) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(newRoot3);

    // Test 4: cây 3 tầng, right có left con
    Rope::Node* x4 = new Rope::Node("x");
    Rope::Node* y4 = new Rope::Node();
    Rope::Node* T2 = new Rope::Node("t2");
    Rope::Node* T3 = new Rope::Node("t3");
    y4->left = T2;
    y4->right = T3;
    Rope::Node* root4 = new Rope::Node();
    root4->left = x4;
    root4->right = y4;
    Rope::Node* newRoot4 = rope.rotateLeft(root4);
    ok = (newRoot4 == y4 && newRoot4->left == root4 && root4->right == T2 && newRoot4->right == T3);
    if (ok) {
        std::cout << GREEN << "rotateLeft(right has left child) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateLeft(right has left child) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(newRoot4);

    // Test 5: cây lớn hơn, right là cây con phức tạp
    Rope::Node* x5 = new Rope::Node("x");
    Rope::Node* y5 = new Rope::Node();
    Rope::Node* T2_5 = new Rope::Node("t2");
    Rope::Node* T3_5 = new Rope::Node("t3");
    Rope::Node* T4_5 = new Rope::Node("t4");
    y5->left = T2_5;
    y5->right = T3_5;
    Rope::Node* root5 = new Rope::Node();
    root5->left = x5;
    root5->right = y5;
    Rope::Node* newRoot5 = rope.rotateLeft(root5);
    ok = (newRoot5 == y5 && newRoot5->left == root5 && root5->right == T2_5 && newRoot5->right == T3_5);
    if (ok) {
        std::cout << GREEN << "rotateLeft(complex right) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateLeft(complex right) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(newRoot5);

    // Test 6: kiểm tra cập nhật height, balance sau xoay
    Rope::Node* x6 = new Rope::Node("x");
    Rope::Node* y6 = new Rope::Node("y");
    Rope::Node* root6 = new Rope::Node();
    root6->left = x6;
    root6->right = y6;
    rope.update(x6); // Cập nhật height cho x6
    rope.update(y6); // Cập nhật height cho y6
    rope.update(root6);

    Rope::Node* newRoot6 = rope.rotateLeft(root6);
    bool heightOk = (newRoot6 == y6 &&
                     newRoot6->height == 2 &&
                     newRoot6->balance == Rope::Node::LH &&
                     newRoot6->left == root6 &&
                     root6->left == x6 &&
                     root6->right == nullptr);
    if (heightOk) {
        std::cout << GREEN << "rotateLeft(update height/balance) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateLeft(update height/balance) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(newRoot6);

    // Test 7: xoay trái nhiều lần liên tiếp
    Rope::Node* a7 = new Rope::Node("a");
    Rope::Node* b7 = new Rope::Node("b");
    Rope::Node* c7 = new Rope::Node("c");
    Rope::Node* root7 = new Rope::Node();
    root7->left = a7;
    root7->right = b7;
    Rope::Node* root8 = new Rope::Node();
    root8->left = root7;
    root8->right = c7;
    rope.update(root7);
    rope.update(root8);
    Rope::Node* after1 = rope.rotateLeft(root8);
    rope.update(after1);
    Rope::Node* after2 = rope.rotateLeft(after1);
    rope.update(after2);

    ok = (after2 == c7 && after2->left == root8 && after2->right == nullptr &&
          root8->left == root7 && root8->right == nullptr &&
          root7->left == a7 && root7->right == b7);
    if (ok) {
        std::cout << GREEN << "rotateLeft(multiple) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateLeft(multiple) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root8);

    // Test 8: kiểm tra dữ liệu không bị mất khi xoay
    Rope::Node* left8 = new Rope::Node("L");
    Rope::Node* right8 = new Rope::Node("R");
    Rope::Node* root9 = new Rope::Node();
    root9->left = left8;
    root9->right = right8;
    Rope::Node* newRoot9 = rope.rotateLeft(root9);
    ok = (newRoot9->left->left == left8 && newRoot9->right == nullptr && newRoot9->left->right == nullptr);
    if (ok) {
        std::cout << GREEN << "rotateLeft(data preserved) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateLeft(data preserved) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(newRoot9);
}

void TestHelper::test_rotateRight() {
    Rope rope;
    std::cout << MAGENTA << "Test rotateRight:" << RESET << std::endl;

    // Test 1: nullptr
    Rope::Node* res = rope.rotateRight(nullptr);
    if (res == nullptr) {
        std::cout << GREEN << "rotateRight(nullptr) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateRight(nullptr) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 2: node không có left
    Rope::Node* y2 = new Rope::Node("y");
    res = rope.rotateRight(y2);
    if (res == y2) {
        std::cout << GREEN << "rotateRight(no left) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateRight(no left) failed." << RESET << std::endl;
        num_incorrect++;
    }
    delete y2;

    // Test 3: cây 2 tầng đơn giản
    Rope::Node* x3 = new Rope::Node("x");
    Rope::Node* y3 = new Rope::Node();
    y3->left = x3;
    Rope::Node* newRoot3 = rope.rotateRight(y3);
    bool ok = (newRoot3 == x3 && newRoot3->right == y3 && y3->left == nullptr);
    if (ok) {
        std::cout << GREEN << "rotateRight(2-level) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateRight(2-level) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(newRoot3);

    // Test 4: cây 3 tầng, left có right con
    Rope::Node* x4 = new Rope::Node();
    Rope::Node* T1 = new Rope::Node("t1");
    Rope::Node* T2 = new Rope::Node("t2");
    x4->left = T1;
    x4->right = T2;
    Rope::Node* y4 = new Rope::Node();
    y4->left = x4;
    Rope::Node* newRoot4 = rope.rotateRight(y4);
    ok = (newRoot4 == x4 && newRoot4->right == y4 && y4->left == T2 && newRoot4->left == T1);
    if (ok) {
        std::cout << GREEN << "rotateRight(left has right child) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateRight(left has right child) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(newRoot4);

    // Test 5: cây lớn hơn, left là cây con phức tạp
    Rope::Node* x5 = new Rope::Node();
    Rope::Node* T1_5 = new Rope::Node("t1");
    Rope::Node* T2_5 = new Rope::Node("t2");
    Rope::Node* T3_5 = new Rope::Node("t3");
    x5->left = T1_5;
    x5->right = T2_5;
    Rope::Node* y5 = new Rope::Node();
    y5->left = x5;
    y5->right = T3_5;
    Rope::Node* newRoot5 = rope.rotateRight(y5);
    ok = (newRoot5 == x5 && newRoot5->right == y5 && y5->left == T2_5 && y5->right == T3_5 && newRoot5->left == T1_5);
    if (ok) {
        std::cout << GREEN << "rotateRight(complex left) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateRight(complex left) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(newRoot5);

    // Test 6: kiểm tra cập nhật height, balance sau xoay
    Rope::Node* x6 = new Rope::Node("x");
    Rope::Node* y6 = new Rope::Node();
    y6->left = x6;
    rope.update(x6);
    rope.update(y6);
    Rope::Node* newRoot6 = rope.rotateRight(y6);
    // Sau xoay, newRoot6 là x6, newRoot6->right là y6, y6->left == nullptr
    bool heightOk = (newRoot6 == x6 &&
                     newRoot6->height == 1 && // Sửa: newRoot6->height phải là 1
                     newRoot6->balance == Rope::Node::EH &&
                     newRoot6->right == y6 &&
                     y6->left == nullptr &&
                     y6->balance == Rope::Node::EH); // Thêm kiểm tra y6->balance
    if (heightOk) {
        std::cout << GREEN << "rotateRight(update height/balance) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateRight(update height/balance) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(newRoot6);

    // Test 7: xoay phải nhiều lần liên tiếp
    Rope::Node* a7 = new Rope::Node("a");
    Rope::Node* b7 = new Rope::Node("b");
    Rope::Node* c7 = new Rope::Node("c");
    Rope::Node* root7 = new Rope::Node();
    root7->left = a7;
    root7->right = b7;
    Rope::Node* root8 = new Rope::Node();
    root8->left = c7;
    root8->right = root7;
    rope.update(root7);
    rope.update(root8);
    Rope::Node* after1 = rope.rotateRight(root8);
    rope.update(after1);
    Rope::Node* after2 = rope.rotateRight(after1);
    rope.update(after2);

    ok = (after2 == c7 && after2->right == root8 && after2->left == nullptr &&
          root8->right == root7 && root8->left == nullptr &&
          root7->left == a7 && root7->right == b7);
    if (ok) {
        std::cout << GREEN << "rotateRight(multiple) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateRight(multiple) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root8);

    // Test 8: kiểm tra dữ liệu không bị mất khi xoay
    Rope::Node* left8 = new Rope::Node("L");
    Rope::Node* right8 = new Rope::Node("R");
    Rope::Node* root9 = new Rope::Node();
    root9->left = left8;
    root9->right = right8;
    Rope::Node* newRoot9 = rope.rotateRight(root9);
    ok = (newRoot9->right->right == right8 && 
        newRoot9->left == nullptr && 
        newRoot9->right == root9);
    if (ok) {
        std::cout << GREEN << "rotateRight(data preserved) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "rotateRight(data preserved) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(newRoot9);
}

void TestHelper::test_split() {
    Rope rope;
    std::cout << MAGENTA << "Test split:" << RESET << std::endl;

    // Test 1: split nullptr
    Rope::Node *left = nullptr, *right = nullptr;
    rope.split(nullptr, 0, left, right);
    bool ok = (left == nullptr && right == nullptr);
    if (ok) {
        std::cout << GREEN << "split(nullptr) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "split(nullptr) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 2: split node lá với index = 0
    Rope::Node* leaf2 = new Rope::Node("abc");
    rope.split(leaf2, 0, left, right);
    ok = (left == nullptr && right != nullptr && right->data == "abc");
    if (ok) {
        std::cout << GREEN << "split(leaf, index=0) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "split(leaf, index=0) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(right);

    // Test 3: split node lá với index = length
    Rope::Node* leaf3 = new Rope::Node("abc");
    rope.split(leaf3, 3, left, right);
    ok = (left != nullptr && left->data == "abc" && right == nullptr);
    if (ok) {
        std::cout << GREEN << "split(leaf, index=length) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "split(leaf, index=length) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(left);

    // Test 4: split node lá với index giữa
    Rope::Node* leaf4 = new Rope::Node("abcdef");
    rope.split(leaf4, 3, left, right);
    ok = (left != nullptr && left->data == "abc" && right != nullptr && right->data == "def");
    if (ok) {
        std::cout << GREEN << "split(leaf, index=mid) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "split(leaf, index=mid) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(left);
    rope.destroy(right);

    // Test 5: split cây 2 lá, index ở ranh giới
    Rope::Node* l5 = new Rope::Node("abc");
    Rope::Node* r5 = new Rope::Node("def");
    Rope::Node* root5 = new Rope::Node();
    root5->left = l5;
    root5->right = r5;
    rope.update(root5);
    rope.split(root5, 3, left, right);
    ok = (left != nullptr && rope.toString(left) == "abc" &&
          right != nullptr && rope.toString(right) == "def");
    if (ok) {
        std::cout << GREEN << "split(two leaves, index=left length) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "split(two leaves, index=left length) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(left);
    rope.destroy(right);

    // Test 6: split cây 2 lá, index giữa
    Rope::Node* l6 = new Rope::Node("abc");
    Rope::Node* r6 = new Rope::Node("def");
    Rope::Node* root6 = new Rope::Node();
    root6->left = l6;
    root6->right = r6;
    rope.update(root6);
    rope.split(root6, 4, left, right);
    ok = (left != nullptr && rope.toString(left) == "abcd" &&
          right != nullptr && rope.toString(right) == "ef");
    if (ok) {
        std::cout << GREEN << "split(two leaves, index=mid) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "split(two leaves, index=mid) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(left);
    rope.destroy(right);

    // Test 7: split cây nhiều tầng, index ở giữa
    Rope::Node* l7 = new Rope::Node("abc");
    Rope::Node* r7 = new Rope::Node("defg");
    Rope::Node* root7 = new Rope::Node();
    root7->left = l7;
    root7->right = r7;
    rope.update(root7);
    rope.split(root7, 5, left, right);
    ok = (left != nullptr && rope.toString(left) == "abcde" &&
          right != nullptr && rope.toString(right) == "fg");
    if (ok) {
        std::cout << GREEN << "split(two leaves, index=5) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "split(two leaves, index=5) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(left);
    rope.destroy(right);

    // Test 8: split cây nhiều tầng, index = tổng length
    Rope::Node* l8 = new Rope::Node("abc");
    Rope::Node* r8 = new Rope::Node("defg");
    Rope::Node* root8 = new Rope::Node();
    root8->left = l8;
    root8->right = r8;
    rope.update(root8);
    rope.split(root8, 7, left, right);
    ok = (left != nullptr && rope.toString(left) == "abcdefg" && right == nullptr);
    if (ok) {
        std::cout << GREEN << "split(two leaves, index=total length) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "split(two leaves, index=total length) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(left);

    // Test 9: split cây nhiều tầng, index = 0
    Rope::Node* l9 = new Rope::Node("abc");
    Rope::Node* r9 = new Rope::Node("defg");
    Rope::Node* root9 = new Rope::Node();
    root9->left = l9;
    root9->right = r9;
    rope.update(root9);
    rope.split(root9, 0, left, right);
    ok = (left == nullptr && right != nullptr && rope.toString(right) == "abcdefg");
    if (ok) {
        std::cout << GREEN << "split(two leaves, index=0) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "split(two leaves, index=0) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(right);
}

void TestHelper::test_concatNodes() {
    Rope rope;
    std::cout << MAGENTA << "Test concatNodes:" << RESET << std::endl;

    // Test 1: left = nullptr, right = nullptr
    Rope::Node* res = rope.concatNodes(nullptr, nullptr);
    bool ok = (res == nullptr);
    if (ok) {
        std::cout << GREEN << "concatNodes(nullptr, nullptr) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "concatNodes(nullptr, nullptr) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 2: left = nullptr, right != nullptr
    Rope::Node* right2 = new Rope::Node("abc");
    res = rope.concatNodes(nullptr, right2);
    ok = (res == right2);
    if (ok) {
        std::cout << GREEN << "concatNodes(nullptr, right) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "concatNodes(nullptr, right) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(res);

    // Test 3: left != nullptr, right = nullptr
    Rope::Node* left3 = new Rope::Node("xyz");
    res = rope.concatNodes(left3, nullptr);
    ok = (res == left3);
    if (ok) {
        std::cout << GREEN << "concatNodes(left, nullptr) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "concatNodes(left, nullptr) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(res);

    // Test 4: left và right đều là lá
    Rope::Node* left4 = new Rope::Node("abc");
    Rope::Node* right4 = new Rope::Node("def");
    res = rope.concatNodes(left4, right4);
    ok = (res != nullptr && rope.toString(res) == "abcdef");
    if (ok) {
        std::cout << GREEN << "concatNodes(two leaves) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "concatNodes(two leaves) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(res);

    // Test 5: left là cây nhiều tầng, right là lá
    Rope::Node* l5a = new Rope::Node("ab");
    Rope::Node* l5b = new Rope::Node("cd");
    Rope::Node* left5 = new Rope::Node();
    left5->left = l5a;
    left5->right = l5b;
    rope.update(left5);
    Rope::Node* right5 = new Rope::Node("efg");
    res = rope.concatNodes(left5, right5);
    ok = (res != nullptr && rope.toString(res) == "abcdefg");
    if (ok) {
        std::cout << GREEN << "concatNodes(tree, leaf) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "concatNodes(tree, leaf) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(res);

    // Test 6: left là lá, right là cây nhiều tầng
    Rope::Node* left6 = new Rope::Node("xy");
    Rope::Node* r6a = new Rope::Node("z");
    Rope::Node* r6b = new Rope::Node("w");
    Rope::Node* right6 = new Rope::Node();
    right6->left = r6a;
    right6->right = r6b;
    rope.update(right6);
    res = rope.concatNodes(left6, right6);
    ok = (res != nullptr && rope.toString(res) == "xyzw");
    if (ok) {
        std::cout << GREEN << "concatNodes(leaf, tree) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "concatNodes(leaf, tree) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(res);

    // Test 7: left và right đều là cây nhiều tầng
    Rope::Node* l7a = new Rope::Node("a");
    Rope::Node* l7b = new Rope::Node("b");
    Rope::Node* left7 = new Rope::Node();
    left7->left = l7a;
    left7->right = l7b;
    rope.update(left7);

    Rope::Node* r7a = new Rope::Node("c");
    Rope::Node* r7b = new Rope::Node("d");
    Rope::Node* right7 = new Rope::Node();
    right7->left = r7a;
    right7->right = r7b;
    rope.update(right7);

    res = rope.concatNodes(left7, right7);
    ok = (res != nullptr && rope.toString(res) == "abcd");
    if (ok) {
        std::cout << GREEN << "concatNodes(tree, tree) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "concatNodes(tree, tree) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(res);

    // Test 8: nối nhiều lần liên tiếp
    Rope::Node* l8 = new Rope::Node("A");
    Rope::Node* r8 = new Rope::Node("B");
    Rope::Node* t8 = rope.concatNodes(l8, r8);
    Rope::Node* r8b = new Rope::Node("C");
    Rope::Node* t8b = rope.concatNodes(t8, r8b);
    ok = (t8b != nullptr && rope.toString(t8b) == "ABC");
    if (ok) {
        std::cout << GREEN << "concatNodes(multiple) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "concatNodes(multiple) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(t8b);

    // Test 9: nối cây lớn, kiểm tra cân bằng
    Rope::Node* l9 = new Rope::Node("1234");
    Rope::Node* r9 = new Rope::Node("5678");
    Rope::Node* big = rope.concatNodes(l9, r9);
    ok = (big != nullptr && rope.toString(big) == "12345678" && big->balance == Rope::Node::EH);
    if (ok) {
        std::cout << GREEN << "concatNodes(balance) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "concatNodes(balance) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(big);
}

void TestHelper::test_charAt() {
    Rope rope;
    std::cout << MAGENTA << "Test charAt(Node*, index):" << RESET << std::endl;

    // Test 1: nullptr node
    char c = rope.charAt(nullptr, 0);
    bool ok = (c == '\0');
    if (ok) {
        std::cout << GREEN << "charAt(nullptr, 0) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "charAt(nullptr, 0) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 2: node lá, index < 0
    Rope::Node* leaf2 = new Rope::Node("abc");
    c = rope.charAt(leaf2, -1);
    ok = (c == '\0');
    if (ok) {
        std::cout << GREEN << "charAt(leaf, -1) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "charAt(leaf, -1) failed." << RESET << std::endl;
        num_incorrect++;
    }
    delete leaf2;

    // Test 3: node lá, index >= length
    Rope::Node* leaf3 = new Rope::Node("abc");
    c = rope.charAt(leaf3, 3);
    ok = (c == '\0');
    if (ok) {
        std::cout << GREEN << "charAt(leaf, out-of-bounds) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "charAt(leaf, out-of-bounds) failed." << RESET << std::endl;
        num_incorrect++;
    }
    delete leaf3;

    // Test 4: node lá, index hợp lệ
    Rope::Node* leaf4 = new Rope::Node("abc");
    c = rope.charAt(leaf4, 1);
    ok = (c == 'b');
    if (ok) {
        std::cout << GREEN << "charAt(leaf, valid) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "charAt(leaf, valid) failed." << RESET << std::endl;
        num_incorrect++;
    }
    delete leaf4;

    // Test 5: cây 2 lá, index ở trái
    Rope::Node* l5 = new Rope::Node("abc");
    Rope::Node* r5 = new Rope::Node("def");
    Rope::Node* root5 = new Rope::Node();
    root5->left = l5;
    root5->right = r5;
    rope.update(root5);
    c = rope.charAt(root5, 2); // 'c'
    ok = (c == 'c');
    if (ok) {
        std::cout << GREEN << "charAt(tree, left) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "charAt(tree, left) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root5);

    // Test 6: cây 2 lá, index ở phải
    Rope::Node* l6 = new Rope::Node("abc");
    Rope::Node* r6 = new Rope::Node("def");
    Rope::Node* root6 = new Rope::Node();
    root6->left = l6;
    root6->right = r6;
    rope.update(root6);
    c = rope.charAt(root6, 4); // 'e'
    ok = (c == 'e');
    if (ok) {
        std::cout << GREEN << "charAt(tree, right) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "charAt(tree, right) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root6);

    // Test 7: cây nhiều tầng, index ở giữa
    Rope::Node* l7 = new Rope::Node("abc");
    Rope::Node* r7 = new Rope::Node("defg");
    Rope::Node* root7 = new Rope::Node();
    root7->left = l7;
    root7->right = r7;
    rope.update(root7);
    c = rope.charAt(root7, 5); // 'f'
    ok = (c == 'f');
    if (ok) {
        std::cout << GREEN << "charAt(tree, mid) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "charAt(tree, mid) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root7);

    // Test 8: cây nhiều tầng, index cuối cùng
    Rope::Node* l8 = new Rope::Node("abc");
    Rope::Node* r8 = new Rope::Node("defg");
    Rope::Node* root8 = new Rope::Node();
    root8->left = l8;
    root8->right = r8;
    rope.update(root8);
    c = rope.charAt(root8, 6); // 'g'
    ok = (c == 'g');
    if (ok) {
        std::cout << GREEN << "charAt(tree, last) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "charAt(tree, last) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root8);

    // Test 9: cây nhiều tầng, index vượt quá
    Rope::Node* l9 = new Rope::Node("abc");
    Rope::Node* r9 = new Rope::Node("defg");
    Rope::Node* root9 = new Rope::Node();
    root9->left = l9;
    root9->right = r9;
    rope.update(root9);
    c = rope.charAt(root9, 7); // out-of-bounds
    ok = (c == '\0');
    if (ok) {
        std::cout << GREEN << "charAt(tree, out-of-bounds) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "charAt(tree, out-of-bounds) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root9);
}

void TestHelper::test_toString() {
    Rope rope;
    std::cout << MAGENTA << "Test toString(Node*):" << RESET << std::endl;

    // Test 1: nullptr node
    std::string s = rope.toString(nullptr);
    bool ok = (s == "");
    if (ok) {
        std::cout << GREEN << "toString(nullptr) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "toString(nullptr) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 2: node lá rỗng
    Rope::Node* leaf2 = new Rope::Node("");
    s = rope.toString(leaf2);
    ok = (s == "");
    if (ok) {
        std::cout << GREEN << "toString(empty leaf) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "toString(empty leaf) failed." << RESET << std::endl;
        num_incorrect++;
    }
    delete leaf2;

    // Test 3: node lá có dữ liệu
    Rope::Node* leaf3 = new Rope::Node("abc");
    s = rope.toString(leaf3);
    ok = (s == "abc");
    if (ok) {
        std::cout << GREEN << "toString(leaf) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "toString(leaf) failed." << RESET << std::endl;
        num_incorrect++;
    }
    delete leaf3;

    // Test 4: cây 2 lá
    Rope::Node* l4 = new Rope::Node("abc");
    Rope::Node* r4 = new Rope::Node("def");
    Rope::Node* root4 = new Rope::Node();
    root4->left = l4;
    root4->right = r4;
    rope.update(root4);
    s = rope.toString(root4);
    ok = (s == "abcdef");
    if (ok) {
        std::cout << GREEN << "toString(two leaves) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "toString(two leaves) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root4);

    // Test 5: cây nhiều tầng
    Rope::Node* l5a = new Rope::Node("ab");
    Rope::Node* l5b = new Rope::Node("cd");
    Rope::Node* left5 = new Rope::Node();
    left5->left = l5a;
    left5->right = l5b;
    rope.update(left5);

    Rope::Node* r5a = new Rope::Node("ef");
    Rope::Node* r5b = new Rope::Node("gh");
    Rope::Node* right5 = new Rope::Node();
    right5->left = r5a;
    right5->right = r5b;
    rope.update(right5);

    Rope::Node* root5 = new Rope::Node();
    root5->left = left5;
    root5->right = right5;
    rope.update(root5);

    s = rope.toString(root5);
    ok = (s == "abcdefgh");
    if (ok) {
        std::cout << GREEN << "toString(multi-level tree) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "toString(multi-level tree) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root5);

    // Test 6: cây có lá rỗng
    Rope::Node* l6 = new Rope::Node("");
    Rope::Node* r6 = new Rope::Node("xyz");
    Rope::Node* root6 = new Rope::Node();
    root6->left = l6;
    root6->right = r6;
    rope.update(root6);
    s = rope.toString(root6);
    ok = (s == "xyz");
    if (ok) {
        std::cout << GREEN << "toString(tree with empty leaf) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "toString(tree with empty leaf) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root6);

    // Test 7: cây chỉ có một nhánh trái
    Rope::Node* l7 = new Rope::Node("abc");
    Rope::Node* root7 = new Rope::Node();
    root7->left = l7;
    root7->right = nullptr;
    rope.update(root7);
    s = rope.toString(root7);
    ok = (s == "abc");
    if (ok) {
        std::cout << GREEN << "toString(left only) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "toString(left only) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root7);

    // Test 8: cây chỉ có một nhánh phải
    Rope::Node* r8 = new Rope::Node("def");
    Rope::Node* root8 = new Rope::Node();
    root8->left = nullptr;
    root8->right = r8;
    rope.update(root8);
    s = rope.toString(root8);
    ok = (s == "def");
    if (ok) {
        std::cout << GREEN << "toString(right only) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "toString(right only) failed." << RESET << std::endl;
        num_incorrect++;
    }
    rope.destroy(root8);
}

void TestHelper::test_destroy() {
    Rope rope;
    std::cout << MAGENTA << "Test destroy(Node*&):" << RESET << std::endl;

    // Test 1: destroy nullptr
    Rope::Node* node1 = nullptr;
    rope.destroy(node1);
    bool ok = (node1 == nullptr);
    if (ok) {
        std::cout << GREEN << "destroy(nullptr) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "destroy(nullptr) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 2: destroy node lá
    Rope::Node* node2 = new Rope::Node("abc");
    rope.destroy(node2);
    ok = (node2 == nullptr);
    if (ok) {
        std::cout << GREEN << "destroy(leaf) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "destroy(leaf) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 3: destroy cây 2 lá
    Rope::Node* l3 = new Rope::Node("abc");
    Rope::Node* r3 = new Rope::Node("def");
    Rope::Node* root3 = new Rope::Node();
    root3->left = l3;
    root3->right = r3;
    rope.update(root3);
    rope.destroy(root3);
    ok = (root3 == nullptr);
    if (ok) {
        std::cout << GREEN << "destroy(two leaves) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "destroy(two leaves) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 4: destroy cây nhiều tầng
    Rope::Node* l4a = new Rope::Node("ab");
    Rope::Node* l4b = new Rope::Node("cd");
    Rope::Node* left4 = new Rope::Node();
    left4->left = l4a;
    left4->right = l4b;
    rope.update(left4);

    Rope::Node* r4a = new Rope::Node("ef");
    Rope::Node* r4b = new Rope::Node("gh");
    Rope::Node* right4 = new Rope::Node();
    right4->left = r4a;
    right4->right = r4b;
    rope.update(right4);

    Rope::Node* root4 = new Rope::Node();
    root4->left = left4;
    root4->right = right4;
    rope.update(root4);

    rope.destroy(root4);
    ok = (root4 == nullptr);
    if (ok) {
        std::cout << GREEN << "destroy(multi-level tree) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "destroy(multi-level tree) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 5: destroy cây chỉ có một nhánh trái
    Rope::Node* l5 = new Rope::Node("abc");
    Rope::Node* root5 = new Rope::Node();
    root5->left = l5;
    root5->right = nullptr;
    rope.update(root5);
    rope.destroy(root5);
    ok = (root5 == nullptr);
    if (ok) {
        std::cout << GREEN << "destroy(left only) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "destroy(left only) failed." << RESET << std::endl;
        num_incorrect++;
    }

    // Test 6: destroy cây chỉ có một nhánh phải
    Rope::Node* r6 = new Rope::Node("def");
    Rope::Node* root6 = new Rope::Node();
    root6->left = nullptr;
    root6->right = r6;
    rope.update(root6);
    rope.destroy(root6);
    ok = (root6 == nullptr);
    if (ok) {
        std::cout << GREEN << "destroy(right only) correct." << RESET << std::endl;
        num_correct++;
    } else {
        std::cout << RED << "destroy(right only) failed." << RESET << std::endl;
        num_incorrect++;
    }
}


int main() {
    cout << BLUE << "=========== LMS TESTS ============" << RESET << endl;
    sample_01();
    sample_02();
    sample_03();
    sample_04();
    sample_05();
    sample_06();
    sample_07();
    sample_08();
    cout << BLUE << "\n=========== OTHER TESTS ============" << RESET << endl;
    test_case_09();
    test_case_10();
    test_case_11();
    cout << BLUE << "\n=========== EXAMPLE TESTS ============" << RESET << endl;
    test_example_3_1();

    cout << BLUE << "\n=========== ROPE PRIVATE FUNCTION TESTS ============" << RESET << endl;
    TestHelper::test_height();
    TestHelper::test_getTotalLength();
    TestHelper::test_update();
    TestHelper::test_rotateLeft();
    TestHelper::test_rotateRight();
    TestHelper::test_split();
    TestHelper::test_concatNodes();
    TestHelper::test_charAt();
    TestHelper::test_toString();
    TestHelper::test_destroy();

    cout << BLUE << "\n=========== Summary ============" << RESET << endl;
    if (num_incorrect == 0)
    {
        cout << GREEN << "Passed all tests." << RESET << std::endl;
        cout << GREEN << "Passed: " << num_correct << " " << RED << "Failed: " << num_incorrect << RESET << std::endl;
    }
    else
    {
        cout << GREEN << "Passed: " << num_correct << " " << RED << "Failed: " << num_incorrect << RESET << std::endl;
    }
    return 0;
}

