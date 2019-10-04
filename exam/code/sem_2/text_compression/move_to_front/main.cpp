
#include <string>
#include <iostream>
#include <vector>

using namespace std;

// Returns index at which character of the input text
// exists in the list
int search(char input_char, string list) {
    int i;
    for (i = 0; i < list.size(); i++) {
        if (list[i] == input_char) {
            return i;
        }
    }
}

// Takes curr_index of input_char as argument
// to bring that character to the front of the list
string moveToFront(int curr_index, string list) {

    string record = list[curr_index] + list.substr(0, curr_index) + list.substr(curr_index+1);
    return record;
}

// Move to Front Encoding
void mtfEncode(string input_text, string list) {
    size_t len_text = input_text.size();
    vector<int> output_arr(len_text);

    for (int i = 0; i < len_text; i++) {

        // Linear Searches the characters of input_text
        // in list
        output_arr[i] = search(input_text[i], list);

        // Printing the Move to Front Transform
        cout << output_arr[i] << " ";

        // Moves the searched character to the front
        // of the list
        list = moveToFront(output_arr[i], list);
    }
}

// Driver program to test functions above
int main() {
    string input_text = "panama";

    string list = "abcdefghijklmnopqrstuvwxyz";

    cout << input_text << "\n";
    cout << "Move to Front Transform: ";

// Computes Move to Front transform of given text
    mtfEncode(input_text, list);

    return 0;
}
