#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <math.h>

using namespace std;

// Structure for a Huffman Tree node
struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = right = nullptr;
    }
};

// Comparison function for priority queue
struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// Traverse the Huffman Tree and generate codes
void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& codes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '$') {
        codes[root->data] = code;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

int fixedsize(const std::string& input) {
    std::unordered_map<char, int> frequencyMap;

    for (char c : input) {
        frequencyMap[c]++;
    }

    int s_size = frequencyMap.size();
    int power = 0;

    for (int i = 0; i < 6; i++) { // Adjusted loop condition to cover up to 32
        if (s_size <= pow(2, i)) {
            power = i;
            break;
        }
    }

    return power * input.length();
}


// Build the Huffman Tree
HuffmanNode* buildHuffmanTree(string input) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> minHeap;

    unordered_map<char, int> frequencyMap;
    for (char c : input) {
        frequencyMap[c]++;
    }


    for (auto pair : frequencyMap) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        minHeap.push(node);
    }

    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        HuffmanNode* internalNode = new HuffmanNode('$', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    return minHeap.top();
}

// Encode the input string using Huffman Codes
string huffmanEncode(string input, unordered_map<char, string>& codes) {
    string encodedString = "";
    for (char c : input) {
        encodedString += codes[c];
    }
    return encodedString;
}

int main() {
    string input = "";
    cout << "Enter a string: ";
    getline(cin, input);
    int fixedSizeBits = fixedsize(input);
    // Build Huffman Tree


    HuffmanNode* root = buildHuffmanTree(input);

    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "Character Codes:\n";
    for (auto pair : codes) {
        cout << pair.first << " : " << pair.second << endl;
    }

    string encodedString = huffmanEncode(input, codes);

    cout << "\nOriginal String: " << input << endl;
    cout<<endl<<endl;
    cout << "Encoded String: " << encodedString << endl;


    int variableSizeBits = encodedString.length();

    cout << "\nBits required for Fixed-Size Encoding: " << fixedSizeBits << " bits\n";
    cout << "Bits required for Variable-Length Encoding: " << variableSizeBits << " bits\n";

    return 0;
}
