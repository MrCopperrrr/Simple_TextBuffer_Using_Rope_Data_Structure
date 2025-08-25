#include "RopeTextBuffer.h"
// ----------------- Node private methods -----------------
// Định nghĩa hàm Node rỗng
Rope::Node::Node()
    : left(nullptr), right(nullptr), data(""), weight(0), height(1),
      balance(EH), totalLength(0) {}

// Định nghĩa hàm Node với dữ liệu chuỗi
Rope::Node::Node(const std::string& s)
    : left(nullptr), right(nullptr), data(s),
      weight(static_cast<int>(s.size())), height(1),
      balance(EH), totalLength(static_cast<int>(s.size())) {}

// Kiểm tra xem nút có phải là lá không
bool Rope::Node::isLeaf() const {
    return left == nullptr && right == nullptr;
}

// ----------------- Rope private methods -----------------
int Rope::height(Node* node) const {
    // Trả về chiều cao của node, nếu node rỗng thì trả về 0
    return node ? node->height : 0;
}

//getTotalLength v1
// int Rope::getTotalLength(Node* node) const {
//     // Tính tổng số ký tự trong cây con gốc tại node
//     // Nếu node là nullptr, trả về 0
//     if (!node) return 0;
//     if (node->isLeaf()) {
//         // Nếu là lá, weight chính là độ dài chuỗi data
//         return node->weight;
//     }
//     // Nếu là node trong, weight là tổng ký tự bên trái,
//     // getTotalLength(node->right) là tổng ký tự bên phải
//     // Độ phức tạp O(log n) vì cây cân bằng AVL, chiều cao log n
//     return node->weight + getTotalLength(node->right);
// }

//getTotalLength v2
int Rope::getTotalLength(Node* node) const {
    return node ? node->totalLength : 0;
}


// update v1
// void Rope::update(Node* node) {
//     // Cập nhật lại weight, height, balance cho node
//     if (!node) return;
//     if (node->isLeaf()) {
//         node->weight = node->data.length();
//         node->height = 1;
//         node->balance = Node::EH;
//     } else {
//         // Node trong: weight là tổng ký tự bên trái
//         node->weight = getTotalLength(node->left);
//         int lh = height(node->left);
//         int rh = height(node->right);
//         node->height = 1 + std::max(lh, rh);
//         // Cập nhật hệ số cân bằng AVL
//         if (lh > rh) node->balance = Node::LH;
//         else if (lh < rh) node->balance = Node::RH;
//         else node->balance = Node::EH;
//     }
// }

//update v2 
// void Rope::update(Node* node) {
//     if (!node) return;

//     int leftHeight = node->left ? node->left->height : 0;
//     int rightHeight = node->right ? node->right->height : 0;

//     int leftLength = node->left ? node->left->totalLength : 0;
//     int rightLength = node->right ? node->right->totalLength : 0;

//     if (node->isLeaf()) {
//         node->weight = (int)node->data.length();
//         node->totalLength = node->weight;
//         node->height = 1;
//         node->balance = Node::EH;
//     } else {
//         node->weight = leftLength; // AVL rope convention
//         node->totalLength = leftLength + rightLength;
//         node->height = std::max(leftHeight, rightHeight) + 1;
//         node->balance = (leftHeight > rightHeight) ? Node::LH :
//                         (leftHeight < rightHeight) ? Node::RH : Node::EH;
//     }
// }

//update v3
void Rope::update(Node* node) {
    if (!node) return;

    // Sử dụng height() để lấy chiều cao, đảm bảo nút rỗng trả về 0
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    int leftLength = node->left ? node->left->totalLength : 0;
    int rightLength = node->right ? node->right->totalLength : 0;

    if (node->isLeaf()) {
        node->weight = (int)node->data.length();
        node->totalLength = node->weight;
        node->height = 0;
        node->balance = Node::EH; // Sửa balance thành EH
    } else {
        node->weight = leftLength; // AVL rope convention
        node->totalLength = leftLength + rightLength;
        node->height = std::max(leftHeight, rightHeight) + 1;
        if (rightHeight - leftHeight > 0)
                node->balance = Node::RH;
        else if(rightHeight - leftHeight < 0)
                node->balance = Node::LH;
        else 
                node->balance = Node::EH;
    }
}


// rotateLeft v1
// Rope::Node* Rope::rotateLeft(Node* x) {
//     // Xoay trái tại node x
//     //      x                y
//     //       \              / \
//     //        y    =>      x   T3
//     //       / \          / \
//     //     T2  T3       T1  T2
//     Node* y = x->right;
//     Node* T2 = y ? y->left : nullptr;

//     // Thực hiện xoay
//     if (y) {
//         y->left = x;
//         x->right = T2;

//         // Cập nhật lại thông tin phụ trợ cho x và y
//         Rope::update(x);
//         Rope::update(y);
//         return y; // y là gốc mới
//     }
//     return x; // Không xoay được nếu y là nullptr
// }

//rotateLeft v2
Rope::Node* Rope::rotateLeft(Node* x) {
    if (!x || !x->right) return x; // Không xoay được
    
    Node* y = x->right;
    Node* T2 = y->left;

    // Thực hiện xoay
    y->left = x;
    x->right = T2;

    // Cập nhật lại thông tin phụ trợ (con trước, cha sau)
    update(x);      // cập nhật x trước
    update(y);      // cập nhật y sau

    // Đảm bảo không gọi update(y) thêm lần nữa ở ngoài test!
    // Nếu gọi update(y) nhiều lần, height sẽ bị cộng dồn sai nếu cây con chưa đúng.

    return y; // y là gốc mới
}

//rotateRight v1
// Rope::Node* Rope::rotateRight(Node* y) {
//     // Xoay phải tại node y
//     //        y              x
//     //       /              / \
//     //      x      =>     T1   y
//     //     / \                / \
//     //   T1  T2             T2  T3
//     Node* x = y->left;
//     Node* T2 = x ? x->right : nullptr;

//     // Thực hiện xoay
//     if (x) {
//         x->right = y;
//         y->left = T2;

//         // Cập nhật lại thông tin phụ trợ cho y và x
//         Rope::update(y);
//         Rope::update(x);
//         return x; // x là gốc mới
//     }
//     return y; // Không xoay được nếu x là nullptr
// }

