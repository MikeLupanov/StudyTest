#include <iostream>
#include <string>
#include "vigenere.h"
using namespace std;
int main(int argc, char **argv)
{
    string key;
    string text;
    unsigned op;
    cout<<"Cipher ready. Input key: ";
    cin>>key;
    Vigenere cipher(key);
    do {
        cout<<"Cipher ready. Input operation (0-exit, 1-encrypt, 2-decrypt): ";
        cin>>op;
        if (op > 2) {
            cout<<"Illegal operation\n";
        } else if (op >0) {
            cout<<"Cipher ready. Input text: ";
            cin>>text;
            try {
                if (op==1) {
                    cout<<"Encrypted text: "<<cipher.encrypt(text)<<endl;
                } else {
                    cout<<"Decrypted text: "<<cipher.decrypt(text)<<endl;
                }
            } catch(std::invalid_argument& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    } while (op!=0);
    return 0;
}
