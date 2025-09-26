 #include <iostream>
using namespace std;
#include <string>
#include "Image_Class.h"
#include<cstdlib>

// el function el mosta5dama
Image merge(string name1);
Image filter_reverse_color(string name);
Image filter_gray(string name);
Image filter_balck_and_white(string name);
void menu();
void editing();

void to_show_new_image(Image img){//function lel natega
    string name;

    cout << "\nImage processing completed successfully!\n";
    cout << "\n Enter a name to save the edited image (with extension): ";
    cin.ignore();
    getline(cin, name);

    char o;
    cout << "\n Do you want to save the edited image? (Y/N): ";
    cin>>o;
    if(o=='Y'||o=='y'){

        bool saved=img.saveImage(name);
        if(saved){
            cout << "Image saved successfully!\n";
            cout << "New image name: " << name << endl;
            
            // fat7 l sora auto
            string com="start "+name;
            system(com.c_str());
        }else{
            cout<<"Failed to save image.\n";
        }

    }else cout << "Image not saved.\n";
}

void editing(){
    string image_name;
    cout << "\n Enter the name of the image file to edit: ";
    cin.ignore(); // 34an law fe input m4 mohema
    getline(cin, image_name); 
    
    int op;
    cout << "\n Available Filters:\n";
    cout << "\t1 - Grayscale\n";
    cout << "\t2 - Black & White\n";
    cout << "\t3 - Reverse Colors\n";
    cout << "\t4 - Merge 2 images\n";
    cout << "Please choose a filter (1, 2, 3, 4): ";
    cin>>op;
    
    Image processed_image;
    switch (op){
    case 1:
        processed_image = filter_gray(image_name); // gray
        break;
    case 2:
        processed_image = filter_balck_and_white(image_name); //  B & w
        break; 
    case 3:
        processed_image = filter_reverse_color(image_name); // rev the color
        break; 
    case 4:
        processed_image = merge(image_name); 
        break; 
    default:
        cout << " Invalid option.\n";   // law e5tar raqam mo5talef
        return;
    }
    
    to_show_new_image(processed_image); // le 3ard l sora ba3d l ta3deel
}

void menu(){
    string x;
    do
    {
        int op;
        cout << "Welcome to the Photo Editing Program!\n";
        cout << "\t1 - Edit an image\n";
        cout << "\t2 - Exit the program\n";
        cout << "Please choose an option (1 or 2): ";
        cin>>op;
        
        if(op == 1){
            editing(); 
        }
        else if(op == 2){
            exit(0); 
        }
        else{
            cout << " Invalid option.\n";
            continue;
        }
        
        cout << "\n Would you like to edit another image? (Y/N): ";
        cin>>x;
        cin.ignore(); 
    } while (x=="Y" || x=="y" || x=="yes"); 
}

// l tagbeer w tas8er l sora
Image resizeImage(const Image& original, int newWidth, int newHeight) {
    Image resized(newWidth, newHeight); // 3mal sora gdeda bakbar H & w
    
    for (int h = 0; h < newHeight; h++) {
        for (int w = 0; w < newWidth; w++) {


            // originalX = (newX / newWidth) × originalWidth
            // (Scaling Formula) قانون التحجيم
            // دا عشان نظبط ابعاد الصورتين على بعض

            float originalW = (float)w / newWidth * original.width;
            float originalH = (float)h / newHeight * original.height;
            
            int w1 = min((int)originalW, original.width - 1);
            int h1 = min((int)originalH, original.height - 1);
            
            // نسخ البكسل من الصورة الأصلية إلى الصوره الجديده
            for (int i = 0; i < 3; i++) {
                resized(w, h, i) = original(w1, h1, i);
            }
        }
    }
    return resized;
}

//  دمج صورتين
Image merge(string name1){
    Image img1;
    Image img2;
    string name2;
    cout << "Enter the name for the second image: ";
    cin.ignore(); 
    getline(cin, name2); // esm l sora l tanya
    
    try{
        img1.loadNewImage(name1); 
        img2.loadNewImage(name2); 
        
    }catch(...){
        cout<<"file not found"<<endl;
        return Image(1,1); // 
    }
    
    int finalWidth = max(img1.width, img2.width);
    int finalHeight = max(img1.height, img2.height);
    
    // تكبير الصورتين لنفس الحجم (جعل الصورة الصغيرة تكبر لتناسب الكبيرة)
    Image resized_img1 = resizeImage(img1, finalWidth, finalHeight);
    Image resized_img2 = resizeImage(img2, finalWidth, finalHeight);
    
    Image result(finalWidth, finalHeight);
    
    // damg l sorteen
    for(int h = 0; h < finalHeight; h++){
        for(int w = 0; w < finalWidth; w++){
            for(int i = 0; i < 3; i++){
                // avg l pixel lel sorteen
                int avg = (resized_img1(w, h, i) + resized_img2(w, h, i)) / 2;
                result(w, h, i) = avg;
            }
        }
    }
    
    return result; 
}

Image filter_gray(string name){
    Image img;
    try{
        img.loadNewImage(name); 
    }catch(...){
        cout<<"file not found"<<endl;
        return Image(1,1);
    }

    
    for (int h=0;h<img.height;h++) {
        for (int w=0; w < img.width; w++) {
            unsigned int avg=0;
            
            for (int i=0;i<3;i++) {
                avg+=img(w,h,i);
            }
            avg/=3; 
            
            for (int i=0;i<3;i++) {
                img(w,h,i)=avg;
            }
        }
    }
    return img;
}

Image filter_balck_and_white(string name){
    Image img;
    try{
        img.loadNewImage(name);
    }catch(...){
        cout<<"file not found"<<endl;
        return Image(1,1);
    }

    for(int h=0;h<img.height;h++){
        for(int w=0;w<img.width;w++ ){
            unsigned int avg=0;
            
            for(int i=0;i<3;i++){
                avg+=img(w,h,i);
            }
            avg/=3;
            
            for(int i=0;i<3;i++){
                if(avg>128){
                    img(w,h,i)=255; // w
                }else{
                    img(w,h,i)=0;   // B
                }
            }
        }
    }
    return img;
}

Image filter_reverse_color(string name){
    Image img;
    try{
        img.loadNewImage(name); 
    }catch(...){
        cout<<"file not found\n";
        return Image(1,1);
    }
    
    // عكس كل لون في الصورة (255 - القيمة الأصلية)
    for(int h=0;h<img.height;h++){
        for(int w=0;w<img.width;w++){
            for(int i=0;i<3;i++){
                img(w,h,i)=255-img(w,h,i);
            }
        }
    }
    return img;
}

int main() {
    menu(); 
    return 0;
}