//rotateRight v2
Rope::Node* Rope::rotateRight(Node* y) {
    if (!y || !y->left) return y; // Không xoay được
    
    Node* x = y->left;
    Node* T2 = x->right;

    // Thực hiện xoay
    x->right = y;
    y->left = T2;

    // Cập nhật lại thông tin phụ trợ (con trước, cha sau)
    update(y);
    update(x);

    return x; // x là gốc mới
}

//rebalance v1
// Rope::Node* Rope::rebalance(Node* node) {
//     // Kiểm tra và cân bằng lại node nếu bị lệch trái hoặc phải
//     // Độ phức tạp O(1) vì chỉ thực hiện tối đa 2 phép xoay

//     if (!node) return node;

//     // Cập nhật lại thông tin trước khi kiểm tra cân bằng
//     Rope::update(node);

//     // Lệch trái (Left Higher)
//     if (node->balance == Node::LH) {
//         if (node->left && node->left->balance == Node::RH) {
//             // Trường hợp Left-Right: xoay trái con trái, sau đó xoay phải node
//             node->left = Rope::rotateLeft(node->left);
//         }
//         // Trường hợp Left-Left hoặc đã xử lý xong Left-Right: xoay phải node
//         return Rope::rotateRight(node);
//     }
//     // Lệch phải (Right Higher)
//     else if (node->balance == Node::RH) {
//         if (node->right && node->right->balance == Node::LH) {
//             // Trường hợp Right-Left: xoay phải con phải, sau đó xoay trái node
//             node->right = Rope::rotateRight(node->right);
//         }
//         // Trường hợp Right-Right hoặc đã xử lý xong Right-Left: xoay trái node
//         return Rope::rotateLeft(node);
//     }
//     // Đã cân bằng
//     return node;
// }

//rebalance v2
Rope::Node* Rope::rebalance(Node* node) {
    if (!node) return nullptr;

    // Cập nhật node hiện tại trước khi kiểm tra
    update(node);

    // Lệch trái
    if (node->balance == Node::LH) {
        if (node->left && node->left->balance == Node::RH) {
            // Left-Right: xoay trái con trái
            node->left = rotateLeft(node->left);
        }
        node = rotateRight(node);
    }
    // Lệch phải
    else if (node->balance == Node::RH) {
        if (node->right && node->right->balance == Node::LH) {
            // Right-Left: xoay phải con phải
            node->right = rotateRight(node->right);
        }
        node = rotateLeft(node);
    }

    // Đảm bảo node trả về đã được cập nhật
    update(node);
    return node;
}

//split v1
// void Rope::split(Node* node, int index, Node*& outLeft, Node*& outRight) {
//     // Tách cây tại node thành hai cây con dựa vào vị trí index
//     // outLeft: chứa chuỗi từ đầu đến index-1
//     // outRight: chứa chuỗi từ index đến hết
//     // Độ phức tạp O(log n) vì cây AVL

//     if (!node) {
//         outLeft = nullptr;
//         outRight = nullptr;
//         return;
//     }

//     if (node->isLeaf()) {
//         // Nếu là lá, tách chuỗi data tại vị trí index
//         if (index <= 0) {
//             // Tất cả sang phải
//             outLeft = nullptr;
//             outRight = node;
//         } else if (index >= (int)node->data.length()) {
//             // Tất cả sang trái
//             outLeft = node;
//             outRight = nullptr;
//         } else {
//             // Tách chuỗi thành hai node lá mới
//             outLeft = new Node(node->data.substr(0, index));
//             outRight = new Node(node->data.substr(index));
//             delete node;
//         }
//         return;
//     }

//     // Nếu là node trong
//     if (index < node->weight) {
//         // Tách bên trái
//         Node *leftL = nullptr, *leftR = nullptr;
//         split(node->left, index, leftL, leftR);
//         // Kết hợp leftR với node->right thành cây phải mới
//         Node* newRight = concatNodes(leftR, node->right);
//         outLeft = leftL;
//         outRight = newRight;
//         delete node;
//     } else {
//         // Tách bên phải
//         Node *rightL = nullptr, *rightR = nullptr;
//         split(node->right, index - node->weight, rightL, rightR);
//         // Kết hợp node->left với rightL thành cây trái mới
//         Node* newLeft = concatNodes(node->left, rightL);
//         outLeft = newLeft;
//         outRight = rightR;
//         delete node;
//     }
// }

//split v2
// void Rope::split(Node* node, int index, Node*& outLeft, Node*& outRight) {
//     // Kết quả mặc định
//     outLeft = nullptr;
//     outRight = nullptr;
//     if (!node) return;

//     // Đảm bảo index trong [0..total]
//     int total = getTotalLength(node);
//     if (index <= 0) { outRight = node; return; }
//     if (index >= total) { outLeft = node; return; }

//     if (node->isLeaf()) {
//         // 0 < index < len(data)
//         const int len = static_cast<int>(node->data.length());
//         // tạo hai lá mới
//         outLeft  = new Node(node->data.substr(0, index));
//         outRight = new Node(node->data.substr(index, len - index));
//         delete node; // node gốc không còn dùng nữa
//         return;
//     }

//     // Nút trong: dùng weight = tổng ký tự cây con trái
//     if (index < node->weight) {
//         // Tách trong cây trái
//         Node *L1 = nullptr, *L2 = nullptr;
//         split(node->left, index, L1, L2);
//         // Cây phải mới = concat(L2, node->right)
//         Node* Rnew = concatNodes(L2, node->right);
//         outLeft  = L1;
//         outRight = Rnew;
//         // node chỉ là "vỏ" đã bị tách -> xóa
//         node->left = node->right = nullptr; // đề phòng destructor tương lai
//         delete node;
//     } else if (index > node->weight) {
//         // Tách trong cây phải
//         Node *R1 = nullptr, *R2 = nullptr;
//         split(node->right, index - node->weight, R1, R2);
//         // Cây trái mới = concat(node->left, R1)
//         Node* Lnew = concatNodes(node->left, R1);
//         outLeft  = Lnew;
//         outRight = R2;
//         node->left = node->right = nullptr;
//         delete node;
//     } else { 
//         // index == node->weight: tách "đúng ranh" giữa trái & phải -> không cần concat
//         outLeft  = node->left;
//         outRight = node->right;
//         node->left = node->right = nullptr;
//         delete node;
//     }
// }

