 #include <iostream>
 #include<bits/stdc++.h>
#include "Image_Class.h"

using namespace std;

// flip horizontel
void flipHorz(Image &img) { //el ta3deel bykon fel l sora l asleya
    int width = img.width;
    int height = img.height;

    for (int y = 0; y < height; y++) {                                    // nemshy 3la kol saf
        for (int x = 0; x < width / 2; x++) {                             // ne2leb nos l 3amod
            for (int c = 0; c < img.channels; c++) {                      // 3shan me4 bnkon 3arfeen no3 l sora
                unsigned char left = img(x, y, c);
                unsigned char right = img(width - 1 - x, y, c);          //l 3amod l a5eer - l 3amod l 7aly
                img(x, y, c) = right;                                    //badelna l pixel ely 3la l shemal lel yemen
                img(width - 1 - x, y, c) = left;// el3aks
            }
        }
    }
}

// flip vertical
void flipVert(Image &img) {
    int width = img.width;
    int height = img.height;

    for (int y = 0; y < height / 2; y++) {      
        for (int x = 0; x < width; x++) {       
            for (int c = 0; c < img.channels; c++) {
                unsigned char top = img(x, y, c);
                unsigned char bottom = img(x, height - 1 - y, c);
                img(x, y, c) = bottom;
                img(x, height - 1 - y, c) = top;
            }
        }
    }
}

int main() {
    string input;
    cout << "Enter input image file name: ";
    getline(cin, input);   //3ashan l msafat ely fe esm l file

    Image img(input);  // neqra2 l sora

    int choice;
    cout << "Choose flip option:\n";
    cout << "1. Flip Horizontally\n";
    cout << "2. Flip Vertically\n";
    cout << "3. Flip Both\n";
    cin >> choice;

    if (choice == 1) {
        flipHorz(img);
    } 
    else if (choice == 2) {
        flipVert(img);
    } 
    else if (choice == 3) {
        flipHorz(img);
        flipVert(img);
    } 
    else {
        cout << "Invalid choice.\n";
        return 0;
    }

    
    // نحفظ الصورة بنفس الاسم اللي دخل المستخدم (overwrite)
    img.saveImage(input);
    cout << "Image saved successfully as " << input << endl;

    return 0;
}
