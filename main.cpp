#include "RopeTextBuffer.h"
#include <sstream> // đã có

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