//slpit v3
void Rope::split(Node* node, int index, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }

    if (node->isLeaf()) {
        // Nếu là lá
        if (index <= 0) {
            left = nullptr;
            right = node;
        } else if (index >= (int)node->data.size()) {
            left = node;
            right = nullptr;
        } else {
            left = new Node(node->data.substr(0, index));
            right = new Node(node->data.substr(index));
        }
        return;
    }

    if (index < node->weight) {
        Node *l, *r;
        split(node->left, index, l, r);
        left = l;
        right = concatNodes(r, node->right);
    } else {
        Node *l, *r;
        split(node->right, index - node->weight, l, r);
        left = concatNodes(node->left, l);
        right = r;
    }
}


//concatNodes v1
// Rope::Node* Rope::concatNodes(Node* left, Node* right) {
//     // Nối hai cây Rope thành một cây mới bằng cách tạo node gốc mới
//     // Không chỉnh sửa trực tiếp left hoặc right
//     // Độ phức tạp O(log n) do có thể cần cân bằng lại cây

//     if (!left) return right;
//     if (!right) return left;

//     // Tạo node gốc mới, không chứa data (node trong)
//     Node* newRoot = new Node();
//     newRoot->left = left;
//     newRoot->right = right;
//     newRoot->data = ""; // node trong không chứa data

//     // Cập nhật lại thông tin phụ trợ cho node mới
//     Rope::update(newRoot);

//     // Đảm bảo cân bằng AVL cho cây mới
//     newRoot = Rope::rebalance(newRoot);

//     return newRoot;
// }

//concatNodes v2
// Rope::Node* Rope::concatNodes(Node* left, Node* right) {
//     if (!left)  return right;
//     if (!right) return left;

//     // Nếu chênh lệch chiều cao quá lớn, gắn vào sâu hơn
//     int hl = height(left);
//     int hr = height(right);

//     if (hl > hr + 1) {
//         // Nối vào nhánh phải của left
//         Node* newRight = concatNodes(left->right, right);
//         Node* newRoot = new Node();
//         newRoot->left = left->left;
//         newRoot->right = newRight;
//         newRoot->data = "";
//         update(newRoot);
//         return rebalance(newRoot);
//     } 
//     else if (hr > hl + 1) {
//         // Nối vào nhánh trái của right
//         Node* newLeft = concatNodes(left, right->left);
//         Node* newRoot = new Node();
//         newRoot->left = newLeft;
//         newRoot->right = right->right;
//         newRoot->data = "";
//         update(newRoot);
//         return rebalance(newRoot);
//     } 
//     else {
//         // Chiều cao 2 bên chênh lệch <= 1 → tạo node gốc mới trực tiếp
//         Node* newRoot = new Node();
//         newRoot->left = left;
//         newRoot->right = right;
//         newRoot->data = "";
//         update(newRoot);
//         return rebalance(newRoot);
//     }
// }

//concatNodes v3
Rope::Node* Rope::concatNodes(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    Node* newRoot = new Node();
    newRoot->left = left;
    newRoot->right = right;
    newRoot->data = ""; // node trong không chứa dữ liệu
    update(newRoot);    // cập nhật weight, height, totalLength
    return rebalance(newRoot);
}


//charAt v1
// char Rope::charAt(Node* node, int index) const {
//     // Trả về ký tự tại vị trí index trong cây Rope
//     // Độ phức tạp O(log n)

//     if (!node) return '\0'; // hoặc throw nếu muốn

//     if (node->isLeaf()) {
//         // Nếu là lá, trả về ký tự tại vị trí index trong data
//         if (index < 0 || index >= (int)node->data.length()) return '\0';
//         return node->data[index];
//     }

//     // Nếu là node trong, so sánh index với weight
//     if (index < node->weight) {
//         // Nằm bên trái
//         return charAt(node->left, index);
//     } else {
//         // Nằm bên phải
//         return charAt(node->right, index - node->weight);
//     }
// }

//charAt v2
char Rope::charAt(Node* node, int index) const {
    if (!node || index < 0) return '\0'; // out-of-bounds

    if (node->isLeaf()) {
        // Kiểm tra giới hạn trong node lá
        if (index >= (int)node->data.length()) return '\0';
        return node->data[index];
    }

    // Node trong: weight = tổng ký tự bên trái
    if (index < node->weight) {
        return charAt(node->left, index);
    } else {
        return charAt(node->right, index - node->weight);
    }
}

// toString v1
// std::string Rope::toString(Node* node) const {
//     // Trả về chuỗi dữ liệu được lưu trong cây Rope
//     // Độ phức tạp O(n) vì phải duyệt qua toàn bộ các node lá
//     if (!node) return "";
//     if (node->isLeaf()) {
//         return node->data;
//     }
//     // Duyệt trái rồi phải (in-order)
//     return toString(node->left) + toString(node->right);
// }

// toString v2 with helper
void Rope::toStringHelper(Node* node, std::string& result) const {
    if (!node) return;
    if (node->isLeaf()) {
        result += node->data;
    } else {
        toStringHelper(node->left, result);
        toStringHelper(node->right, result);
    }
}

std::string Rope::toString(Node* node) const {
    std::string result;
    result.reserve(getTotalLength(node)); // tránh realloc nhiều lần
    toStringHelper(node, result);
    return result;
}

void Rope::destroy(Node*& node) {
    // Giải phóng toàn bộ bộ nhớ được cấp phát cho cây có gốc tại node
    // Độ phức tạp O(n)
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
}




// ----------------- Rope public methods -----------------
// Đã đúng yêu cầu đề bài:
// Rope()                // Khởi tạo Rope rỗng
// ~Rope()               // Giải phóng bộ nhớ động O(n)
// int length() const    // Trả về tổng số ký tự, O(1)
// bool empty() const    // Kiểm tra Rope rỗng, O(1)
// char charAt(int) const// Trả về ký tự tại index, O(log n), ném out_of_range nếu index không hợp lệ
// string substring(int, int) const // Trả về chuỗi con, O(log n), ném out_of_range nếu start/length không hợp lệ
// void insert(int, const string&)  // Chèn chuỗi vào vị trí index, O(log n), ném out_of_range nếu index không hợp lệ
// void deleteRange(int, int)       // Xoá length ký tự từ start, O(log n), ném out_of_range nếu start/length không hợp lệ
// string toString() const          // Trả về toàn bộ chuỗi, O(n)

