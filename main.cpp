#include <iostream>
using namespace std;
#include <string>
#include "Image_Class.h"
#include<bits/stdc++.h>


#include<cstdlib>

Image merge(string name1);
Image filter_reverse_color(string name);
Image filter_gray(string name);
Image filter_balck_and_white(string name);
Image filter_rotate_170_90(string name) ;
Image filter_flip(string name);
void menu();
void editing();

void to_show_new_image(Image img){
    string name;
    int op;
    cout<<"";
    cout << "\n Enter a name to save the edited image (without extension): ";
    cin>>name;
    cout << "\nChoose a file format to save the image:\n";
    cout << "\t1 - .jpeg\n";
    cout << "\t2 - .jpg\n";
    cout << "\t3 - .png\n";
    cout << "\t4 - .bmp\n";
    cout << "Enter your choice (1-4): ";
    cin>>op;
    string newImage;
    switch (op)
    {
    case 1:
        newImage=name+".jpeg";
        break;
    case 2:
        newImage=name+".jpg";
        break;
    case 3:
        newImage=name+".png";
        break;
    case 4:
        newImage=name+".bmp";
        break;
    
    default:
        cout << "Invalid choice. Defaulting to .jpg\n";
    }

    char o;
    cout << "\n Do you want to save the edited image? (Y/N): ";
    cin>>o;
    if(o=='Y'||o=='y'){

        bool saved=img.saveImage(newImage);
        if(saved){
            string com="start "+newImage;
            cout<<"file saved:are you want show the image?{Y , N}\n";
            char choise;
            cin>>choise;
            if (choise=='Y'|| choise=='y')system(com.c_str());

        }else{
            cout<<"Failed to save image.\n";
        }

    }else cout << "Image not saved.\n";
    
    
    
    

    

}

Image flipVert(Image &img) {
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
    return img;
}
Image flipHorz(Image &img) { //el ta3deel bykon fel l sora l asleya
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
    return img;
}




void editing(){
    string image_name;
    cout << "\n Enter the full path of the image file:";
    cin>>image_name;
    
    int op;
    cout << "\n Available Filters:\n";
    cout << "\t1 - Grayscale\n";
    cout << "\t2 - Black & White\n";
    cout << "\t3 - Reverse Colors\n";
    cout << "\t4 - merge 2 image\n";
    cout << "\t5 - Flip Image\n";
    cout<<"\t6-rotate 90 or 270 degrees\n";
    cout << "Please choose a filter (1, 2, 3, 4, 5, ...): ";
    cin>>op;
    switch (op){
    case 1:
        to_show_new_image(filter_gray(image_name));
        break;
    case 2:
        to_show_new_image(filter_balck_and_white(image_name));
        break; 
    case 3:
        to_show_new_image(filter_reverse_color(image_name));
        break; 
    case 4:
        to_show_new_image(merge(image_name));
        break; 
    case 5:
        to_show_new_image(filter_flip(image_name));
        break;
    case 6:
        to_show_new_image(filter_rotate_170_90(image_name));
    default:
            cout << " Invalid option.\n";   
    

    }
    
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
        switch (op)
        {
            case 1:
                editing();    
                break;
            case 2:
                exit(0);
                break;
            default:
                cout << " Invalid option.\n";
        }
        cout << "\n Would you like to edit another image? (Y/N): ";
        
        cin>>x;
    } while (x=="Y" || x=="y" || x=="yes");
    

    


}

Image merge(string name1){
    Image img1;
    Image img2;
    string name2;
    cout<<"enter the name for image 2:";
    cin>>name2;
    try{
        img1.loadNewImage(name1);
        img2.loadNewImage(name2);
        
    }catch(...){
        cout<<"file not found"<<endl;
    }
    int a1=img1.width*img1.height;
    int a2=img2.width*img2.height;
    if(a1>a2){
        for(int w=0;w<img2.width;w++){
        for(int h=0;h<img2.height;h++){
            for(int i=0;i<3;i++){
                img1(w,h,i) = (img1(w,h,i) + img2(w,h,i)) / 2;
            }
        }
    }
    return img1;

    }
    for(int w=0;w<img1.width;w++){
        for(int h=0;h<img1.height;h++){
            for(int i=0;i<3;i++){
                img2(w,h,i) = (img1(w,h,i) + img2(w,h,i)) / 2;
            }
        }
    }
    return img2;
    
}

Image filter_gray(string name){

    Image img;
    try{
        img.loadNewImage(name);
    }catch(...){
        cout<<"file not found"<<endl;
        return img;
    }

    

    for (int w= 0; w < img.width; w++) {
        for (int h=0;h<img.height;h++) {
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
        return img;
    }

    for(int w=0;w<img.width;w++){
        for(int h=0;h<img.height;h++ ){
            unsigned int avg=0;
            for(int i=0;i<3;i++){
                avg+=img(w,h,i);
            }
            avg/=3;
            for(int i=0;i<3;i++){
                if(avg>128){
                    img(w,h,i)=255;
                }else{
                    img(w,h,i)=0;
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
    }
    for(int w=0;w<img.width;w++){
        for(int h=0;h<img.height;h++){
            
            for(int i=0;i<3;i++){
                img(w,h,i)=255-img(w,h,i);
            }
            

        }
    }
    return img;
}

Image filter_flip(string name){
    Image img(name);
    int choice;
    cout << "Choose flip option:\n";
    cout << "1. Flip Horizontally\n";
    cout << "2. Flip Vertically\n";
    cout << "3. Flip Both\n";
    cin >> choice;
    if (choice == 1) {
        return flipHorz(img);
    }
    else if (choice == 2) {
        return flipVert(img);
    }
    else if (choice == 3) {
        flipHorz(img);
        flipVert(img);
        return img;
    }
    else {
        cout << "Invalid choice.\n";
        return img;
    }


}

Image filter_rotate_170_90(string name) {
    //المفروض هنمشي على عمود عمود نخليه صف عشان نشقلبها
    int angle;
    Image img(name);
    cout << "Enter rotation angle (90 or 270 or 180 degrees): ";
    cin >> angle;

    if (angle != 90 && angle != 270 &&angle!=180) {
        cout << "Only 90 or 270 or 180degrees are supported.\n";
        return img;
    }
    if (angle==180) {
        return flipVert(img);
    }
    int newWidth=img.height;
    int newHeight=img.width;
    Image newImage(newWidth,newHeight);//انشاء صوره بابعاد مقلوبه
    for (int h = 0; h < img.height; h++) {
        for (int w = 0; w < img.width; w++) {
            for (int i = 0; i < 3; i++) {
                if (angle == 90) {
                    newImage(img.height - 1 - h, w, i) = img(w, h, i);
                } else if (angle == 270) {
                    newImage(h, img.width - 1 - w, i) = img(w, h, i);
                }
            }
        }
    }

    return newImage;
}


int main() {

    
    menu();


    return 0;
}