Rope::Rope() {
    // Khởi tạo Rope rỗng
    root = nullptr;
}

Rope::~Rope() {
    // Giải phóng toàn bộ bộ nhớ động của Rope
    destroy(root);
}
//length v1
// int Rope::length() const {
//     // Trả về tổng số ký tự đang được lưu trong Rope
//     // Độ phức tạp O(1) vì chỉ cần lấy tổng ký tự từ root
//     return getTotalLength(root);
// }

//length v2
int Rope::length() const {
    return root ? root->totalLength : 0;
}

//empty v1
// bool Rope::empty() const {
//     // Kiểm tra Rope có rỗng hay không
//     // Độ phức tạp O(1)
//     return root == nullptr || getTotalLength(root) == 0;
// }

//empty v2
bool Rope::empty() const {
    return !root || root->totalLength == 0;
}

// charAt v1
// char Rope::charAt(int index) const {
//     if (index < 0 || index >= length()) {
//         throw std::out_of_range("Index is invalid!");
//     }
//     return charAt(root, index);
// }

//charAt v2
char Rope::charAt(int index) const {
    int len = length(); // O(1) nếu dùng totalLength
    if (index < 0 || index >= len) {
        throw std::out_of_range("Index is invalid!");
    }
    return charAt(root, index); // Gọi phiên bản đệ quy
}

// substring v1
// std::string Rope::substring(int start, int length) const {
//     // Trả về chuỗi con gồm length ký tự bắt đầu từ vị trí start
//     // Độ phức tạp O(log n)
//     if (start < 0 || length < 0 || start >= this->length() || length == 0) return "";
//     if (start + length > this->length()) length = this->length() - start;

//     Node *left = nullptr, *midRight = nullptr, *middle = nullptr, *right = nullptr;
//     split(root, start, left, midRight);
//     split(midRight, length, middle, right);

//     std::string result = toString(middle);

//     // Ghép lại cây gốc như cũ
//     Node* tmp = concatNodes(left, middle);
//     root = concatNodes(tmp, right);

//     return result;
// }

//substring v2
// helper: trả về số ký tự đã append vào 'out' từ subtree 'node',
// bắt đầu tại vị trí 'start' (tính theo subtree đó), tối đa 'len' ký tự.
int Rope::collectSubstring(Node* node, int start, int len, string &out) const {
    if (!node || len <= 0) return 0;

    if (node->isLeaf()) {
        int n = (int)node->data.length();
        if (start >= n) return 0;                // start nằm ngoài lá này
        int take = std::min(len, n - start);     // số ký tự có thể lấy từ lá này
        if (take > 0) out.append(node->data.substr(start, take));
        return take;
    }

    int leftLen = node->left ? node->left->totalLength : 0;
    int taken = 0;

    if (start < leftLen) {
        // Lấy từ bên trái trước (bắt đầu ở vị trí 'start')
        taken += collectSubstring(node->left, start, len, out);
        // Nếu còn thiếu, lấy tiếp từ bên phải bắt đầu từ pos 0
        if (taken < len) {
            taken += collectSubstring(node->right, 0, len - taken, out);
        }
    } else {
        // Bắt đầu trong bên phải (dịch start sang subtree phải)
        taken += collectSubstring(node->right, start - leftLen, len, out);
    }

    return taken;
}

string Rope::substring(int start, int length) const {
    // Kiểm tra điều kiện ngoại lệ theo đề bài (message phải chính xác)
    int total = this->length(); // O(1) nếu Node có totalLength
    if (start < 0 || start >= total) {
        throw std::out_of_range("Index is invalid!");
    }
    if (length < 0 || start + length > total) {
        throw std::out_of_range("Length is invalid!");
    }
    if (length == 0) return "";

    string res;
    res.reserve(length); // tránh nhiều realloc
    collectSubstring(root, start, length, res);
    return res;
}

// insert v1
// void Rope::insert(int index, const std::string& s) {
//     // Chèn chuỗi s vào vị trí index
//     // Độ phức tạp O(log n)
//     if (s.empty()) return;
//     if (index < 0 || index > length()) throw std::out_of_range("Index is invalid!");

//     // Tách thành left và right tại vị trí index
//     Node *left = nullptr, *right = nullptr;
//     split(root, index, left, right);

//     Node* mid = nullptr;
//     int n = (int)s.length();
//     for (int i = 0; i < n; i += CHUNK_SIZE) {
//         Node* chunk = new Node(s.substr(i, CHUNK_SIZE));
//         mid = concatNodes(mid, chunk);
//     }

//     Node* tmp = concatNodes(left, mid);
//     root = concatNodes(tmp, right);
// }

//insert v2
Rope::Node* Rope::buildFromString(const std::string& s) {
    Node* rope = nullptr;
    int n = (int)s.size();
    for (int i = 0; i < n; i += CHUNK_SIZE) {
        Node* chunk = new Node(s.substr(i, CHUNK_SIZE));
        rope = concatNodes(rope, chunk); // concatNodes đã tự cân bằng
    }
    return rope;
}

void Rope::insert(int index, const std::string& s) {
    if (s.empty()) return;
    if (index < 0 || index > length()) {
        throw std::out_of_range("Index is invalid!");
    }

    Node *left = nullptr, *right = nullptr;
    split(root, index, left, right);

    Node* mid = buildFromString(s);

    Node* tmp = concatNodes(left, mid);
    root = concatNodes(tmp, right);
}

// deleteRange v1
// void Rope::deleteRange(int start, int length) {
//     // Xoá length ký tự bắt đầu từ vị trí start
//     // Độ phức tạp O(log n)
//     if (start < 0 || length < 0 || start >= this->length() || length == 0) return;
//     if (start + length > this->length()) length = this->length() - start;

//     // Tách thành 3 phần: left | middle | right
//     Node *left = nullptr, *midRight = nullptr, *middle = nullptr, *right = nullptr;
//     split(root, start, left, midRight);
//     split(midRight, length, middle, right);

//     // Ghép lại cây mới: left + right (bỏ middle)
//     root = concatNodes(left, right);

//     // Giải phóng middle
//     destroy(middle);
// }

void Rope::deleteRange(int start, int len) {
    // Kiểm tra đầu vào
    if (start < 0 || start >= this->length()) { 
        throw std::out_of_range("Index is invalid!");
    }
    if (len < 0) {
        throw std::out_of_range("Length is invalid!");
    }
    if (len == 0) return;
    if (start + len > this->length()) {
        throw std::out_of_range("Length is invalid!");
    }

    // Tách thành 3 phần: left | middle | right
    Node *left = nullptr, *midRight = nullptr;
    Node *middle = nullptr, *right = nullptr;

    split(root, start, left, midRight);    // left | midRight
    split(midRight, len, middle, right);   // middle | right

    // Ghép lại cây mới: left + right
    root = concatNodes(left, right);

    // Giải phóng middle
    destroy(middle);
}

std::string Rope::toString() const {
    // Chuyển toàn bộ Rope thành một chuỗi liên tục
    // Độ phức tạp O(n)
    return toString(root);
}



// ----------------- RopeTextBuffer -----------------
RopeTextBuffer::RopeTextBuffer() {
    // Khởi tạo buffer rỗng, con trỏ ở vị trí đầu tiên
    cursorPos = 0;
    history = new HistoryManager();
    // Rope rope tự động khởi tạo rỗng
}

RopeTextBuffer::~RopeTextBuffer() {
    // Giải phóng bộ nhớ cho history (rope tự giải phóng qua destructor)
    delete history;
}

//insert v1
// void RopeTextBuffer::insert(const std::string& s) {
//     // Chèn chuỗi mới tại vị trí ngay trước vị trí con trỏ hiện tại
//     // Độ phức tạp O(log n)
//     rope.insert(cursorPos, s);
//     cursorPos += s.length();
//     // TODO: Ghi lại lịch sử thao tác nếu cần
// }

//insert v2
// void RopeTextBuffer::insert(const std::string& s) {
//     if (s.empty()) return; // Không chèn nếu chuỗi rỗng

//     rope.insert(cursorPos, s); // Rope tự ném out_of_range nếu index sai
//     cursorPos += static_cast<int>(s.length());

//     // Ghi lại lịch sử thao tác (undo/redo) - sẽ implement sau
//     // history->recordInsert(cursorPosBefore, s);
// }

//insert v3
void RopeTextBuffer::insert(const std::string& s) {
    if (s.empty()) return; // Không chèn nếu chuỗi rỗng

    int cursorBefore = cursorPos;

    rope.insert(cursorPos, s); // Rope tự ném out_of_range nếu index sai
    cursorPos += static_cast<int>(s.length());

    // Lưu lịch sử
    HistoryManager::Action act;
    act.actionName = "insert";
    act.cursorBefore = cursorBefore;
    act.cursorAfter = cursorPos;
    act.oldData = "";    // Không có chuỗi cũ
    act.newData = s;     // Chuỗi mới được chèn
    act.data = s;        // Sửa: lưu dữ liệu chèn vào trường data để printHistory đúng format

    history->addAction(act);
}

//deleteRange v1
// void RopeTextBuffer::deleteRange(int length) {
//     // Xoá một đoạn văn bản bắt đầu từ vị trí ngay sau con trỏ, với độ dài cho trước
//     // Độ phức tạp O(log n)
//     int totalLen = rope.length();
//     if (length < 0 || cursorPos + length > totalLen) {
//         throw std::out_of_range("Length is invalid!");
//     }
//     if (length == 0) return;
//     rope.deleteRange(cursorPos, length);
//     // Không thay đổi vị trí con trỏ
//     // TODO: Ghi lại lịch sử thao tác nếu cần
// }

//deleteRange v2
// void RopeTextBuffer::deleteRange(int length) {
//     if (length < 0) {
//         throw std::out_of_range("Length is invalid!");
//     }
//     if (length == 0) return;

//     int totalLen = rope.length();
//     if (cursorPos + length > totalLen) {
//         throw std::out_of_range("Length is invalid!");
//     }

//     rope.deleteRange(cursorPos, length);

//     // Ghi lại lịch sử thao tác (undo/redo) - sẽ implement sau
//     // history->recordDelete(cursorPos, deletedString);
// }

//deleteRange v3
void RopeTextBuffer::deleteRange(int length) {
    // Đúng yêu cầu đề bài:
    // - Xóa một đoạn văn bản bắt đầu từ vị trí ngay sau con trỏ, với độ dài cho trước
    // - Đầu vào: length là số ký tự cần xóa
    // - Độ phức tạp: O(log n)
    // - Ngoại lệ: Ném out_of_range("Length is invalid!") nếu length vượt quá giới hạn của chuỗi

    if (length < 0) {
        throw std::out_of_range("Length is invalid!");
    }
    if (length == 0) return;

    int totalLen = rope.length();
    if (cursorPos + length > totalLen) {
        throw std::out_of_range("Length is invalid!");
    }

    int cursorBefore = cursorPos;
    std::string deleted = rope.substring(cursorPos, length); // Lưu chuỗi bị xóa

    rope.deleteRange(cursorPos, length);

    int cursorAfter = cursorPos; // Sau khi xóa, con trỏ ở vị trí cũ

    // Lưu lịch sử
    HistoryManager::Action act;
    act.actionName = "delete";
    act.cursorBefore = cursorBefore;
    act.cursorAfter = cursorAfter;
    act.oldData = deleted; // Chuỗi bị xóa
    act.newData = "";      // Không có chuỗi mới
    act.data = deleted;    // Đúng format cho printHistory

    history->addAction(act);
}

//replace v1
// void RopeTextBuffer::replace(int length, const std::string& s) {
//     // Thay thế hoàn toàn length ký tự bắt đầu từ vị trí ngay sau con trỏ bằng chuỗi s
//     // Độ phức tạp O(log n)
//     int totalLen = rope.length();
//     if (length < 0 || cursorPos + length > totalLen) {
//         throw std::out_of_range("Length is invalid!");
//     }
//     // Xoá length ký tự sau con trỏ
//     rope.deleteRange(cursorPos, length);
//     // Chèn chuỗi mới vào vị trí cursorPos
//     rope.insert(cursorPos, s);
//     cursorPos += s.length();
//     // TODO: Ghi lại lịch sử thao tác nếu cần
// }

//replace v2
// void RopeTextBuffer::replace(int length, const std::string& s) {
//     // Kiểm tra đầu vào
//     if (length < 0) {
//         throw std::out_of_range("Length is invalid!");
//     }
//     int totalLen = rope.length();
//     if (cursorPos < 0 || cursorPos > totalLen) {
//         // Nếu cursorPos không hợp lệ (không nên xảy ra nếu các hàm khác giữ invariant),
//         // ném lỗi hoặc điều chỉnh tuỳ thiết kế. Ở đây ta ném để an toàn.
//         throw std::out_of_range("Length is invalid!");
//     }
//     if (cursorPos + length > totalLen) {
//         throw std::out_of_range("Length is invalid!");
//     }

//     // Nếu không có gì để làm thì return (length == 0 và s rỗng)
//     if (length == 0 && s.empty()) return;

//     // --- (OPTIONAL) Lưu lịch sử trước khi thay đổi ---
//     // Ví dụ: lưu chuỗi bị xóa để undo:
//     // std::string deleted = (length > 0) ? rope.substring(cursorPos, length) : "";
//     // int cursorBefore = cursorPos;

//     // Thực hiện thay thế: xóa đoạn cũ, chèn đoạn mới
//     if (length > 0) {
//         rope.deleteRange(cursorPos, length);
//     }
//     if (!s.empty()) {
//         rope.insert(cursorPos, s);
//     }

//     // Cập nhật con trỏ: nằm ngay sau chuỗi vừa chèn
//     cursorPos += static_cast<int>(s.length());

//     // --- (OPTIONAL) Ghi lại hành động vào history (undo/redo) ---
//     // history->addAction(...); // cần thiết kế cấu trúc Action
// }

//replace v3
void RopeTextBuffer::replace(int length, const std::string& s) {
    // Đúng yêu cầu đề bài:
    // - Thay thế hoàn toàn length ký tự bắt đầu từ vị trí ngay sau con trỏ bằng chuỗi s
    // - Sau khi thay thế, con trỏ nằm ngay sau chuỗi vừa được thay thế vào
    // - Đầu vào: length và chuỗi s
    // - Độ phức tạp: O(log n)
    // - Ngoại lệ: Ném out_of_range("Length is invalid!") nếu length vượt quá giới hạn chuỗi

    if (length < 0) {
        throw std::out_of_range("Length is invalid!");
    }
    int totalLen = rope.length();
    // cursorPos có thể == totalLen (con trỏ ở cuối, cho phép replace 0 ký tự)
    if (cursorPos < 0 || cursorPos > totalLen) {
        // throw std::out_of_range("Cursor position is invalid!");
        return;
    }
    // Chỉ kiểm tra length nếu length > 0 (nếu length == 0 thì luôn hợp lệ)
    if (length > 0 && (cursorPos + length > totalLen)) {
        throw std::out_of_range("Length is invalid!");
    }

    if (length == 0 && s.empty()) return;

    // Lưu chuỗi cũ bị thay thế
    std::string deleted = (length > 0) ? rope.substring(cursorPos, length) : "";
    int cursorBefore = cursorPos;

    // Thay thế: xóa đoạn cũ, chèn đoạn mới
    if (length > 0) {
        rope.deleteRange(cursorPos, length);
    }
    if (!s.empty()) {
        rope.insert(cursorPos, s);
    }

    // cursorAfter của action "replace" là vị trí sau đoạn bị thay thế (theo đề)
    int cursorAfter = cursorBefore + length;

    // Lưu lịch sử thao tác
    HistoryManager::Action act;
    act.actionName = "replace";
    act.cursorBefore = cursorBefore;
    act.cursorAfter = cursorAfter;
    act.oldData = deleted;
    act.newData = s;
    act.data = deleted;

    history->addAction(act);

    // Sau replace, con trỏ nằm ngay sau chuỗi mới chèn vào
    cursorPos = cursorBefore + (int)s.length();
}



void RopeTextBuffer::moveCursorTo(int index) {
    if (index < 0 || index > rope.length()) {
        throw std::out_of_range("Index is invalid!");
    }
    int cursorBefore = cursorPos;
    cursorPos = index;
    // Ghi lịch sử di chuyển con trỏ
    if (history) {
        HistoryManager::Action act;
        act.actionName = "move";
        act.cursorBefore = cursorBefore;
        act.cursorAfter = cursorPos;
        act.data = "J"; // Jump
        act.oldData = "";
        act.newData = "";
        history->addAction(act);
    }
}

void RopeTextBuffer::moveCursorLeft() {
    if (cursorPos <= 0) {
        throw cursor_error();
    }
    int cursorBefore = cursorPos;
    --cursorPos;
    // Ghi lịch sử di chuyển con trỏ
    if (history) {
        HistoryManager::Action act;
        act.actionName = "move";
        act.cursorBefore = cursorBefore;
        act.cursorAfter = cursorPos;
        act.data = "L";
        act.oldData = "";
        act.newData = "";
        history->addAction(act);
    }
}

void RopeTextBuffer::moveCursorRight() {
    if (cursorPos >= rope.length()) {
        throw cursor_error();
    }
    int cursorBefore = cursorPos;
    ++cursorPos;
    // Ghi lịch sử di chuyển con trỏ
    if (history) {
        HistoryManager::Action act;
        act.actionName = "move";
        act.cursorBefore = cursorBefore;
        act.cursorAfter = cursorPos;
        act.data = "R";
        act.oldData = "";
        act.newData = "";
        history->addAction(act);
    }
}

int RopeTextBuffer::getCursorPos() const {
    // Trả về vị trí hiện tại của con trỏ
    // Độ phức tạp O(1)
    return cursorPos;
}

std::string RopeTextBuffer::getContent() const {
    // Trả về toàn bộ nội dung buffer hiện tại
    // Độ phức tạp O(n)
    return rope.toString();
}

//findFirst v1
// int RopeTextBuffer::findFirst(char c) const {
//     // Tìm vị trí xuất hiện đầu tiên của ký tự c
//     // Độ phức tạp O(n)
//     std::string content = rope.toString();
//     size_t pos = content.find(c);
//     if (pos == std::string::npos) return -1;
//     return static_cast<int>(pos);
// }

//findFirst v2
int RopeTextBuffer::findFirst(char c) const {
    std::string content = rope.toString();
    for (size_t i = 0; i < content.length(); ++i) {
        if (content[i] == c) return static_cast<int>(i);
    }
    return -1;
}

// findAll v1
// int* RopeTextBuffer::findAll(char c) const {
//     // Tìm tất cả vị trí xuất hiện của ký tự c
//     // Đầu ra: mảng động chứa các vị trí, nullptr nếu không có

//     std::string content = rope.toString();
//     int count = 0;
//     // Đếm số lần xuất hiện
//     for (size_t i = 0; i < content.length(); ++i) {
//         if (content[i] == c) ++count;
//     }
//     if (count == 0) return nullptr;

//     int* result = new int[count];
//     int idx = 0;
//     for (size_t i = 0; i < content.length(); ++i) {
//         if (content[i] == c) result[idx++] = static_cast<int>(i);
//     }
//     return result;
// }

//findAll v2
int* RopeTextBuffer::findAll(char c) const {
    // Lấy toàn bộ nội dung buffer
    std::string content = rope.toString();
    int n = static_cast<int>(content.length());

    // Đếm số lần xuất hiện của ký tự c
    int count = 0;
    for (int i = 0; i < n; ++i) {
        if (content[i] == c) {
            ++count;
        }
    }

    // Không có ký tự cần tìm -> trả về nullptr
    if (count == 0) {
        return nullptr;
    }

    // Cấp phát mảng kết quả và lưu các vị trí
    int* result = new int[count];
    int idx = 0;
    for (int i = 0; i < n; ++i) {
        if (content[i] == c) {
            result[idx++] = i;
        }
    }

    return result; // Người gọi cần tự delete[] sau khi dùng
}

void RopeTextBuffer::undo() {
    if (!history || !history->canUndo()) {
        // throw std::logic_error("No undo available");
        return;
    }

    auto action = history->getUndoAction();

    if (action.actionName == "insert") {
        rope.deleteRange(action.cursorBefore, action.newData.size());
        cursorPos = action.cursorBefore;
    }
    else if (action.actionName == "delete") {
        rope.insert(action.cursorBefore, action.oldData);
        cursorPos = action.cursorBefore; // Đúng: cursor về vị trí trước khi xóa
    }
    else if (action.actionName == "move") {
        // Sai ở đây: undo move chỉ cần trả cursor, KHÔNG đổi nội dung buffer!
        cursorPos = action.cursorBefore;
    }
    else if (action.actionName == "replace") {
        rope.deleteRange(action.cursorBefore, action.newData.size());
        if (!action.oldData.empty()) {
            rope.insert(action.cursorBefore, action.oldData);
        }
        cursorPos = action.cursorBefore + action.oldData.size();
    }

    history->moveUndoPointer(-1);
}

void RopeTextBuffer::redo() {
    if (!history || !history->canRedo()) {
        // throw std::logic_error("No redo available");
        return;
    }

    auto action = history->getRedoAction();

    if (action.actionName == "insert") {
        // Redo insert: chèn lại chuỗi đã chèn
        rope.insert(action.cursorBefore, action.newData);
        cursorPos = action.cursorBefore + action.newData.size();
    }
    else if (action.actionName == "delete") {
        // Redo delete: xóa lại chuỗi đã xóa
        rope.deleteRange(action.cursorBefore, action.oldData.size());
        cursorPos = action.cursorBefore;
    }
    else if (action.actionName == "move") {
        // Redo move: đưa cursor về vị trí sau thao tác
        cursorPos = action.cursorAfter;
    }
    else if (action.actionName == "replace") {
        // Redo replace: xóa chuỗi cũ, chèn lại chuỗi mới
        rope.deleteRange(action.cursorBefore, action.oldData.size());
        if (!action.newData.empty()) {
            rope.insert(action.cursorBefore, action.newData);
        }
        cursorPos = action.cursorBefore + action.newData.size();
    }

    history->moveUndoPointer(1);
}


void RopeTextBuffer::printHistory() const {
    // In ra lịch sử thao tác đã thực hiện
    // Độ phức tạp O(n)
    if (history) history->printHistory();
}

void RopeTextBuffer::clear() {
    // Xoá toàn bộ nội dung văn bản, đưa buffer về trạng thái rỗng
    // Độ phức tạp O(n)
    int len = rope.length();
    if (len == 0) {
        // Không có gì để xóa, con trỏ vẫn ở vị trí hiện tại
        return;
    }

    // Lưu vào lịch sử để có thể undo
    if (history) {
        HistoryManager::Action a;
        a.actionName   = "delete";         // Xem như xóa toàn bộ
        a.cursorBefore = cursorPos;        // Vị trí con trỏ trước khi clear
        a.cursorAfter  = 0;                // Sau clear, con trỏ về đầu
        a.data         = rope.toString();  // Lưu toàn bộ nội dung cũ
        a.oldData      = rope.toString();  // Để undo lại toàn bộ
        a.newData      = "";               // Sau clear là rỗng
        history->addAction(a);
    }

    // Xóa toàn bộ nội dung
    rope.deleteRange(0, len);
    cursorPos = 0;
}


// ----------------- HistoryManager -----------------
RopeTextBuffer::HistoryManager::HistoryManager() {
    capacity = 10;
    size = 0;
    current = -1;
    actions = new Action[capacity];
}

RopeTextBuffer::HistoryManager::~HistoryManager() {
    delete[] actions;
}
//addAction v1: redoStack sẽ bị xóa nếu có hành động cắt ngang 
// void RopeTextBuffer::HistoryManager::addAction(const Action& a) {
//     // Nếu đang undo và có redo history -> clear redo
//     if (current < size - 1) {
//         size = current + 1; // bỏ toàn bộ redo phía sau
//     }

//     ensureCapacity();

//     // Thêm vào cuối mảng
//     actions[size] = a;
//     size++;
//     current = size - 1; // con trỏ undo trỏ vào hành động mới nhất
// }

//addAction v2: redoStack sẽ KO bị xóa nếu có hành động cắt ngang 
// void RopeTextBuffer::HistoryManager::addAction(const Action& a) {
//     // Chỉ clear redo nếu đang undo và action là insert hoặc delete
//     if ((a.actionName == "insert" || a.actionName == "delete") && current < size - 1) {
//         size = current + 1; // bỏ toàn bộ redo phía sau
//     }

//     ensureCapacity();

//     actions[size] = a;
//     size++;
//     current = size - 1; // con trỏ undo trỏ vào hành động mới nhất
// }

//addAction v3 giống v2
// void RopeTextBuffer::HistoryManager::addAction(const Action& a) {
//     // Đang ở giữa lịch sử (có redo phía sau)?
//     if (current < size - 1) {
//         bool resetsRedo = (a.actionName == "insert" || a.actionName == "delete");

//         if (resetsRedo) {
//             // Chỉ insert/delete mới xóa redo
//             size = current + 1; // cắt bỏ toàn bộ redo phía sau
//             // rơi xuống nhánh append ở cuối hàm
//         } else {
//             // replace/move: KHÔNG xóa redo -> chèn a ngay sau current
//             ensureCapacity();                 // đảm bảo đủ chỗ cho size+1
//             int insertPos = current + 1;

//             // dịch phải đuôi [insertPos .. size-1]
//             for (int i = size; i > insertPos; --i) {
//                 actions[i] = actions[i - 1];
//             }

//             actions[insertPos] = a;
//             ++size;
//             current = insertPos;              // con trỏ undo trỏ tới action vừa thêm
//             return;
//         }
//     }

//     // Append bình thường (đang ở cuối lịch sử, hoặc vừa truncate do insert/delete)
//     ensureCapacity();
//     actions[size] = a;
//     ++size;
//     current = size - 1;
// }

//addAction v4
void RopeTextBuffer::HistoryManager::addAction(const Action& a) {
    if (current < size - 1) {
        bool resetsRedo = (a.actionName == "insert" || a.actionName == "delete");

        if (!resetsRedo && a.actionName == "replace") {
            const Action& nextRedo = actions[current + 1];
            // Kiểm tra nếu vùng bị thay thế mới trùng hoặc chạm vào vùng tác động của redo kế tiếp
            int aStart = a.cursorBefore;
            int aEnd   = a.cursorBefore + (int)a.oldData.size();

            int rStart = nextRedo.cursorBefore;
            int rEnd   = nextRedo.cursorBefore + (int)nextRedo.oldData.size();

            bool overlap = !(aEnd <= rStart || rEnd <= aStart);
            if (overlap) {
                resetsRedo = true;
            }
        }

        if (resetsRedo) {
            size = current + 1; // cắt redo
        } else {
            // Chèn action mới ngay sau current
            ensureCapacity();
            int insertPos = current + 1;
            for (int i = size; i > insertPos; --i) {
                actions[i] = actions[i - 1];
            }
            actions[insertPos] = a;
            ++size;
            current = insertPos;
            return;
        }
    }

    // Append bình thường (đang ở cuối lịch sử hoặc vừa truncate redo)
    ensureCapacity();
    actions[size] = a;
    ++size;
    current = size - 1;
}



bool RopeTextBuffer::HistoryManager::canUndo() const {
    // Kiểm tra có thể thực hiện undo không
    // Độ phức tạp O(1)
    return current >= 0;
}

bool RopeTextBuffer::HistoryManager::canRedo() const {
    // Kiểm tra có thể thực hiện redo không
    // Độ phức tạp O(1)
    return (current + 1) < size;
}

void RopeTextBuffer::HistoryManager::printHistory() const {
    // In ra danh sách tất cả các hành động đã được lưu trong lịch sử thao tác
    // Định dạng: [(actionName, cursorBefore, cursorAfter, data), ...]
    // Độ phức tạp O(n)
    std::cout << "[";
    for (int i = 0; i < size; ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << "("
                  << actions[i].actionName << ", "
                  << actions[i].cursorBefore << ", "
                  << actions[i].cursorAfter << ", "
                  << actions[i].data << ")";
    }
    std::cout << "]" << std::endl;
}

// RopeTextBuffer attributes and public methods are already implemented as required:
// - Rope rope: lưu trữ nội dung văn bản
// - int cursorPos: vị trí con trỏ hiện tại, bắt đầu từ 0, cuối là sau ký tự cuối cùng
// - HistoryManager* history: quản lý lịch sử thao tác

// Các phương thức công khai đã đúng yêu cầu đề bài:
// RopeTextBuffer()           // Khởi tạo buffer rỗng, con trỏ ở đầu
// ~RopeTextBuffer()          // Giải phóng bộ nhớ động O(n)
// void insert(const string&) // Chèn chuỗi tại vị trí con trỏ, O(log n)
// void deleteRange(int)      // Xoá đoạn văn bản sau con trỏ, O(log n), ném out_of_range nếu length vượt quá giới hạn
// void replace(int, const string&) // Thay thế đoạn sau con trỏ bằng chuỗi mới, O(log n), ném out_of_range nếu length vượt quá giới hạn

// Các phương thức dưới đã đúng yêu cầu đề bài:
// void moveCursorTo(int index)      // Di chuyển con trỏ đến vị trí index, O(1), ném out_of_range nếu index không hợp lệ
// void moveCursorLeft()             // Di chuyển con trỏ sang trái, O(1), ném cursor_error nếu ở đầu
// void moveCursorRight()            // Di chuyển con trỏ sang phải, O(1), ném cursor_error nếu ở cuối
// int getCursorPos() const          // Trả về vị trí hiện tại của con trỏ, O(1)
// string getContent() const         // Trả về toàn bộ nội dung buffer, O(n)
// int findFirst(char c) const       // Tìm vị trí đầu tiên của ký tự c, O(n), trả về -1 nếu không có
// int* findAll(char c) const        // Tìm tất cả vị trí xuất hiện của ký tự c, O(n), trả về nullptr nếu không có
// int findFirst(char c) const       // Tìm vị trí đầu tiên của ký tự c, O(n), trả về -1 nếu không có
// int* findAll(char c) const        // Tìm tất cả vị trí xuất hiện của ký tự c, O(n), trả về nullptr nếu không có
// int* findAll(char c) const        // Tìm tất cả vị trí xuất hiện của ký tự c, O(n), trả về nullptr nếu không có
// int findFirst(char c) const       // Tìm vị trí đầu tiên của ký tự c, O(n), trả về -1 nếu không có
// int* findAll(char c) const        // Tìm tất cả vị trí xuất hiện của ký tự c, O(n), trả về nullptr nếu không có
